#include <protocoljson.h>
#include <protocolxml.h>
#include <command.h>
#include "client.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDataStream>
#include <QTcpServer>
#include <QThread>
#include <QPoint>
#include <QList>
#include <cmath>



#include <netinet/tcp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>

Client::Client(QString typeProtocol)
{
  m_typeSignal = "sin";
  m_countPoint = -100;
  m_idTimerEvent = 0;

  if(typeProtocol == "JSON")
  {
    m_messageProtocol = new ProtocolJSON;
  }
  else if(typeProtocol == "XML")
  {
    m_messageProtocol = new ProtocolXML;
  }
}

void Client::connected(qintptr socketDeskription)
{
  m_socket = new QTcpSocket;
  m_socket->setSocketDescriptor(socketDeskription);
  connect(m_socket, &QTcpSocket::readyRead, this, &Client::readFromClient);
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

void Client::readFromClient()
{
  m_messageProtocol->addData(m_socket->readAll());
  Command command = m_messageProtocol->decode(m_messageProtocol->getNextCommand());
  while(command.isValid())
  {
    switch (command.getCommandType())
    {
    case Command::CommandType::TypeSignalSetting:
      handlerTypeSignal(command);
      break;
    case Command::CommandType::DrawStartOrFin:
      handlerDrawPoint(command);
      break;
    default:
      qDebug() <<"the request is not understood";
      break;
    }
    command = m_messageProtocol->decode(m_messageProtocol->getNextCommand());
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
    disconnect(m_socket, &QTcpSocket::readyRead, this, &Client::readFromClient);
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
  QList<int> points;
  if(m_countPoint == 100)
  {
    m_countPoint = -100;
  }

  for(int i = 0; i < 10; i++)
  {
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
      m_countPoint++;

      points.push_back(Point.x());
      points.push_back(Point.y());
    }
  }
  if(points.size() != 0)
  {
    QByteArray a = m_messageProtocol->encode(Command::CommandType::PointGraphing, QVariant::fromValue(points));
    QByteArray b = m_messageProtocol->encode(Command::CommandType::PointGraphing, "");

    m_socket->write(a);
    m_socket->write(a);
    // m_socket->write(b);
  }
}

void Client::handlerDrawPoint(Command command){
  if(m_idTimerEvent != 0)
  {
    killTimer((m_idTimerEvent));
    m_idTimerEvent = 0;
    qDebug() <<"handlDrawPoint:  DeleteTimerEvent";
  }
  else
  {
    m_idTimerEvent = startTimer(400);
    qDebug() <<"handlDrawPoint:  CreateTimerEvent";
  }
}

void Client::handlerTypeSignal(Command command)
{
  m_typeSignal = command.getVariableData();
  qDebug() <<"Receive request: "<< m_typeSignal;
  m_countPoint = -100;
}
