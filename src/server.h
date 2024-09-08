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

    void readToClient();

    void sendToClient();

    void disconectClient();

    void timerEvent(QTimerEvent*event) override;
signals:
    void startWaves();

private:
    /*TCP/IP*/

    QByteArray m_data;

    qint16 m_port;

    int m_timerId;
    int m_countPoint;

    QMultiMap<QTcpSocket*,QString> m_clients;
};

#endif // SERVER_H
