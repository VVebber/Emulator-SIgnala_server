#ifndef PROTOCOLXML_H
#define PROTOCOLXML_H

#include "protocol.h"

class ProtocolXML: public Protocol
{
public:
  ProtocolXML();

  QByteArray encode(QString command, QVariant data) override;
  Command decode(QByteArray messageCode) override;
};

#endif // PROTOCOLXML_H
