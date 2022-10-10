#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Online Game");

    SetUpClient();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetUpClient()
{
    socket_client=new QTcpSocket(this);

    socket_client->connectToHost("127.0.0.1",12345);

    connect(socket_client,SIGNAL(readyRead()),this,SLOT(readReady()));

    connect(socket_client,SIGNAL(connected()),this,SLOT(newConnection()));

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(sendMessage()));

    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(sendMessage()));

    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(SetNamePlayers()));

}

void MainWindow::setButtons()
{

    ui->firstButton->setText("*");
    ui->secondButton->setText("*");
    ui->thirdButton->setText("*");

    ui->fourth->setText("*");
    ui->fiveth->setText("*");
    ui->sixth->setText("*");

    ui->seventh->setText("*");
    ui->eigtinth->setText("*");
    ui->nineth->setText("*");
}

void MainWindow::setUpGame()
{
    srand(time(nullptr));

    turnPlayer=rand()%2+1;

    setButtons();

    connect(ui->pushButton_26,SIGNAL(clicked()),this,SLOT(restartGame()));
    connect(ui->pushButton_27,SIGNAL(clicked()),this,SLOT(GiveUpOrNot()));

}

void MainWindow::SetNamePlayers()
{
    SetUpClient();
    setUpGame();

    second_player._name= QInputDialog::getText(this,tr("FirstPlayer"),tr("Enter your name "));

    first_player._name=QInputDialog::getText(this,tr("SecondPlayer"),tr("Enter your name "));


    if(!second_player._name.size()==0){
        ui->label_6->setText(second_player._name);
    }else{
        second_player._name="Player1";
    }

    if(!first_player._name.size()==0){
       ui->label_5->setText(first_player._name);
     }else{
        first_player._name="Player2";
    }

}


void MainWindow::checkWin()
{
    if(board[0]==1 && board[1]==1 && board[2]==1){
        firstPlayerWin();
    }
    else if(board[3]==1 && board[4]==1 && board[5]==1){
        firstPlayerWin();
    }
    else if(board[6]==1 && board[7]==1 && board[8]==1){
        firstPlayerWin();
    }

    if(board[0]==1 && board[3]==1 && board[6]==1){
        firstPlayerWin();
    }
    else if(board[0]==1 &&  board[4]==1 && board[8]==1){
        firstPlayerWin();
    }
    else if(board[1]==1 && board[4]==1 && board[7]==1){
        firstPlayerWin();
    }
    else if(board[2]==1 && board[5]==1 && board[8]==1){
        firstPlayerWin();
    }
    else if(board[2]==1 && board[4]==1 && board[6]==1){
        firstPlayerWin();
    }


    if(board[0]==2 && board[1]==2 && board[2]==2){
        secondPlayerWin();
    }
    else if(board[3]==2 && board[4]==2 && board[5]==2){
        secondPlayerWin();
    }
    else if(board[1]==2 && board[4]==2 && board[7]==2){
        secondPlayerWin();
    }
    else if(board[6]==2 && board[7]==2 && board[8]==2){
        secondPlayerWin();
    }
    else if(board[2]==2 && board[5]==2 && board[8]==2){
        secondPlayerWin();
    }

    if(board[0]==2 && board[3]==2 && board[6]==2){
        secondPlayerWin();
    }
    else if(board[0]==2 &&  board[4]==2 && board[8]==2){
        secondPlayerWin();
    }
    else if(board[2]==2 && board[4]==2 && board[6]==2){
        secondPlayerWin();
    }

    else if(board[0]!=0 && board[1]!=0 && board[2]!=0 && board[3]!=0 && board[4]!=0 &&
            board[5]!=0 && board[6]!=0 && board[7]!=0 && board[8]!=0) { DrawWon(); }

}

void MainWindow::firstPlayerWin()
{
    for(int i=0;i<9;i++){
        board[i]=0;
    }

    QMessageBox box;
    box.setWindowTitle("Game Over !");
    box.setText(ui->label_5->text()+ " " + " Win");
    box.exec();

    turnPlayer=1;

    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());


}

void MainWindow::secondPlayerWin()
{
    for(int i=0;i<9;i++){
        board[i]=0;
    }

    QMessageBox box;
    box.setWindowTitle("Game Over !");
    box.setText(ui->label_6->text()+ "  " + "Win");
    box.exec();

    turnPlayer=2;

    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

}

void MainWindow::DrawWon()
{
    QMessageBox box;
    box.setWindowTitle("Game Over !");
    box.setText("Draw Won");
    box.exec();

    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void MainWindow::sendMessage()
{
    QString message=ui->lineEdit->text();
    message="I: "+message;
    socket_client->write(ui->lineEdit->text().toLatin1());

    ui->textEdit->append(message);

    ui->lineEdit->clear();
}

void MainWindow::newConnection()
{
    socket_client->write("Client successfuly connected to server !");
}

void MainWindow::restartGame()
{
   auto choice=QMessageBox::question(this,"Qustions","Do you sure want to restart game?");

   switch(choice){

   case QMessageBox::Yes:
       qApp->quit();
       QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
       SetNamePlayers();
       break;

   case QMessageBox::No:
       break;

   default:
       throw std::logic_error("Enter Wrong choice");
   }
}

void MainWindow::GiveUpOrNot()
{
    auto choice = QMessageBox::question(this,"Question","Do you sure want to give up ?");

   switch(choice){
      case QMessageBox::Yes:
            qApp->quit();
            QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
            break;
      case QMessageBox::No:
            break;
      default:
         throw std::logic_error("Wrong your choice");
     }
}


void MainWindow::readReady()
{
    QString message_server=socket_client->readAll();
    message_server="Server: "+message_server;
    ui->textEdit->append(message_server);
}


void MainWindow::on_firstButton_clicked()
{
   if(turnPlayer==1 && board[0]==0){
       board[0]=1;
       ui->firstButton->setText("X");
       turnPlayer=2;
   } else if(turnPlayer==1 && board[0]!=0){ }


   else if(turnPlayer==2 && board[0]==0)
   {
       board[0]=2;
       ui->firstButton->setText("O");
       turnPlayer=1;
   } else if(turnPlayer==2 && board[0]!=0){ }

   checkWin();
}


void MainWindow::on_secondButton_clicked()
{
    if(turnPlayer==1 && board[1]==0){
        board[1]=1;
        ui->secondButton->setText("X");
        turnPlayer=2;
    } else if(turnPlayer==1 && board[1]!=0) { }

    else if(turnPlayer==2 && board[1]==0){
        board[0]=2;
        ui->secondButton->setText("O");
        turnPlayer=1;
    } else if(turnPlayer==2 && board[1]!=0) { }

    checkWin();
}


void MainWindow::on_thirdButton_clicked()
{
    if(turnPlayer==1 && board[2]==0){
        board[2]=1;
        ui->thirdButton->setText("X");
        turnPlayer=2;
    } else if(turnPlayer==1 && board[2]!=0) { }

    else if(turnPlayer==2 && board[2]==0){
        board[2]=2;
        ui->thirdButton->setText("O");
        turnPlayer=1;
    } else if(turnPlayer==2 && board[2]!=0) { }

    checkWin();
}


void MainWindow::on_fourth_clicked()
{
    if(turnPlayer==1 && board[3]==0){
        board[3]=1;
        ui->fourth->setText("X");
        turnPlayer=2;
    } else if(turnPlayer==1 && board[3]!=0) { }

    else if(turnPlayer==2 && board[3]==0){
        board[3]=2;
        ui->fourth->setText("O");
        turnPlayer=1;
    } else if(turnPlayer==2 && board[3]!=0) { }

    checkWin();
}


void MainWindow::on_fiveth_clicked()
{
    if(turnPlayer==1 && board[4]==0){
        board[4]=1;
        ui->fiveth->setText("X");
        turnPlayer=2;
    } else if(turnPlayer==1 && board[4]!=0) { }

    else if(turnPlayer==2 && board[4]==0){
        board[4]=2;
        ui->fiveth->setText("O");
        turnPlayer=1;
    } else if(turnPlayer==2 && board[4]!=0) { }

    checkWin();
}


void MainWindow::on_sixth_clicked()
{
    if(turnPlayer==1 && board[5]==0){
        board[5]=1;
        ui->sixth->setText("X");
        turnPlayer=2;
    } else if(turnPlayer==1 && board[5]!=0) { }

    else if(turnPlayer==2 && board[5]==0){
        board[5]=2;
        ui->sixth->setText("O");
        turnPlayer=1;
    } else if(turnPlayer==2 && board[5]!=0) { }

    checkWin();
}


void MainWindow::on_seventh_clicked()
{

    if(turnPlayer==1 && board[6]==0){
        board[6]=1;
        ui->seventh->setText("X");
        turnPlayer=2;
    } else if(turnPlayer==1 && board[6]!=0) { }

    else if(turnPlayer==2 && board[6]==0){
        board[6]=2;
        ui->seventh->setText("O");
        turnPlayer=1;
    } else if(turnPlayer==2 && board[6]!=0) { }

    checkWin();
}


void MainWindow::on_eigtinth_clicked()
{
    if(turnPlayer==1 && board[7]==0){
        board[7]=1;
        ui->eigtinth->setText("X");
        turnPlayer=2;
    } else if(turnPlayer==1 && board[7]!=0) { }

    else if(turnPlayer==2 && board[7]==0){
        board[7]=2;
        ui->eigtinth->setText("O");
        turnPlayer=1;
    } else if(turnPlayer==2 && board[7]!=0) { }

    checkWin();
}


void MainWindow::on_nineth_clicked()
{
    if(turnPlayer==1 && board[8]==0){
        board[8]=1;
        ui->nineth->setText("X");
        turnPlayer=2;
    } else if(turnPlayer==1 && board[8]!=0) { }

    else if(turnPlayer==2 && board[8]==0){
        board[8]=2;
        ui->nineth->setText("O");
        turnPlayer=1;
    } else if(turnPlayer==2 && board[8]!=0) { }

    checkWin();
}
