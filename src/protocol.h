#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QJsonDocument>
#include <QDomDocument>

class QJsonObject;
class QTcpSocket;
class Command;

class Protocol : public QJsonDocument, public QDomDocument
{
public:
  Protocol() = default;

  virtual QByteArray encode(QJsonObject message) = 0;
  //virtual QByteArray encode(QDomDocument message) = 0;

  virtual Command decode(QByteArray messageCode) = 0;
  //virtual QDomDocument decode(QDomDocument message) = 0;

  virtual ~Protocol() = default;
};

#endif // PROTOCOL_H
