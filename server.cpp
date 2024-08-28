#include "server.h"

Server::Server(qint16 nPort) {
    if (!this->listen(QHostAddress::Any, nPort))
        QMessageBox::critical(0, "Ошибка сервера", "Невозможно запустить сервер:" + this->errorString());
    else qDebug() << "Сервер запущен, порт"<< nPort;
}

void Server::incomingConnection(qintptr sokerDeskription){
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(sokerDeskription);
    connect(socket, &QTcpSocket::readyRead, this, &Server::ReadToClient);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    qDebug() <<"Поднлючен пользователь:" <<sokerDeskription;
}

Server::~Server(){
    delete socket;
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

        SendToClient(str);
    } else
        qDebug() <<"Ошибка запроса.";
}

void Server::SendToClient(QString &TypeSignal) {
    qDebug() <<"Отправка запроса: "<< TypeSignal;
    for (int x = -100; x < 100; x++) {
        qreal y = 0;
        if (TypeSignal == "sin") {
            y = 50 * std::sin(x * M_PI / 50);
        } else if (TypeSignal == "cos") {
            y = 50 * std::cos(x * M_PI / 50);
        } else if (TypeSignal == "tan") {
            y = 50 * std::tan(x * M_PI / 50);
        } else if (TypeSignal == "atan") {
            y = 50 * std::atan(x * M_PI / 50);
        } else if (TypeSignal == "acos") {
            y = 50 * std::acos(x / 100.0);
        } else if (TypeSignal == "asin") {
            y = 50 * std::asin(x / 100.0);
        }

        if (std::abs(y) > 500) {
            y = std::copysign(500.0, y);
        }

        QPoint Point(x,y);

        QByteArray Data;
        Data.clear();
        QDataStream out(&Data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_2);
        out << Point;
        socket->write(Data);
        socket->flush();


        QThread::msleep(100);
    }
}
