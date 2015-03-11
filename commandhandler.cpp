#include "commandhandler.h"

commandHandler::commandHandler(KeyReturnEvent *Parent, QDir *myDir, QDir *Location)
{
    this->Parent = Parent;
    this->myDir = myDir;
    this->Location = Location;
    this->arguments = new QStringList();
    this->cdPattern = QString("^cd\\s+([A-Z]:)?(/\)?(((\\w+\\d*\.?(/\)?(\/)?)+)|\.{2})$");
    this->cmdOFilePat = QString("^\\w+\\s*([\-]*\\w+\\d*\.?(/\)?(\/)?(\\s)?)*$");
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
        genericList.replace(0,"/"+genericList.at(0));
        int type = -1;
        QString path = "";
        QFile fileOrCmd(myDir->path()+genericList.at(0));
        if (fileOrCmd.exists()) {
            path = myDir->path()+ genericList.at(0);
            type =0;
        }else{
            fileOrCmd.setFileName(Location->path()+genericList.at(0));
            if (fileOrCmd.exists()) {
                path = Location->path()+genericList.at(0);
                type = 1;
            }
        }
        //path = "C:\\Users\\OWNER\\Documents\\Qt_creations\\build-Console-Desktop_Qt_5_2_1_MinGW_32bit-Release\\release\\rm.exe";
        qDebug()<<"Este es el path: "+path;
        for (int var = 0; var < arguments->size(); ++var) {
            qDebug()<<"Estos son los argumentos: "+QString::number(var)+" "+arguments->at(var);
        }
        if (type != -1) {
            programOrFile = new QString(path);
            myProcess= new QProcess(Parent);
            Parent->setMyProcess(myProcess);
            connect (myProcess, SIGNAL(readyReadStandardOutput()), Parent, SLOT(processOutput()));
            connect (myProcess, SIGNAL(readyReadStandardError()), Parent, SLOT(processOutputError()));
            connect (myProcess, SIGNAL(finished(int,QProcess::ExitStatus)), Parent, SLOT(finishedProcess(int,QProcess::ExitStatus)));
            myProcess->start(*programOrFile,*arguments);
        }
    }
}



