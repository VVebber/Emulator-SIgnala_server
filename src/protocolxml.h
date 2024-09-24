#ifndef PROTOCOLXML_H
#define PROTOCOLXML_H

#include "protocol.h"

class ProtocolXML: public Protocol
{
public:
  ProtocolXML();

  // QDomDocument encode(QDomDocument data) override;
  // QDomDocument decode(QDomDocument code) override;

  //void write(QDomDocument code) override;
};

#endif // PROTOCOLXML_H
