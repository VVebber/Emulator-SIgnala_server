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


protected:/*PROTECTED*/

public:/*PUBLIC*/
    Client();
    ~Client();

    void connectClient();
    void setsokerDeskription(qintptr sokerDeskription);

public slots:
    void readToClient();
    void start();
    void timerEvent(QTimerEvent *event) override;
    void disconectClient();

private:/*PRIVATE*/
    QMap<QTcpSocket*, QString> m_socket;
    qintptr m_socketDeskription;

    int m_countPoint;
    int m_idTimeEveent;

private:
    void  sendToClient();
};

#endif
