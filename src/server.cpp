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
    m_wave = new Client;
    m_wave->moveToThread(&m_thread);

    connect(&m_thread, &QThread::started, m_wave, &Client::start);
    connect(this, &Server::connectClient, m_wave, &Client::connectClient);
    connect(&m_thread, &QThread::finished, m_wave, &QThread::deleteLater);
    connect(&m_thread, &QThread::finished, &m_thread, &Client::deleteLater);


    m_thread.start();
}



void Server::incomingConnection(qintptr socketDeskription)
{
    m_wave->setsokerDeskription(socketDeskription);
    emit connectClient();
}

Server::~Server(){

}

bool Server::isServerRunning() const
{
    return this->isListening();
}
