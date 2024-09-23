#include "client.h"

#include <QDataStream>
#include <QTcpServer>
#include <QThread>
#include <QPoint>
#include <cmath>

#include <netinet/tcp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>

Client::Client()
{
  m_typeSignal = "sin";
  m_countPoint = -100;
  m_idTimerEvent = startTimer(200);
}

void Client::connected(qintptr socketDeskription)
{
  m_socket = new QTcpSocket;
  m_socket->setSocketDescriptor(socketDeskription);
  connect(m_socket, &QTcpSocket::readyRead, this, &Client::readToClient);
  connect(m_socket, &QTcpSocket::disconnected, this, &Client::disconectClient);

  int intSocketDescriptor = m_socket->socketDescriptor();

  int keepAlive = 1;
  if (setsockopt(intSocketDescriptor, SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof(keepAlive)) == -1)
  {
    qWarning() << "1Failed to set keep_alive."<<strerror(errno);
  }

  int keepIdle = 10;
  if (setsockopt(intSocketDescriptor, IPPROTO_TCP, TCP_KEEPIDLE, &keepIdle, sizeof(keepIdle)) == -1)
  {
    qWarning() << "2Failed to set TCP_KEEPIDLE."<<strerror(errno);
  }

  int keepInterval = 5;
  if (setsockopt(intSocketDescriptor, IPPROTO_TCP, TCP_KEEPINTVL, &keepInterval, sizeof(keepInterval)) == -1)
  {
    qWarning() << "3Failed to set TCP_KEEPINTVL."<<strerror(errno);
  }

  int keepCount = 2;
  if (setsockopt(intSocketDescriptor, IPPROTO_TCP, TCP_KEEPCNT, &keepCount, sizeof(keepCount)) == -1)
  {
    qWarning() << "4Failed to set TCP_KEEPCNT."<<strerror(errno);
  }
}

Client::~Client()
{
  qDebug() << "destructor";
  close(false);
}

QString Client::name() const
{
  if (m_socket)
  {
    return m_socket->peerAddress().toString();
  }

  return QString("Client(closed)");
}

void Client::disconectClient()
{
  qDebug() << "disconectClient";
  close(true);
  emit dicsonect();
}

void Client::readToClient()
{
  QDataStream in(m_socket);
  in.setVersion(QDataStream::Qt_5_15);

  if(in.status() == QDataStream::Ok)
  {
    QString str;
    in >> str;
    m_typeSignal = str;
    m_countPoint = -100;

    qDebug() <<"Receive request: "<< str;
  }
  else
  {
    qDebug() <<"Request Error.";
  }
}

void Client::close(bool isDeleteLater)
{
  if(m_idTimerEvent != 0)
  {
    killTimer((m_idTimerEvent));
    m_idTimerEvent = 0;
  }

  if(m_socket)
  {
    qDebug() <<this<< "close socket";
    disconnect(m_socket, &QTcpSocket::readyRead, this, &Client::readToClient);
    disconnect(m_socket, &QTcpSocket::disconnected, this, &Client::disconectClient);

    m_socket->close();
    if(isDeleteLater)
    {
      m_socket->deleteLater();
    }
    else
    {
      delete m_socket;
    }
    m_socket = nullptr;
  }
  else
  {
    qDebug() <<"the socket has already been closed";
  }
}

void Client::timerEvent(QTimerEvent *event)
{
  sendToClient();
}

void Client::sendToClient()
{
  const float PI = 3.14;

  if(m_countPoint >= 100)
  {
    m_countPoint = -100;
  }

  QPoint Point(m_countPoint, 0);
  if(m_socket->isOpen())
  {
    if (m_typeSignal == "sin")
    {
      Point.setY(50 * std::sin(m_countPoint * PI / 50));
    }
    else if (m_typeSignal == "cos")
    {
      Point.setY(50 * std::cos(m_countPoint * PI / 50));
    }
    else if (m_typeSignal == "tan")
    {
      Point.setY(50 * std::tan(m_countPoint * PI / 50));
    }
    else if (m_typeSignal == "atan")
    {
      Point.setY(50 * std::atan(m_countPoint * PI / 50));
    }
    else if (m_typeSignal == "acos")
    {
      Point.setY(30 * std::acos(m_countPoint / 150.0));
    }
    else if (m_typeSignal == "asin")
    {
      Point.setY(40 * std::asin(m_countPoint / 100.0));
    }

    QByteArray data;
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << Point;
//    if(m_socket->state())
    int errorWhite = m_socket->write(data);
    if(errorWhite == -1){
      qDebug()<<"errorWhite";
    }
    m_socket->flush();
    m_countPoint++;
  }
}
