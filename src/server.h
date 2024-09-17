#ifndef SERVER_H
#define SERVER_H

#include "manager.h"
#include <QTimerEvent>
#include <QMultiMap>


class Server : public QTcpServer
{
  Q_OBJECT

public:
  Server(qint16 nPort = 1024);
  ~Server();
  bool connection();
  void closeServer();

public slots:
  void incomingConnection(qintptr sokerDeskription) override;

signals:
  void connectClient(qintptr socketDeskription);

private:
  qint16 m_port;
};

#endif // SERVER_H
