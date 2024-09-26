#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QJsonDocument>
#include <QDomDocument>

class QJsonObject;
class QTcpSocket;
class QByteArray;
class Command;

class Protocol : public QJsonDocument, public QDomDocument
{
public:
  Protocol() = default;

//  template <class T1>
  virtual QByteArray encode(QString command, QVariant data) = 0;
  //virtual QByteArray encode(QDomDocument message) = 0;

  virtual Command decode(QByteArray messageCode) = 0;
  //virtual QDomDocument decode(QDomDocument message) = 0;

  virtual ~Protocol() = default;
};

#endif // PROTOCOL_H
