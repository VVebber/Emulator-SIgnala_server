#include "manager.h"
#include "server.h"

Server::Server(qint16 nPort)
{
  m_port = nPort;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
  emit connectClient(socketDescriptor);
}

bool Server::startServer()
{
  if(isListening())
  {
    qDebug() << "the server is already running";
    return false;
  }
  else if(!listen(QHostAddress::Any, m_port))
  {
    qDebug() <<"Unable to start server.";
    return false;
  }
  else
  {
    qDebug() << "Server is running, port"<< m_port;
    connect(this, &Server::connectClient, &Manager::getInstance(), &Manager::connectClient);

    return true;
  }
}

void Server::finishServer(){
  qDebug() <<QThread::currentThreadId() <<"closeServer";
  close();

  disconnect(this, &Server::connectClient, &Manager::getInstance(), &Manager::connectClient);
}

Server::~Server(){
  qDebug() << QThread::currentThreadId() <<"destructorServer";
}
