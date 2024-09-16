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

void Manager::start()
{
    m_instance->moveToThread(&m_thread);
    m_thread.start();
}

Manager::~Manager()
{
    QMutexLocker locker(&m_mutex);
    for(int i = 0; i < m_clients.size(); ++i)
    {
        //        emit deletedeleteClient();

        disconnect(m_clients.at(i), &Client::dicsonect, this, &Manager::dicsonectClient);
        delete m_clients.at(i);
        QThread::sleep(1);
    }
    m_clients.clear();

    m_thread.quit();
    m_thread.wait();
}

void Manager::connectClient(qintptr socketDeskription)
{
    Client* client = new Client;
    client->connection(socketDeskription);
    connect(client, &Client::dicsonect, this, &Manager::dicsonectClient);
    connect(this, &Manager::deletedeleteClient, client, &Client::deleteClient);
    m_clients.push_back(client);

    qDebug() << QThread::currentThreadId() << "Connect client:" << client->name();
}

void Manager::dicsonectClient()
{
    QMutexLocker locker(&m_mutex);
    Client* client = qobject_cast<Client*>(sender());

    if (m_clients.removeOne(client))
    {
        qDebug() << QThread::currentThreadId() << "Dicsonnect client" << client->name();
    }
    else
    {
        qWarning() << QThread::currentThreadId() << "Unknown client" << client->name();
    }
    delete client;
}
