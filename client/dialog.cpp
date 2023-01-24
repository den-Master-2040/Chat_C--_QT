#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //mainwindow = new MainWindow;
   // mainwindow->show();



}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::slot(QString b)
{
    char proverka[] = "login true";
    if(b == proverka) {
    close();
    };
}

void Dialog::on_pushButton_clicked()
{
    emit signaldialog(ui->lineEdit->text(),ui->lineEdit_2->text());
}


void Dialog::on_pushButton_2_clicked()
{
     emit signalregistration(ui->lineEdit_3->text(),ui->lineEdit_4->text());
}

