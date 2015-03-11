#include "keyreturnevent.h"

KeyReturnEvent::KeyReturnEvent(QMainWindow *Parent, Ui_MainWindow *ParentUI)
{
    this->Parent = Parent;
    this->ParentUI = ParentUI;
    myDir = new QDir(QDir::current());
    Location = new QDir(QDir::root());
    myDir->cd("release");
    prompt();
    cursor = ParentUI->textEdit->textCursor();
    lastPos = cursor.position();
    position = cursor.position();
    handler = new commandHandler(this,myDir,Location);
    // a = & handler--getMyProcess()
    qDebug()<<myDir->path();
}

bool KeyReturnEvent::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
             if(cursor.position() < lastPos){
                 ParentUI->textEdit->insertPlainText(" ");
                 cursor.setPosition(position,QTextCursor::KeepAnchor);;
                 return true;
             }
             if (keyEvent->key() == 16777220) {
                 //Comando a ejecutar debe ir aqui

                 position = cursor.position();
                 cursor.setPosition(lastPos,QTextCursor::MoveAnchor);
                 cursor.setPosition(position,QTextCursor::KeepAnchor);
                 QString linea =cursor.selectedText();
                 //qDebug()<< linea ;

                 if (myProcess == NULL) {
                       handler->sendcommand(linea);
                 } else {
                     stateProcess = myProcess->state();
                     if (stateProcess == 2) {
                         if (myProcess->isWritable()) {
                             QByteArray array;
                             array.append(linea);
                             array.append('\0');
                             myProcess->write(array);
                             //myProcess->closeWriteChannel();
                             //return QObject::eventFilter(obj, event);
                             return true;
                         }
                     }
                 }
                 return true;
             }
             if (keyEvent->key() == 16777217) {
                 //Autocompletacion de comandos
                 return true;
             }
             position = cursor.position();
      }
    return QObject::eventFilter(obj, event);
}

void KeyReturnEvent::prompt()
{
    ParentUI->textEdit->append("Command:$"+ Location->path()+"> ");
    lastPos = cursor.position();
}

void KeyReturnEvent::prompt(QString value)
{
    ParentUI->textEdit->append(value);
    ParentUI->textEdit->append("Command:$"+ Location->path()+"> ");
    lastPos = cursor.position();
}


void KeyReturnEvent::processOutput()
{ 
    ParentUI->textEdit->append(myProcess->readAllStandardOutput());  // read normal output
    lastPos = cursor.position();
}

void KeyReturnEvent::processOutputError()
{
    ParentUI->textEdit->append(myProcess->readAllStandardError());  // read error channel
    lastPos = cursor.position();
}

void KeyReturnEvent::finishedProcess(int exitCode, QProcess::ExitStatus exit)
{
    if (exit) {
          ParentUI->textEdit->append("The process crashed, exit code:"+QString::number(exitCode));
    }else{
        //ParentUI->textEdit->insertPlainText("The process exited normally.");
    }
    myProcess->~QProcess();
    myProcess = NULL;
    prompt();
    lastPos = cursor.position();
}

QDir *KeyReturnEvent::getLocation() const
{
    return Location;
}

void KeyReturnEvent::setLocation(QDir *value)
{
    Location = value;
}

QDir *KeyReturnEvent::getMyDir() const
{
    return myDir;
}

void KeyReturnEvent::setMyDir(QDir *value)
{
    myDir = value;
}


QProcess *KeyReturnEvent::getMyProcess() const
{
    return myProcess;
}

void KeyReturnEvent::setMyProcess(QProcess *value)
{
    myProcess = value;
}

