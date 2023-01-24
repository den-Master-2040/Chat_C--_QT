#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <mainwindow.h>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    //MainWindow *mainwindow;

signals:
    void signaldialog(QString a, QString c);
    void signalregistration(QString d, QString f);
public slots:
    void slot(QString b);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};


#endif // DIALOG_H
