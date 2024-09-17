#ifndef MANAGER_H
#define MANAGER_H

#include <QMutex>
#include "client.h"

class Manager : public QObject
{
  Q_OBJECT

public:
  static Manager& getInstance();
  static void freeInstance();

  Manager(const Manager&) = delete;
  ~Manager();
  void operator=(const Manager&) = delete;
  void closeManager();
  void startThread();

public slots:
  void connectClient(qintptr socketDeskription);
  void dicsonectClient();

private:
  QList<Client*> m_clients;
  QThread m_thread;
  QMutex m_mutex;

private:
  Manager();
};

#endif // MANAGER_H
