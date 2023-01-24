#include "mainwindow.h"
#include "ui_mainwindow.h"
 char buff[20];
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)



{

    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead,this, &MainWindow::slotReadyRead);
    connect(socket,&QTcpSocket::disconnected,socket, &QTcpSocket::deleteLater);
    nextBlockSize = 0;
    Dialog *dialog;
    dialog = new Dialog;
    dialog->show();

    connect(this,&MainWindow::signal,dialog,&Dialog::slot);
    connect(dialog,&Dialog::signaldialog,this,&MainWindow::slotdialog);

    connect(dialog,&Dialog::signalregistration,this,&MainWindow::slotregistration);

    socket->connectToHost("192.168.0.67", 2323);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

      i = 0;
}

void MainWindow::on_pushButton_2_clicked()
{

      i = 1;
}
void MainWindow::on_pushButton_3_clicked()
{
      i = 2;

}

void MainWindow::on_pushButton_9_clicked()
{
    QString s = QString::number(i);
    QString ss = "2";
    SendToServer(s + ss +ui->lineEdit->text());
    ui->textBrowser->append(ui->lineEdit->text());
}
void MainWindow::SendToServer(QString str)
{
    Data.clear();
    QDataStream out(&Data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out  <<str;


    socket->write(Data);
                                      //очистка лайнэдита после отправки сообщения

}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_9);
    if(in.status()==QDataStream::Ok)
    {
       /* QString str;
        in >> str;
        ui->textBrowser->append(str);*/
        for(;;)
        {
            if(nextBlockSize == 0)
            {
               if(socket->bytesAvailable() < 2)
               {
                  break;
               }
               in >> nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize)
            {
             break;
            }

            if(nextBlockSize == 10) {
             //socket->disconnectFromHost();
             //socket->connectToHost("192.168.0.67", 2324);
            }
            if(nextBlockSize == 16) {
             ui->textBrowser->append("nextBlockSize = 16");
            }





            QString str;
            QTime time;
            in >> time >>str;
            nextBlockSize = 0;
             // перенос пришедшего сообщения в текстбраузер
            char logintrue[] = "login true";
            if(str == logintrue) {
              emit signal(logintrue);





                if(socket->waitForConnected())
                {
                  ui->label_2->setText("подключено!");
                }
             }
            str.remove(0,2);
            ui->textBrowser->append(time.toString() + " " + str);
        }
    }
    else
    {
       ui->textBrowser->append("read error");
    }
}




void MainWindow::slotdialog(QString a, QString c)// передача этой информации из DIALOG в NAINWINDOW
{
    QString dl = a+c;
    SendToServer(dl);
}

void MainWindow::slotregistration(QString d, QString f)// передача этой информации из DIALOG в NAINWINDOW
{
    ui->label_2->setText("подключено!");
    QString buff = "+-=is";
    QString s = d+f+buff;


    SendToServer(s);
}






void MainWindow::on_lineEdit_returnPressed()
{
    QString s = QString::number(i);
    QString ss = "2";
    SendToServer(s + ss +ui->lineEdit->text());
    ui->textBrowser->append(ui->lineEdit->text());
}

void MainWindow::on_textBrowser_anchorClicked(const QUrl &arg1)
{

}







