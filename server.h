#ifndef SERVER_H
#define SERVER_H
#include <QMessageBox>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(qint16 nPort);


    bool isServerRunning() const;

public slots:
    void incomingConnection(qintptr sokerDeskription) override;

    void ReadToClient();
private:
    /*TCP/IP*/
    QTcpSocket* socket;
    QByteArray Data;
    qint16 nPort;

    void SendToClient(QString &TypeSignal);


};

#endif // SERVER_H
