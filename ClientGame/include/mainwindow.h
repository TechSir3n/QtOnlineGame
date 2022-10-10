#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QProcess>
#include <QDialogButtonBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


struct Player{
    QString _name;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void SetUpClient();
    void setButtons();



public:
    void setUpGame();

    void checkWin();

    void firstPlayerWin();

    void secondPlayerWin();

    void DrawWon();

public slots:
    void sendMessage();

    void readReady();

    void newConnection();

    void restartGame();

    void GiveUpOrNot();

    void  SetNamePlayers();



private slots:
    void on_firstButton_clicked();

    void on_secondButton_clicked();

    void on_thirdButton_clicked();

    void on_fourth_clicked();

    void on_fiveth_clicked();

    void on_sixth_clicked();

    void on_seventh_clicked();

    void on_eigtinth_clicked();

    void on_nineth_clicked();

private:
    QTcpSocket* socket_client{nullptr};

    int turnPlayer{0};
    int board[9]={0,0,0,0,0,0,0,0,0};

    Player first_player;
    Player second_player;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
