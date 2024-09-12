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
  QTcpSocket* getSocket();
  QString getTypeSignal() const;
  //set
  void setTypeSignal(QString newtypeSignal);

signals:
  void dicsonect();

public:
  void disconectClient();

private:
  QTcpSocket* m_socket;
  QString m_typeSignal;
};

#endif
