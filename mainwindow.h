#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include<QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void myfunction();
       void connected();
    // void newConnection();
          void disconnected();
       void bytesWritten(qint64 bytes);
       void readyRead();
//void sendtoserver();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket1;
    QTimer *timer;
};

#endif // MAINWINDOW_H
