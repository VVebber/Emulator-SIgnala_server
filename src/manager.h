#ifndef MANAGER_H
#define MANAGER_H
#include "client.h"

class Manager : public QObject
{
  Q_OBJECT

public:
  static Manager* getManager();
  Manager(const Manager&) = delete;
  void operator=(const Manager&) = delete;
  ~Manager();

public slots:
  void timerEvent(QTimerEvent *event) override;
  void connectClient(qintptr socketDeskription);
  void readToClient();
  void dicsonectClient();

  // singletone - паттерн одиночка c++

private:
  static Manager* sm_manager;
  QList<Client*> m_clients;
  int m_idTimerEvent;
  int m_countPoint;

private:
  Manager();
  void sendToClient();
};

#endif // MANAGER_H
