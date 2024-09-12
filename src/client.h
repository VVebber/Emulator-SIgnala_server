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
    //get
    QTcpSocket* getsocket();
    QString gettypeSignal() const;
    //set
    void settypeSignal(QString newtypeSignal);
signals:
    void dicsonect();

public:
    void disconectClient();

private:
    QTcpSocket* m_socket;
    QString m_typeSignal;

};

#endif
