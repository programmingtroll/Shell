#include "commandhandler.h"

commandHandler::commandHandler(KeyReturnEvent *Parent, QDir *myDir, QDir *Location)
{
    this->Parent = Parent;
    this->myDir = myDir;
    this->Location = Location;
    this->arguments = new QStringList();
    this->cdPattern = QString("^cd\\s+([A-Z]:)?(/\)?(((\\w+\\d*\.?(/\)?(\/)?)+)|\.{2})$");
    this->cmdOFilePat = QString("^\\w+\\s*([\-]*\\w+\\d*\.?(/\)?(\/)?(\\s)?)*$");
    this->pipesPattern = QString("\\|");
}


void commandHandler::sendcommand(QString linea)
{
    reg.setPattern(cdPattern);
    match = reg.match(linea.trimmed());
    if (match.hasMatch()) {
        int firstSpace = linea.indexOf(" ");
        linea = linea.mid(firstSpace).trimmed();
        //qDebug()<< linea;
        //genericList = linea.split(" ",QString::SkipEmptyParts);
//        if ('/' ==genericList.at(1).at(1)) {
//            genericList.replace(1,Location->path()+genericList.at(1));
//        }
        bool sucess = Location->cd(linea);
        if (sucess) {
            Parent->prompt();
        }else{
            Parent->prompt("No existe ese directorio");
        }
        return;
    }

    reg.setPattern(pipesPattern);
    match = reg.match(linea.trimmed());
    if (match.hasMatch()) {
        genericList = linea.split("|",QString::SkipEmptyParts);
        int firstSpace;
        for (int i = 0; i < genericList.size(); ++i) {
            genericList.replace(i,genericList.at(i).trimmed());
            firstSpace = genericList.at(i).indexOf(" ");
            if (firstSpace == -1) {
                prgWithArgs.append(new capsulePrg(genericList.at(i)));
                prgWithArgs.at(i)->insertParam(0,Location->path());
            }else{
                prgWithArgs.append(new capsulePrg(genericList.at(i).left(firstSpace),
                                                  genericList.at(i).mid(firstSpace)) );
                prgWithArgs.at(i)->insertParam(0,Location->path());
//                qDebug()<< genericList.at(i).left(firstSpace);
//                qDebug()<< genericList.at(i).mid(firstSpace);
            }
        }
        bool doPipes = true;
        int command = 0;
        for (int i = 0; i < prgWithArgs.size(); ++i) {
            prgWithArgs.at(i)->setProgramPath(verifier(prgWithArgs.at(i)->getName()));
            if (prgWithArgs.at(i)->getProgramPath() == "") {
                command = i;
                doPipes = false;
                break;
            }
        }
        if (doPipes) {
            //Limpieza de la lista de procesos si es necesario.
            if (processes.size()>0) {
                processes.clear();
            }

            //Creacion de procesos hijos
            for (int i = 0; i < prgWithArgs.size(); ++i) {
                processes.append(new QProcess(Parent));
            }

            //Redireccion del flujo de salida del proceso n con el n+1.
            for (int i = 0; i < processes.size()-1; ++i) {
                processes.at(i)->setStandardOutputProcess(processes.at(i+1));
            }

            //Conexion del ultimo proceso con la entrada estandar de la consola.
            myProcess = processes.at(processes.size()-1);
            Parent->setMyProcess(myProcess);
            streamRedirection(myProcess);

            //Inicio de todos los procesos.
            for (int i = 0; i < processes.size(); ++i) {
                processes.at(i)->start(prgWithArgs.at(i)->getProgramPath(),
                                       prgWithArgs.at(i)->getParams());
            }
        }else{
            Parent->prompt("El comando "+prgWithArgs.at(command)->getName()+" no fue encontrado");
        }
        
    }

    reg.setPattern(cmdOFilePat);
    match = reg.match(linea.trimmed());
    if (match.hasMatch()) {
        genericList = linea.split(" ",QString::SkipEmptyParts);
        arguments->clear();
        arguments->append(Location->path());
        if (genericList.size()>1) {
            for (int i = 1; i < genericList.size(); ++i) {
                arguments->append(genericList.at(i));
            }
        }
        QString path = verifier(genericList.at(0));
//        qDebug()<<"Este es el path: "+path;
//        qDebug()<<"Estos son los argumentos: "<<*arguments;
        if (path != "") {
            programOrFile = new QString(path);
            myProcess= new QProcess(Parent);
            Parent->setMyProcess(myProcess);
            Parent->prompt("simpleline");
            streamRedirection(myProcess);
            myProcess->start(*programOrFile,*arguments);
        }else{
            Parent->prompt("Comando no encontrado.");
        }
    }
}

inline QString commandHandler::verifier(QString program)
{
    program = "/"+program;
    QString path = "";
    QFile fileOrCmd(myDir->path()+program);
    if (thisPlatform.productType() == "windows") {
        fileOrCmd.setFileName(fileOrCmd.fileName()+".exe");
    }
    if (fileOrCmd.exists()) {
        path = myDir->path()+ program;
    }else{
        fileOrCmd.setFileName(Location->path()+program);
        if (fileOrCmd.exists()) {
            path = Location->path()+program;
        }
    }
    return path;
}

void commandHandler::streamRedirection(QProcess * process)
{
    connect (process, SIGNAL(readyReadStandardOutput()), Parent, SLOT(processOutput()));
    connect (process, SIGNAL(readyReadStandardError()), Parent, SLOT(processOutputError()));
    connect (process, SIGNAL(finished(int,QProcess::ExitStatus)), Parent, SLOT(finishedProcess(int,QProcess::ExitStatus)));
}



