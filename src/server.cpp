#include "server.h"
Server::Server(qint16 nPort)
{
  if (!this->listen(QHostAddress::Any, nPort))
  {
    qDebug() <<"Unable to start server.";
  }
  else
  {
    qDebug() << "Server is running, port"<< nPort;
  }
  m_manager = Manager::getManager();
  connect(this, &Server::connectClient, m_manager, &Manager::connectClient);
  m_manager->moveToThread(&m_thread);

  m_thread.start();
}

void Server::incomingConnection(qintptr socketDescriptor)
{
  emit connectClient(socketDescriptor);
}

Server::~Server(){
  m_thread .quit();
  m_thread .wait();
}

bool Server::isServerRunning() const
{
  return this->isListening();
}
