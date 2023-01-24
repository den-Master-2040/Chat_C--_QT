#include "SERVER_FERB.h"
#include <QTextStream>
#include <QDataStream>
#include <QTextStream>
#include <QFile>
#include <cstdlib>
#include <stdlib.h>
Server::Server()
{

    if(this->listen(QHostAddress::AnyIPv4, 2323))
    {
       qDebug() << "start";
    }
    else
    {
        qDebug() << "error";
    }
    nextBlockSize = 0;
}

        //метод работы с прищедшими пользователями
void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket,&QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket,&QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    Sockets.push_back(socket);
    qDebug() << "client connected" << socketDescriptor;



}

        //метод работы с прищедшими сообщениями
void Server::slotReadyRead() {
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_9);
    if(in.status() == QDataStream::Ok)
    {
       qDebug() << "read...";
       QString str;
       in >> str;
       qDebug() << str;
       for(int i = 0; i < (int)sizeof(str); i++ ) {
           if(str [i] == "+"){
               for(int i = 0; i < (int)sizeof(str); i++ ) {
                   if(str [i] == "-"){
                       for(int i = 0; i < (int)sizeof(str); i++ ) {
                           if(str [i] == "="){
                               for(int i = 0; i < (int)sizeof(str); i++ ) {
                                   if(str [i] == "i"){
                                       for(int i = 0; i < (int)sizeof(str); i++ ) {
                                           if(str [i] == "s"){
                                               registration(str);

                                               SendToClient("login true");
                                               qDebug() << "registration";

                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
           else
           {
              logining(str);
              break;
           }
        }

    if (str[1] == "2"){
       chatting(str);
    }


    }

}




void Server::chatting(QString str) {
           QChar l = str[0];
           int s = l.digitValue();

           SendToClientS(str,s);

}


void Server::logining(QString str)
{

        //Чтение файла

    QTextStream out(stdout);

    // Создаем объект
    QFile file("D:\\users.txt");

    // С помощью метода open() открываем файл в режиме чтения
    if (!file.open(QIODevice::ReadOnly)) {
      qWarning("Cannot open file for reading"); // если файл не найден, то выводим предупреждение и завершаем выполнение программы

    }

    // Создаем входящий поток, из которого будут считываться данные, и связываем его с нашим файлом
    QTextStream in(&file);

    // Считываем файл строка за строкой

    while (!in.atEnd()) { // метод atEnd() возвращает true, если в потоке больше нет данных для чтения
      QString line = in.readLine(); // метод readLine() считывает одну строку из потока
      //out << line << endl;

      if(str == line) {
            qDebug() << "login true";
            SendToClient("login true");
            break;
      }

    }

    // Закрываем файл
    file.close();
}

void Server::registration(QString str) {

    QTextStream out(stdout);

      // Создаем объект класса QFile и связываем его с указанным именем файла
      QString filename = "D:\\users.txt";
      QFile file(filename);

       // Открываем файл в режиме "Только для записи"
       if (file.open(QIODevice::Append)) {
         QTextStream out(&file); // поток записываемых данных направляем в файл

         // Для записи данных в файл используем оператор <<
         //file.seek(10);
         str.chop(5);


         out << str << endl;


       } else {

         qWarning("Could not open file");
       }

       // Закрываем файл
       file.close();

}
void Server::SendToClientS(QString str,int i)
{
    Data.clear();                                           // очистка уже  созданного массива
    QDataStream out(&Data,QIODevice::WriteOnly);            // информация на вывод, только для записи. Для массива выше строкой
    out.setVersion(QDataStream::Qt_5_9);                    // версия
    out << quint16(0) << QTime::currentTime() << str;       // записываем в строку массив Data
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));         // далее массив в сокет, данные отправляются
    Sockets[i]->write(Data);


}
void Server::SendToClient(QString str)
{
    Data.clear();                                           // очистка уже  созданного массива
    QDataStream out(&Data,QIODevice::WriteOnly);            // информация на вывод, только для записи. Для массива выше строкой
    out.setVersion(QDataStream::Qt_5_9);                    // версия
    out << quint16(0) << QTime::currentTime() << str;       // записываем в строку массив Data
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    //socket->write(Data);                                  // далее массив в сокет, данные отправляются
    for ( int i = 0; i < Sockets.size();i++)
    {
        Sockets[i]->write(Data);
    }

}









