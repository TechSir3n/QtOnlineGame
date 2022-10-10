#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QGridLayout>
#include <stdexcept>
#include <QComboBox>
#include <QListWidget>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Online Game");
    setDate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpServer()
{
    _server=new QTcpServer(this);
    _socket=new QTcpSocket(this);

    if(!_server->listen(QHostAddress::Any,12345)){
        QMessageBox::critical(this,"Listening error","Failed connect !");
        _server->errorString();
    }
    else{
        connect(_server,SIGNAL(newConnection()),this,SLOT(newConnection()));

    }
}

void MainWindow::newConnection()
{
    _socket=_server->nextPendingConnection();

    if(_socket==nullptr){
        QMessageBox::critical(this,"Error in newCon","Failed accept signal from client !");
        exit(EXIT_FAILURE);
    }
    else{
        connect(_socket,SIGNAL(disconnected()),this,SLOT(deleteLater()));
        connect(_socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    }

    _socket->write("Welcome To Online Game");
    _socket->flush();
}

void MainWindow::readyRead()
{
    QString accept_message=_socket->readAll();
    accept_message="Client: "+accept_message;
    ui->textEdit->append(accept_message);
}

void MainWindow::on_pushButton_2_clicked()
{

   auto choice = QMessageBox::question(this,"Question","Do you sure want to close game ?");

    switch(choice){
     case QMessageBox::Yes:
           close();
           break;
     case QMessageBox::No:
           break;
     default:
        throw std::logic_error("Wrong your choice");
    }
}

void MainWindow::setDate()
{
    _time=QDateTime::currentDateTime();
    QString setTime=_time.toString("dd/MM/yy");
    ui->label_3->setText(setTime);
}

void MainWindow::on_pushButton_clicked()
{

     setUpServer();
}
