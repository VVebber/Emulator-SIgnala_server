#include "manager.h"
#include <QMutex>

QMutex mutex;

Manager::Manager() {
    m_idTimerEvent = startTimer(100);
    m_countPoint = -100;
}

Manager::~Manager(){
    killTimer(m_idTimerEvent);
}

void Manager::connectClient(qintptr socketDeskription)
{
    QTcpSocket* socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDeskription);

    Client* client = new Client(socket);
    connect(socket, &QTcpSocket::readyRead, this, &Manager::readToClient);
    connect(client, &Client::dicsonect, this, &Manager::dicsonectClient);
    m_clients.push_back(client);

    qDebug() << "Connect client:" << socket->peerPort() <<"\n";
}

void Manager::timerEvent(QTimerEvent *event)
{
    sendToClient();
}

void Manager::dicsonectClient()
{
    QMutexLocker locker(&mutex);
    Client* client = qobject_cast<Client*>(sender());

    for(qsizetype i = 0; i < m_clients.size(); ++i)
    {
        if(m_clients.at(i) == client)
        {
            m_clients.removeAt(i);
            delete client;

            qDebug() << "Dicsonnect client" <<m_clients.size() <<"\n";
            break;
        }
    }
}

void Manager::readToClient(){
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);

    if(in.status() == QDataStream::Ok)
    {
        QString str;
        in >> str;
        for(qsizetype i = 0; i < m_clients.size(); ++i)
        {
            if(socket == m_clients.at(i)->getsocket())
            {
                m_clients.at(i)->settypeSignal(str);
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

void Manager::sendToClient()
{
    QMutexLocker locker(&mutex);
    if(m_countPoint >= 100)
    {
        m_countPoint = -100;
    }

    QPoint Point(m_countPoint, 0);
    if(m_clients.isEmpty())
    {
        return;
    }
    else
    {
        for(qsizetype i = 0; i < m_clients.size(); ++i)
        {
            if(m_clients.at(i)->getsocket()->isOpen())
            {
                if (m_clients.at(i)->gettypeSignal() == "sin")
                {
                    Point.setY(50 * std::sin(m_countPoint * M_PI / 50));
                }
                else if (m_clients.at(i)->gettypeSignal() == "cos")
                {
                    Point.setY(50 * std::cos(m_countPoint * M_PI / 50));
                }
                else if (m_clients.at(i)->gettypeSignal() == "tan")
                {
                    Point.setY(50 * std::tan(m_countPoint * M_PI / 50));
                }
                else if (m_clients.at(i)->gettypeSignal() == "atan")
                {
                    Point.setY(50 * std::atan(m_countPoint * M_PI / 50));
                }
                else if (m_clients.at(i)->gettypeSignal() == "acos")
                {
                    Point.setY(30 * std::acos(m_countPoint / 150.0));
                }
                else if (m_clients.at(i)->gettypeSignal() == "asin")
                {
                    Point.setY(40 * std::asin(m_countPoint / 100.0));
                }

                QByteArray Data;
                Data.clear();
                QDataStream out(&Data, QIODevice::WriteOnly);
                out.setVersion(QDataStream::Qt_5_15);
                out << Point;
                m_clients.at(i)->getsocket()->write(Data);
                m_clients.at(i)->getsocket()->flush();
                m_countPoint++;
                QThread::msleep(100);
            }
        }
    }
}
