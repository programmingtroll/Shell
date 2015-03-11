#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "keyreturnevent.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   //enterAction* action = new enterAction(this->ui);
    KeyReturnEvent *evento = new KeyReturnEvent(this,this->getUi());
    ui->textEdit->installEventFilter(evento);

}

MainWindow::~MainWindow()
{
    delete ui;
}


Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}

void MainWindow::setUi(Ui::MainWindow *value)
{
    ui = value;
}


