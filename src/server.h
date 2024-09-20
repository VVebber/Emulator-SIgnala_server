#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Server : public QTcpServer
{
  Q_OBJECT

public:
  Server(qint16 nPort = 1024);
  ~Server();
  bool startServer();
  void finishServer();

public slots:
  void incomingConnection(qintptr sokerDeskription) override;

signals:
  void connectClient(qintptr socketDeskription);

private:
  qint16 m_port;
};

#endif // SERVER_H
