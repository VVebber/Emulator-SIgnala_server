#include "protocolxml.h"
#include "command.h"

#include <QString>
#include <QSequentialIterable>

ProtocolXML::ProtocolXML()
{

}


QByteArray ProtocolXML::encode(QString command, QVariant data)
{

  QDomDocument XMLDocument;
  QDomElement root = XMLDocument.createElement("task");

  QDomElement commandXML = XMLDocument.createElement("command");
  QDomText commandXMLText = XMLDocument.createTextNode(command);

  commandXML.appendChild(commandXMLText);
  root.appendChild(commandXML);
  if(data.isValid())
  {
    QDomElement variableDataXML = XMLDocument.createElement("VariableData");
    root.appendChild(variableDataXML);
    if (data.canConvert<int>())
    {
      QDomText variableDataXMLText = XMLDocument.createTextNode(data.toString());
      variableDataXML.appendChild(variableDataXMLText);
    }
    else if (data.canConvert<double>())
    {
      QDomText variableDataXMLText = XMLDocument.createTextNode(data.toString());
      variableDataXML.appendChild(variableDataXMLText);
    }
    else if (data.canConvert<QString>())
    {
      QDomText variableDataXMLText = XMLDocument.createTextNode(data.toString());
      variableDataXML.appendChild(variableDataXMLText);
    }
    else if (data.canConvert<QVariantList>())
    {
      QSequentialIterable iterable = data.value<QSequentialIterable>();
      for(const QVariant& v : iterable)
      {
        QDomElement listItem = XMLDocument.createElement("Item");
        QDomText variableDataXMLText = XMLDocument.createTextNode(v.toString());
        listItem.appendChild(variableDataXMLText);
        variableDataXML.appendChild(listItem);
      }
    }
    else
    {
      qDebug()<< "ProtocolXLM encode error";
    }
  }
  XMLDocument.appendChild(root);

  qDebug()<<XMLDocument.toByteArray(0);

  qDebug()<<root.elementsByTagName("VariableData").at(0).toElement().childNodes().at(0).toText().data();


  QByteArray wwwww = XMLDocument.toByteArray(0);
  wwwww.append("\n");
  return wwwww;
}


Command ProtocolXML::decode(QByteArray messageCode)
{
  QDomDocument main;
  main.setContent(messageCode);
  QDomElement box = main.documentElement().toElement();

  QString command  = box.elementsByTagName("command").at(0).toElement().childNodes().at(0).toText().data();
  QString VariableData = box.elementsByTagName("VariableData").at(0).toElement().childNodes().at(0).toText().data();

  Command com(command);
  if(!VariableData.isEmpty())
  {
    com.setVariableData(VariableData);
  }
  return com;
}
