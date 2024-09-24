#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class QThread;
class Protocol;
class Command;

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

  Protocol* m_messageProtocol;

  int m_idTimerEvent;
  int m_countPoint;

private:
    void sendToClient();
    void handlTypeSignal(Command command);
    void handlDrawPoint(Command command);
};

#endif
