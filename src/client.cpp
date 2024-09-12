#include "client.h"

Client::Client(QTcpSocket* socket)
{
  m_typeSignal = "sin";
  m_socket = socket;

  connect(m_socket, &QTcpSocket::disconnected, this, &Client::disconectClient);
}

void Client::disconectClient()
{
  m_socket->close();
  m_socket->deleteLater();
  m_socket = nullptr;
  emit dicsonect();
}


QTcpSocket* Client::getSocket(){
  return m_socket;
}

QString Client::getTypeSignal() const{
  return m_typeSignal;
}

void Client::setTypeSignal(QString newtypeSignal){
  m_typeSignal = newtypeSignal;
}
