#include "manager.h"
#include <QMutex>

Manager* Manager::sm_instance = nullptr;

Manager::Manager()
{
  qDebug() <<QThread::currentThreadId() << Q_FUNC_INFO;
  connect(this, &Manager::finished, &m_thread, &QThread::quit, Qt::DirectConnection);// TODO qq
  moveToThread(&m_thread);
  m_thread.start();
}

Manager& Manager::getInstance()
{
  if(sm_instance == nullptr)
    sm_instance = new Manager;
  return *sm_instance;
}

Manager::~Manager()
{
  qDebug() <<QThread::currentThreadId() << Q_FUNC_INFO;
  m_thread.quit();
}

void Manager::resetInstance()
{
  qDebug() <<QThread::currentThreadId() << Q_FUNC_INFO;
  sm_instance->m_thread.wait();
  delete sm_instance;
}

void Manager::closeManager()
{
  if(!m_thread.isRunning())
  {
    return;
  }
  qDebug() <<QThread::currentThreadId() << Q_FUNC_INFO;
  QMutexLocker locker(&m_mutex);
  for(int i = 0; i < m_clients.size(); ++i)
  {
    disconnect(m_clients.at(i), &Client::dicsonect, this, &Manager::dicsonectClient);
    delete m_clients.at(i);
  }
  m_clients.clear();
  emit finished();
}

void Manager::connectClient(qintptr socketDeskription)
{
  Client* client = new Client;
  client->connected(socketDeskription);
  connect(client, &Client::dicsonect, this, &Manager::dicsonectClient);
  m_clients.push_back(client);

  qDebug() <<QThread::currentThreadId() << "Connect client:" << client->name();
}

void Manager::dicsonectClient()
{
  QMutexLocker locker(&m_mutex);
  Client* client = qobject_cast<Client*>(sender());

  if (m_clients.removeOne(client))
  {
    qDebug() << "Dicsonnect client" << client->name();
  }
  else
  {
    qWarning() << "Unknown client" << client->name() <<"\n";
  }
  delete client;
}
