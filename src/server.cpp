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
    // m_Clients = new Client;
    // m_Clients->moveToThread(&m_thread);

    // connect(&m_thread, &QThread::started, m_Clients, &Client::start);
    // connect(this, &Server::connectClient, m_Clients, &Client::connectClient);
    // connect(&m_thread, &QThread::finished, m_Clients, &QThread::deleteLater);
    // connect(&m_thread, &QThread::finished, &m_thread, &Client::deleteLater);

    // m_thread.start();
}

void Server::incomingConnection(qintptr socketDeskription)
{
    if(m_thread.isRunning())
    {
        m_thread.quit();
    }

    Client* newClient = new Client;
    newClient->moveToThread(&m_thread);

    connect(&m_thread, &QThread::started, newClient, &Client::start);
    connect(this, &Server::connectClient, newClient, &Client::connectClient);
    connect(s,&Client::dicsonect, newClient, &Client::deleteLater);
    // connect(&m_thread, &QThread::finished, s, &Client::deleteLater);
    // connect(&m_thread, &QThread::finished, &m_thread, &QThread::deleteLater);

    newClient->setsocketDeskription(socketDeskription);
    emit connectClient();

    m_Clients.push_back(newClient);

    m_thread.start();

}

Server::~Server(){
    m_thread .quit();
    m_thread .wait();
    m_thread.deleteLater();
    //delete m_Clients;
}

bool Server::isServerRunning() const
{
    return this->isListening();
}
