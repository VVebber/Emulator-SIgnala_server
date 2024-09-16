#include "server.h"

#include <QCoreApplication>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qRegisterMetaType<qintptr>("qintptr");
    Manager::getInstance()->start();

    Server* server = nullptr;

    if (argc != 3)
    {
      return 1;
    }

    QStringList args = a.arguments();
    int port = 1024;
    int portArgIndex = args.indexOf("-p");
    if(portArgIndex < 0 || portArgIndex == 2)
    {
      return 2;
    }
    else
    {
      QString portStr = args[portArgIndex + 1];
      bool isOk = true;
      int argPort = portStr.toInt(&isOk);

      if (!isOk)
      {
        return 3;
      }

      port = argPort;
    }


    server = new Server(port);
    server->connection();

    return a.exec();
}
