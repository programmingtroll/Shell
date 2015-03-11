#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H
#include <QObject>
#include <QDir>
#include <QFile>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QProcess>
#include <QSysInfo>
#include <QString>
#include <QStringList>
#include <QDebug>
#include "keyreturnevent.h"

class commandHandler:public QObject
{
     Q_OBJECT
     QDir *Location;
     QString system;
     QSysInfo localSystem;
     QString cdPattern;
     QString cmdOFilePat;
     QRegularExpression reg;
     QRegularExpressionMatch match;
     QStringList genericList;
     QDir *myDir;
     KeyReturnEvent *Parent;
     QProcess *myProcess;
     QString *programOrFile;
     QStringList *arguments;
public:
    commandHandler(KeyReturnEvent* Parent, QDir *myDir,QDir *Location);
    void sendcommand(QString linea);

};

#endif // COMMANDHANDLER_H
