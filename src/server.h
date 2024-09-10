#ifndef SERVER_H
#define SERVER_H

#include "client.h"
#include <QTimerEvent>
#include <QMultiMap>


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
    void connectClient();

private:
    /*TCP/IP*/
    qint16 m_port;

    client* m_wave;

    QThread m_thread;
};

#endif // SERVER_H
