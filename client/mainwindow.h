#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "dialog.h"
#include <QMainWindow>
#include <QTcpSocket>
#include <QTime>
#include <dialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //Dialog *dialog;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_returnPressed();

    void on_textBrowser_anchorClicked(const QUrl &arg1);



    void on_pushButton_3_clicked();

    void on_pushButton_9_clicked();

private:
    int i= 0;
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray Data;
    void SendToServer(QString str);

    quint16 nextBlockSize;


signals:
    void signal(QString b);

public slots:
    void slotReadyRead();
    void slotdialog(QString a, QString c);
    void slotregistration(QString d, QString f);


};



#endif // MAINWINDOW_H
