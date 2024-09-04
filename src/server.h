#ifndef SERVER_H
#define SERVER_H

#include "wavesimulator.h"

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(qint16 nPort);
    ~Server();


    bool isServerRunning() const;

public slots:
    void incomingConnection(qintptr sokerDeskription) override;

    void ReadToClient();

private:
    /*TCP/IP*/
    QTcpSocket* socket;
    QByteArray Data;
    qint16 nPort;
    /*=====*/

    WaveSimulator* Wave;
};

#endif // SERVER_H
