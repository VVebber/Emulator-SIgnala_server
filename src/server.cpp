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

    startWaves();
    m_timerId = startTimer(100);
    m_countPoint = -100;
}



void Server::incomingConnection(qintptr sokerDeskription)
{
    QTcpSocket* socket = new QTcpSocket(this);
    socket->setSocketDescriptor(sokerDeskription);
    connect(socket, &QTcpSocket::readyRead, this, &Server::readToClient);
    connect(socket, &QTcpSocket::disconnected, this, &Server::disconectClient);
    m_clients.insert(socket,"cos");

    qDebug() <<"Connect client, port" << socket;
}

Server::~Server(){
    killTimer(m_timerId);

}

bool Server::isServerRunning() const
{
    return this->isListening();
}

void Server::readToClient()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);

    if(in.status() == QDataStream::Ok)
    {
        QString str;
        in >> str;

        for(auto i = m_clients.begin(); i != m_clients.end(); ++i)
        {
            if(i.key() == socket)
            {
                i.value() = str;
            }
        }

        qDebug() <<"Получен запрос: "<< str;
    }
    else
    {
        qDebug() <<"Ошибка запроса.";
    }
}

void Server::disconectClient()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    if (socket)
    {
        for(auto i = m_clients.begin(); i != m_clients.end(); ++i)
        {
            if(i.key() == socket)
            {
                i.key()->close();
                i.key()->deleteLater();
                i = m_clients.erase(i);
                break;
            }
        }
    }
}
//time

void Server::timerEvent(QTimerEvent *event){
    sendToClient();
}

void Server::sendToClient()
{
    if(m_clients.size() != 0)
    {
        if(m_countPoint >= 100){
            m_countPoint = -100;
        }
        QPoint Point(m_countPoint, 0);
        for(auto i = m_clients.begin(); i != m_clients.end(); i++)
        {
            if(!i.key()->isOpen())
            {
                continue;
            }

            if (i.value() == "sin")
            {
                Point.setY(50 * std::sin(m_countPoint * M_PI / 50));
            }
            else if (i.value() == "cos")
            {
                Point.setY(50 * std::cos(m_countPoint * M_PI / 50));
            }
            else if (i.value() == "tan")
            {
                Point.setY(50 * std::tan(m_countPoint * M_PI / 50));
            }
            else if (i.value() == "atan")
            {
                Point.setY(50 * std::atan(m_countPoint * M_PI / 50));
            }
            else if (i.value() == "acos")
            {
                Point.setY(30 * std::acos(m_countPoint / 150.0));
            }
            else if (i.value() == "asin")
            {
                Point.setY(40 * std::asin(m_countPoint / 100.0));
            }

            QByteArray Data;
            QDataStream out(&Data, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_15);
            out << Point;
            i.key()->write(Data);
            i.key()->flush();
        }
        m_countPoint++;
    }
}
