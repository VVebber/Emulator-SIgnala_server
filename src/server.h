#ifndef SERVER_H
#define SERVER_H

#include "wavesimulator.h"
#include <QTimerEvent>
#include <QMultiMap>

#include <vector>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(qint16 nPort);
    ~Server();


    bool isServerRunning() const;

public slots:
    void incomingConnection(qintptr sokerDeskription) override;

signals:
    void startWaves();

private:
    /*TCP/IP*/
    qint16 m_port;

    QList<WaveSimulator*> m_clients;

    QThread m_thread;
};

#endif // SERVER_H
