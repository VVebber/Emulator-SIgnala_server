#ifndef MANAGER_H
#define MANAGER_H

#include <QMutex>
#include "client.h"

class Manager : public QObject
{
  Q_OBJECT

public:
  static Manager* getInstance();
  static void freeInstance();

  Manager(const Manager&) = delete;
  ~Manager();
  void operator=(const Manager&) = delete;

public slots:
  void connectClient(qintptr socketDeskription);
  void dicsonectClient();

private:
  static Manager* m_instance;
  QList<Client*> m_clients;
  QMutex m_mutex;

private:
  Manager() = default;
};

#endif // MANAGER_H
