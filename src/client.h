#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class QThread;

class Client : public QObject {
  Q_OBJECT

public:
  Client();
  ~Client();
  QString name() const;

signals:
  void dicsonect();

public slots:
  void connected(qintptr socketDeskription);
  void timerEvent(QTimerEvent *event) override;
  void disconectClient();
  void readToClient();

private:
  void close(bool isDeleteLater);

  QTcpSocket* m_socket;
  QString m_typeSignal;

  int m_idTimerEvent;
  int m_countPoint;

private:
    void sendToClient();
};

#endif
