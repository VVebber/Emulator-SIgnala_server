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
    Client(QTcpSocket* socket);

    QTcpSocket* getsocket(){
        return m_socket;
    }

    QString gettypeSignal() const{
        return m_typeSignal;
    }

signals:
    void dicsonect();

public:
    void disconectClient();

private:
    QTcpSocket* m_socket;
    QString m_typeSignal;

};

#endif
