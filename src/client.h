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

  QString name() const;

signals:
  void dicsonect();

public slots:
  //void disabling();
  void connection(qintptr socketDeskription);
  void timerEvent(QTimerEvent *event) override;
  void disconectClient();
  void readToClient();
  void deleteClient();

private:  
  void close();

  QTcpSocket* m_socket;
  QString m_typeSignal;

  int m_idTimerEvent;
  int m_countPoint;

private:
    void sendToClient();
};

#endif
