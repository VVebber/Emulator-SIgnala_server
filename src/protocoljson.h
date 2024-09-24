#ifndef PROTOCOLJSON_H
#define PROTOCOLJSON_H

#include "protocol.h"

class ProtocolJSON : public Protocol
{
public:
  ProtocolJSON();

  QByteArray encode(QJsonObject message) override;
  Command decode(QByteArray messageCode) override;

};

#endif // PROTOCOLJSON_H
