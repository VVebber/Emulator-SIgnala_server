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


QTcpSocket* Client::getsocket(){
    return m_socket;
}

QString Client::gettypeSignal() const{
    return m_typeSignal;
}

void Client::settypeSignal(QString newtypeSignal){
    m_typeSignal = newtypeSignal;
}
