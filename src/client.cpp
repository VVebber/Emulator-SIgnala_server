#include "client.h"

Client::Client(qintptr socketDeskription)
{
  m_typeSignal = "sin";
  m_socket = new QTcpSocket;
  m_socket->setSocketDescriptor(socketDeskription);
  connect(m_socket, &QTcpSocket::readyRead, this, &Client::readToClient);
  connect(m_socket, &QTcpSocket::disconnected, this, &Client::disconectClient);

  m_idTimerEvent = startTimer(200);
}

Client::~Client()
{
  close();
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
  close();
  emit dicsonect();
}

void Client::readToClient(){
  QDataStream in(m_socket);
  in.setVersion(QDataStream::Qt_5_15);

  if(in.status() == QDataStream::Ok)
  {
    QString str;
    in >> str;
    m_typeSignal = str;

    qDebug() <<"Receive request: "<< str;
  }
  else
  {
    qDebug() <<"Request Error.";
  }
}

void Client::close()
{
  killTimer(m_idTimerEvent);

  if(m_socket)
  {
    disconnect(m_socket, &QTcpSocket::readyRead, this, &Client::readToClient);
    disconnect(m_socket, &QTcpSocket::disconnected, this, &Client::disconectClient);

    m_socket->close();
    m_socket->deleteLater();
    m_socket = nullptr;
  }
}

void Client::timerEvent(QTimerEvent *event)
{
  sendToClient();
}

void Client::sendToClient(){
  if(m_countPoint >= 100)
  {
    m_countPoint = -100;
  }

  QPoint Point(m_countPoint, 0);
  if(m_socket->isOpen())
  {
    if (m_typeSignal == "sin")
    {
      Point.setY(50 * std::sin(m_countPoint * M_PI / 50));
    }
    else if (m_typeSignal == "cos")
    {
      Point.setY(50 * std::cos(m_countPoint * M_PI / 50));
    }
    else if (m_typeSignal == "tan")
    {
      Point.setY(50 * std::tan(m_countPoint * M_PI / 50));
    }
    else if (m_typeSignal == "atan")
    {
      Point.setY(50 * std::atan(m_countPoint * M_PI / 50));
    }
    else if (m_typeSignal == "acos")
    {
      Point.setY(30 * std::acos(m_countPoint / 150.0));
    }
    else if (m_typeSignal == "asin")
    {
      Point.setY(40 * std::asin(m_countPoint / 100.0));
    }

    QByteArray Data;
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << Point;
    m_socket->write(Data);
    m_socket->flush();
    m_countPoint++;
  }
}
