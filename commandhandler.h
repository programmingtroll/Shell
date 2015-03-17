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
#include <QList>
#include <QSysInfo>
#include "keyreturnevent.h"
#include "capsuleprg.h"

class commandHandler:public QObject
{
     Q_OBJECT
     QString system;
     QSysInfo localSystem;
     QString cdPattern;
     QString cmdOFilePat;
     QString pipesPattern;
     QRegularExpression reg;
     QRegularExpressionMatch match;
     QStringList genericList;
     QSysInfo thisPlatform;
     QDir *Location;
     QDir *myDir;
     KeyReturnEvent *Parent;
     QProcess *myProcess;
     QString *programOrFile;
     QStringList *arguments;
     QList <capsulePrg*> prgWithArgs;
     QList <QProcess*> processes;
public:
    commandHandler(KeyReturnEvent* Parent, QDir *myDir,QDir *Location);
    void sendcommand(QString linea);
    inline QString verifier(QString program);
    void streamRedirection(QProcess*);

};

#endif // COMMANDHANDLER_H
