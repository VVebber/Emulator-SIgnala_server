#ifndef CLIENT_H
#define CLIENT_H

#include <QMessageBox>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <cmath>

class Client : public QObject {
    Q_OBJECT

public:
    Client();
    ~Client();

    void connectClient();
    void setsocketDeskription(qintptr socketDeskription);

public slots:
    void readToClient();
    void start();
    void timerEvent(QTimerEvent *event) override;
    void disconectClient();

signals:
    void dicsonect();

private:
    QTcpSocket* m_socket;
    qintptr m_socketDeskription;
    QString typeSignal;
    int m_countPoint;

private:
    void  sendToClient();
};

#endif
