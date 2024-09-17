#include "server.h"
#include <iostream>

#include <QSysInfo>
#include <QCoreApplication>


#ifdef Q_OS_LINUX
#define LInux
#endif

#ifdef LInux
#include <signal.h>
#endif
void signal(int s){
  std::cout<<"exit from signal";
  QCoreApplication::instance()->quit();
}


int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  qRegisterMetaType<qintptr>("qintptr");
  Manager::getInstance().startThread();

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

#ifdef LInux
  signal(SIGINT,signal);
  signal(SIGTERM,signal);
#endif
  server = new Server(port);
  server->connection();

  QObject::connect(&a, &QCoreApplication::aboutToQuit, server, &Server::close);
  QObject::connect(&a, &QCoreApplication::aboutToQuit, server, &Server::deleteLater);
  QObject::connect(&a, &QCoreApplication::aboutToQuit, &Manager::getInstance(), &Manager::deleteLater);

  return a.exec();
}
