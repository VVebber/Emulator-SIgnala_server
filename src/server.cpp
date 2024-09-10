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
    m_wave = new WaveSimulator;
    m_wave->moveToThread(&m_thread);

    connect(&m_thread, &QThread::started, m_wave, &WaveSimulator::start);
    connect(this, &Server::connectClient, m_wave, &WaveSimulator::connectClient);
    connect(&m_thread, &QThread::finished, m_wave, &QThread::deleteLater);
    connect(&m_thread, &QThread::finished, &m_thread, &WaveSimulator::deleteLater);


    m_thread.start();
}



void Server::incomingConnection(qintptr sokerDeskription)
{
    m_wave->setsokerDeskription(sokerDeskription);
    emit connectClient();
}

Server::~Server(){

}

bool Server::isServerRunning() const
{
    return this->isListening();
}
