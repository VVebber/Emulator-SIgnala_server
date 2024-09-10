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

    Client* s = new Client;
    s->moveToThread(&m_thread);

    connect(&m_thread, &QThread::started, s, &Client::start);
    connect(this, &Server::connectClient, s, &Client::connectClient);
    connect(s,&Client::dicsonect, s, &Client::deleteLater);
    // connect(&m_thread, &QThread::finished, s, &Client::deleteLater);
    // connect(&m_thread, &QThread::finished, &m_thread, &QThread::deleteLater);

    s->setsocketDeskription(socketDeskription);
    emit connectClient();

    m_Clients.push_back(s);

    m_thread.start();

}

Server::~Server(){
    m_thread.exit();
    m_thread.deleteLater();
    //delete m_Clients;
}

bool Server::isServerRunning() const
{
    return this->isListening();
}
