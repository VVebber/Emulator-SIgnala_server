#include "server.h"
Server::Server(qint16 nPort)
{
    if (!this->listen(QHostAddress::Any, nPort))
    {
        qDebug() <<"Невозможно запустить сервер.";
    }
    else
    {
        qDebug() << "Сервер запущен, порт"<< nPort;
    }
    m_Clients = new Client;
    m_Clients->moveToThread(&m_thread);

    connect(&m_thread, &QThread::started, m_Clients, &Client::start);
    connect(this, &Server::connectClient, m_Clients, &Client::connectClient);
    connect(&m_thread, &QThread::finished, m_Clients, &QThread::deleteLater);
    connect(&m_thread, &QThread::finished, &m_thread, &Client::deleteLater);

    m_thread.start();
}



void Server::incomingConnection(qintptr socketDeskription)
{
    m_Clients->setsokerDeskription(socketDeskription);
    emit connectClient();
}

Server::~Server(){
    delete m_Clients;
}

bool Server::isServerRunning() const
{
    return this->isListening();
}
