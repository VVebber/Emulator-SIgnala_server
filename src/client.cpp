#include "client.h"

Client::Client()
{
    m_countPoint = -100;
    m_idTimeEveent = 0;
}

Client::~Client()
{
    killTimer(m_idTimeEveent);
}

void Client::connectClient()
{
    QTcpSocket* socket = new QTcpSocket;
    socket->setSocketDescriptor(m_socketDeskription);

    connect(socket, &QTcpSocket::readyRead, this, &Client::readToClient);
    connect(socket, &QTcpSocket::disconnected, this, &Client::disconectClient);

    m_socket.insert(socket, "cos");

    qDebug() <<"Connect client";
    qDebug() <<"count"<< m_socket.size();

}

void Client::setsokerDeskription(qintptr socketDeskription)
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

        for(auto i= m_socket.begin(); i!= m_socket.end(); ++i)
        {
            if(i.key() == socket)
            {
                i.value() = str;
                break;
            }
        }

        qDebug() <<"Receive request: "<< str;
    }
    else
    {
        qDebug() <<"Request Error.";
    }
}

void Client::disconectClient()
{
    QTcpSocket* soket = qobject_cast<QTcpSocket*>(sender());

    for(auto i= m_socket.begin(); i!= m_socket.end(); ++i)
    {
        if(i.key() == soket)
        {
            i.key()->close();
            i.key()->deleteLater();
            i = m_socket.erase(i);
            break;
        }

    }
}

void Client::start()
{
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
    if(m_socket.size() == 0)
    {
        return;
    }
    for(auto i= m_socket.begin(); i!= m_socket.end(); ++i)
    {
        if(i.key()->isOpen())
        {

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
            Data.clear();
            QDataStream out(&Data, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_15);
            out << Point;
            i.key()->write(Data);
            i.key()->flush();


            m_countPoint++;

            QThread::msleep(100);
        }
    }
}
