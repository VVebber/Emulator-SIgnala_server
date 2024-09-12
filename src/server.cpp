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
    m_manager = new Manager;
    connect(this, &Server::connectClient, m_manager, &Manager::connectClient);

    m_manager->moveToThread(&
                            m_thread);

    m_thread.start();
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    emit connectClient(socketDescriptor);
}

Server::~Server(){
    m_thread .quit();
    m_thread .wait();
    m_thread.deleteLater();
}

bool Server::isServerRunning() const
{
    return this->isListening();
}
