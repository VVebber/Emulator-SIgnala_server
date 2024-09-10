#include "client.h"

Client::Client()
{
    m_countPoint = -100;
    typeSignal = "cos";
    m_socket = nullptr;
    qRegisterMetaType<qintptr>("S");
}

Client::~Client() {}

void Client::connectClient(qintptr socketDeskription)
{
    m_socket = new QTcpSocket;
    m_socket->setSocketDescriptor(m_socketDeskription);

    connect(m_socket, &QTcpSocket::readyRead, this, &Client::readToClient);
    connect(m_socket, &QTcpSocket::disconnected, this, &Client::disconectClient);
}

void Client::setsocketDeskription(qintptr socketDeskription)
{
    m_socketDeskription = socketDeskription;
}

void Client::readToClient()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);

    if(in.status() == QDataStream::Ok)
    {
        QString str;
        in >> str;

        typeSignal = str;
        qDebug() <<"Receive request: "<< str;
    }
    else
    {
        qDebug() <<"Request Error.";
    }
}

void Client::disconectClient()
{
    m_socket->close();
    m_socket->deleteLater();
    m_socket = nullptr;
    emit dicsonect();
}

void Client::start()
{
    qDebug()<<"ss";
    startTimer(200);
}

void Client::timerEvent(QTimerEvent* event)
{
    sendToClient();
}

void Client::sendToClient()
{    
    if(m_countPoint >= 100){
        m_countPoint = -100;
    }
    QPoint Point(m_countPoint, 0);

    if(m_socket == nullptr){
        return;
    }

    if(m_socket->isOpen())
    {
        if (typeSignal == "sin")
        {
            Point.setY(50 * std::sin(m_countPoint * M_PI / 50));
        }
        else if (typeSignal == "cos")
        {
            Point.setY(50 * std::cos(m_countPoint * M_PI / 50));
        }
        else if (typeSignal == "tan")
        {
            Point.setY(50 * std::tan(m_countPoint * M_PI / 50));
        }
        else if (typeSignal == "atan")
        {
            Point.setY(50 * std::atan(m_countPoint * M_PI / 50));
        }
        else if (typeSignal == "acos")
        {
            Point.setY(30 * std::acos(m_countPoint / 150.0));
        }
        else if (typeSignal == "asin")
        {
            Point.setY(40 * std::asin(m_countPoint / 100.0));
        }

        QByteArray Data;
        Data.clear();
        QDataStream out(&Data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_15);
        out << Point;
        m_socket->write(Data);
        m_socket->flush();
        m_countPoint++;
        QThread::msleep(100);
    }
}

