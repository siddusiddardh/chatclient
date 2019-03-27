#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTime>
QTcpSocket *socket=NULL;
QString time_text;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    ui->textEdit_2->setReadOnly(true);
    ui->textEdit->setAlignment(Qt::AlignRight);
    ui->textEdit->setFocus(Qt::OtherFocusReason);


    socket = new QTcpSocket(this);
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(myfunction()));
    timer->start(2000);
      socket->connectToHost("192.168.0.49", 8421);
    // connect(socket, SIGNAL(newConnection()),this,SLOT(newConnection()));

  // connect(socket, SIGNAL(newConnection()),this,SLOT(newConnection()));
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
   connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    qDebug() << "connecting...";

    // this is not blocking call


    // we need to wait...
    if(!socket->waitForConnected(5000))
    { socket = new QTcpSocket(this);
        qDebug() << "Error: " << socket->errorString();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::myfunction()
{
 QTime time=QTime::currentTime();
 time_text=time.toString("hh:mm:ss");
 disconnect(timer,SIGNAL(timeout()),this,SLOT(myfunction()));
}
void MainWindow::connected()
{
  qDebug() << "connected...";

  //socket->write("data from client");
}

void MainWindow::disconnected()
{
  qDebug() << "disconnected...";
}

void MainWindow::bytesWritten(qint64 bytes)
{


   qDebug() << bytes << " bytes written...";
}

void MainWindow::readyRead()
{
  myfunction();
  qDebug() << "reading...";

  // read the data from the socket

  QByteArray arry_dat = socket->readAll();
  qDebug() << arry_dat;
  ui->textEdit_2->setFontPointSize(25);
  ui->textEdit_2->append(arry_dat);
  ui->textEdit_2->setFontPointSize(8);
  ui->textEdit_2->append(time_text);
  //ui->textEdit->append("");
}

void MainWindow::on_pushButton_clicked()
{
    QString data=ui->lineEdit_2->text();
    ui->textEdit->setFontPointSize(25);
    ui->textEdit->append(data);
    ui->textEdit->setFontPointSize(8);
    ui->textEdit->append(time_text);
   // ui->textEdit_2->append("");
    socket->write(data.toLocal8Bit());
    socket->waitForBytesWritten(3000);
    ui->lineEdit_2->clear();
}
