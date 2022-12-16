#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowFlags ( Qt::FramelessWindowHint ); //Frameless

    // timer to the splash screen loading
    t1= new QTimer(this);
    t1->setInterval(10);
    connect(t1,SIGNAL(timeout()),this,SLOT(loadThread()));
    t1->start();


    // centering login screen ui
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
     _x = (screenGeometry.width()- Authihentication.width()) / 2;
     _y = (screenGeometry.height()- Authihentication.height()) / 2;

     ui->status->setText("loading data .... ");


}

// thread for loading splash screen
void MainWindow::loadThread()
{
    i++;
    if(i==150)
    {
        ui->status->setText("initializing graphics .... ");
    }
    if(i==250)
    {
        ui->status->setText("initializing database .... ");
    }
    if(i<360)
    {
       ui->loadingpanel->resize(i,20);
    }
    else
    {
       ui->status->setText("successfully initialized  .... ");
       Authihentication.move(_x, _y);
       Authihentication.show();
       t1->stop();
       close();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

