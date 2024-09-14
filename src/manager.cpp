#include "manager.h"
#include <QMutex>

Manager* Manager::m_instance = nullptr;

Manager* Manager::getInstance(){
    if(m_instance == nullptr)
    {
        m_instance = new Manager();
    }
    return m_instance;
}

void Manager::freeInstance()
{
    if(m_instance != nullptr)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

Manager::~Manager()
{
    QMutexLocker locker(&m_mutex);
    for(int i = 0; i < m_clients.size(); ++i)
    {
        QMetaObject::invokeMethod(m_clients.at(i), "deleteClient", Qt::QueuedConnection);
        //emit m_clients.at(i)->disconectClient();
        disconnect(m_clients.at(i), &Client::dicsonect, this, &Manager::dicsonectClient);
        //delete m_clients[i];

        //m_clients.at(i)->deleteLater();
        qDebug() <<"desManager" << m_clients.at(i);
    }
    m_clients.clear();
}

void Manager::connectClient(qintptr socketDeskription)
{
    Client* client = new Client;
    client->connection(socketDeskription);
    connect(client, &Client::dicsonect, this, &Manager::dicsonectClient);
    m_clients.push_back(client);

    qDebug() << "Connect client:" << client->name() <<"\n";
}

void Manager::dicsonectClient()
{
    QMutexLocker locker(&m_mutex);
    Client* client = qobject_cast<Client*>(sender());

    if (m_clients.removeOne(client))
    {
        qDebug() << "Dicsonnect client" << client->name() <<"\n";
    }
    else
    {
        qWarning() << "Unknown client" << client->name() <<"\n";
    }
    delete client;
}
