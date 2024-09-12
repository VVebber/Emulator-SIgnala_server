#ifndef MANAGER_H
#define MANAGER_H
#include "client.h"

class Manager : public QObject
{
    Q_OBJECT

public:
    Manager();
    ~Manager();

public slots:
    void timerEvent(QTimerEvent *event) override;
    void connectClient(qintptr socketDeskription);
    void readToClient();
    void dicsonectClient();

private:
    QList<Client*> m_clients;
    int m_idTimerEvent;
    int m_countPoint;

private:
    void sendToClient();

};

#endif // MANAGER_H
