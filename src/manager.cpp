#include "manager.h"

Manager::Manager() {
    m_idTimerEvent = startTimer(1000);
    m_countPoint = -100;
}

Manager::~Manager(){
    killTimer(m_idTimerEvent);
}

void Manager::connectClient(qintptr socketDeskription){
    QTcpSocket* socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDeskription);

    Client* client = new Client(socket);
    connect(client, &Client::dicsonect, this, &Manager::dicsonectClient);


    m_Clients.push_back(client);

    qDebug() << "Connect client" <<m_Clients.size() <<"\n";
}

void Manager::timerEvent(QTimerEvent *event)
{
    sendToClient();

}

void Manager::dicsonectClient()
{
    Client* client = qobject_cast<Client*>(sender());

    for(qsizetype i = 0; i < m_Clients.size(); ++i)
    {
        if(m_Clients.at(i) == client)
        {
            m_Clients.removeAt(i);
            qDebug() << "Dicsonnect client" <<m_Clients.size() <<"\n";
            break;
        }
    }
}

void Manager::sendToClient()
{

    if(m_countPoint >= 100)
    {
        m_countPoint = -100;
    }

    QPoint Point(m_countPoint, 0);
    if(m_Clients.isEmpty())
    {
        return;
    }
    else
    {
        for(qsizetype i = 0; i < m_Clients.size(); ++i)
        {
            if(m_Clients.at(i)->getsocket() == nullptr)
            {
                continue;
            }
            if(m_Clients.at(i)->getsocket()->isOpen())
            {
                if (m_Clients.at(i)->gettypeSignal() == "sin")
                {
                    Point.setY(50 * std::sin(m_countPoint * M_PI / 50));
                }
                else if (m_Clients.at(i)->gettypeSignal() == "cos")
                {
                    Point.setY(50 * std::cos(m_countPoint * M_PI / 50));
                }
                else if (m_Clients.at(i)->gettypeSignal() == "tan")
                {
                    Point.setY(50 * std::tan(m_countPoint * M_PI / 50));
                }
                else if (m_Clients.at(i)->gettypeSignal() == "atan")
                {
                    Point.setY(50 * std::atan(m_countPoint * M_PI / 50));
                }
                else if (m_Clients.at(i)->gettypeSignal() == "acos")
                {
                    Point.setY(30 * std::acos(m_countPoint / 150.0));
                }
                else if (m_Clients.at(i)->gettypeSignal() == "asin")
                {
                    Point.setY(40 * std::asin(m_countPoint / 100.0));
                }

                QByteArray Data;
                Data.clear();
                QDataStream out(&Data, QIODevice::WriteOnly);
                out.setVersion(QDataStream::Qt_5_15);
                out << Point;
                m_Clients.at(i)->getsocket()->write(Data);
                m_Clients.at(i)->getsocket()->flush();
                m_countPoint++;
                QThread::msleep(100);
            }
        }
    }
}
