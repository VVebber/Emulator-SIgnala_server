#include "server.h"

Server::Server(qint16 nPort)
{
    if (!this->listen(QHostAddress::Any, nPort))
        qDebug() <<"Невозможно запустить сервер.";
    else qDebug() << "Сервер запущен, порт"<< nPort;
}

void Server::incomingConnection(qintptr sokerDeskription){
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(sokerDeskription);
    connect(socket, &QTcpSocket::readyRead, this, &Server::ReadToClient);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    qDebug() <<"Поднлючен пользователь:" <<sokerDeskription;

    Wave = new WaveSimulator(socket);
    connect(socket, &QTcpSocket::disconnected, Wave, &WaveSimulator::terminate);

}

Server::~Server(){
    if(socket)
    delete socket;
    delete Wave;
}

bool Server::isServerRunning() const{
    return this->isListening();
}

void Server::ReadToClient(){
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);

    if(in.status() == QDataStream::Ok){
        QString str;
        in >> str;

        qDebug() <<"Получен запрос: "<< str;
        if(Wave->isRunning())
            Wave->terminate();
        Wave->settypeSignal(str);
        Wave->start();
    } else
        qDebug() <<"Ошибка запроса.";
}
