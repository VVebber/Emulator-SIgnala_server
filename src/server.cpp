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

   // m_thread = new QThread;

}



void Server::incomingConnection(qintptr sokerDeskription)
{
    //WaveSimulator *client = new WaveSimulator;
    //client->connectClient(socketDescriptor());
    //m_clients.push_back(client);

    WaveSimulator* wave = new WaveSimulator;
    wave->setsokerDeskription(sokerDeskription);

     wave->moveToThread(&m_thread);

    connect(&m_thread, &QThread::started, wave, &WaveSimulator::start);
  //  connect(wave, &WaveSimulator::finished, wave, &WaveSimulator::deleteLater);
    connect(&m_thread, &QThread::finished, &m_thread, &QThread::deleteLater);
    connect(&m_thread, &QThread::finished, wave, &WaveSimulator::deleteLater);

    m_thread.start();
}

Server::~Server(){
   // killTimer(m_timerId);
}

bool Server::isServerRunning() const
{
    return this->isListening();
}
