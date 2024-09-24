#include "protocoljson.h"
#include "command.h"

#include <QJsonObject>
#include <QTcpSocket>

ProtocolJSON::ProtocolJSON() {}

QByteArray ProtocolJSON::encode(QJsonObject message)
{
  QJsonDocument code(message);
  return code.toJson();
}

Command ProtocolJSON::decode(QByteArray messageCode)
{
  QJsonDocument message;
  message = QJsonDocument::fromJson(messageCode);
  Command command(message["command"].toString());
  if(message.object().contains("VariableData"))
  {
    command.setVariableData(message["VariableData"].toString());
  }
  return command;
}
