#ifndef KEYRETURNEVENT_H
#define KEYRETURNEVENT_H
#include <QObject>
#include <QKeyEvent>
#include <QMainWindow>
#include <ui_mainwindow.h>
#include <QDebug>
#include <QProcess>
#include <QString>
#include <QDir>

class commandHandler;

class KeyReturnEvent: public QObject
{
    Q_OBJECT
    int stateProcess;
    QTextCursor cursor;
    int position;
    int lastPos;
    QMainWindow *Parent;
    Ui_MainWindow* ParentUI;
    QProcess* myProcess = NULL;
    QDir *myDir;
    QDir *Location;
    commandHandler *handler;
public:
    KeyReturnEvent(QMainWindow *Parent,Ui_MainWindow* ParentUI);
    void prompt();
    void prompt(QString);
    QDir *getLocation() const;
    void setLocation(QDir *value);

    QDir *getMyDir() const;
    void setMyDir(QDir *value);

    QProcess *getMyProcess() const;
    void setMyProcess(QProcess *value);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

public slots:
    void processOutput();
    void processOutputError();
    void finishedProcess(int, QProcess::ExitStatus);
};

#include "commandhandler.h"

#endif // KEYRETURNEVENT_H
