#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QListWidget>
#include <QList>
#include <QPushButton>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public :
    void setUpServer();
    void setDate();

public slots:
    void newConnection();
    void readyRead();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    QTcpServer *_server{nullptr};
    QTcpSocket *_socket{nullptr};
    QDateTime _time;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
