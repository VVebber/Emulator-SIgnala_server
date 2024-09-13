#include "server.h"
Server::Server(qint16 nPort)
{
    m_port = nPort;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    emit connectClient(socketDescriptor);
}

bool Server::connection()
{
    if(isListening()){
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
        return true;
    }
}

void Server::setting()
{
    connect(this, &Server::connectClient, Manager::getInstance(), &Manager::connectClient);
    Manager::getInstance()->moveToThread(&m_thread);

    m_thread.start();
}

Server::~Server()
{
    m_thread.quit();
    m_thread.wait();

    QTcpServer::close();

    disconnect(this, &Server::connectClient, Manager::getInstance(), &Manager::connectClient);
    Manager::freeInstance();
}
