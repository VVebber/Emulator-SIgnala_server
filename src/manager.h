#ifndef MANAGER_H
#define MANAGER_H

#include "client.h"
#include <QMutex>
#include <QThread>

class Manager : public QObject
{
  Q_OBJECT

public:
  static Manager& getInstance();
  static void createInstance();
  static void freeInstance();
  static void resetInstance();

  Manager(const Manager&) = delete;
  ~Manager();
  void operator=(const Manager&) = delete;


public slots:
  void connectClient(qintptr socketDeskription);
  void dicsonectClient();
  void closeManager();

signals:
  void finished();

private:
  static Manager* sm_instance;
  QList<Client*> m_clients;
  QThread m_thread;
  QMutex m_mutex;

private:
  Manager();
};

#endif // MANAGER_H
