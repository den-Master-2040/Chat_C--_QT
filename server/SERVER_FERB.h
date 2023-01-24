#ifndef SERVER_FERB_H
#define SERVER_FERB_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <vector>
#include <QTime>
#include <cstdlib>
class Server : public QTcpServer {

    Q_OBJECT
public:
    Server();
    QTcpSocket *socket;
private:
  QVector <QTcpSocket*> Sockets;
  QVector <QString> clients;
  QByteArray Data; //буфер данных которые передаются
  void SendToClientS(QString str, int i);
  void SendToClient(QString str);
void registration(QString str);
  quint16 nextBlockSize;

public slots:
  void incomingConnection(qintptr socketDescriptor);
  void slotReadyRead();
  void logining(QString d);
  void chatting(QString str);
};
#endif // SERVER_FERB_H
