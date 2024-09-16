#include "server.h"
Server::Server(qint16 nPort)
{
    qDebug() <<QThread::currentThreadId()<<"constructor server";
    connect(this, &Server::connectClient, Manager::getInstance(), &Manager::connectClient);

    m_port = nPort;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    qDebug() <<QThread::currentThreadId()<<" incomingConnection server";
    emit connectClient(socketDescriptor);
}

bool Server::connection()
{
    if(isListening()){
        qDebug() <<QThread::currentThreadId()<< "the server is already running";
        return false;
    }
    else if(!listen(QHostAddress::Any, m_port))
    {
        qDebug() <<QThread::currentThreadId()<<"Unable to start server.";
        return false;
    }
    else
    {
        qDebug() <<QThread::currentThreadId()<< "Server is running, port"<< m_port;
        return true;
    }
}

Server::~Server()
{
    QTcpServer::close();

    disconnect(this, &Server::connectClient, Manager::getInstance(), &Manager::connectClient);
    Manager::freeInstance();
    delete this;

}
