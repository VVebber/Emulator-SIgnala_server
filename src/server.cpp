#include "server.h"
Server::Server(qint16 nPort)
{
  if (!listen(QHostAddress::Any, nPort))
  {
    qDebug() <<"Unable to start server.";
    return;
  }

  qDebug() << "Server is running, port"<< nPort;

  connect(this, &Server::connectClient, Manager::getInstance(), &Manager::connectClient);
  Manager::getInstance()->moveToThread(&m_thread);

  m_thread.start();
}

void Server::incomingConnection(qintptr socketDescriptor)
{
  emit connectClient(socketDescriptor);
}

Server::~Server(){
  m_thread .quit();
  m_thread .wait();

  QTcpServer::close();

  disconnect(this, &Server::connectClient, Manager::getInstance(), &Manager::connectClient);
  Manager::freeInstance();
}

bool Server::isServerRunning() const
{
  return isListening();
}
