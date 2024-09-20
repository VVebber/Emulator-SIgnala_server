#include "server.h"
#include "manager.h"
#include <iostream>

#include <QSysInfo>
#include <QCoreApplication>
#include <QThread>

#ifdef Q_OS_LINUX
#include <signal.h>
#endif

void signal(int s)
{
  std::cout<<"exit from signal" << std::endl;
  QCoreApplication::instance()->quit();
}


int main(int argc, char *argv[])
{
  qDebug() <<QThread::currentThreadId() <<"start";
  QCoreApplication a(argc, argv);
  qRegisterMetaType<qintptr>("qintptr");
  Manager &instance = Manager::getInstance();

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

#ifdef Q_OS_LINUX
  signal(SIGINT,signal);
  signal(SIGTERM,signal);
#endif

  Server server(port);
  server.startServer();

  QObject::connect(&a, &QCoreApplication::aboutToQuit, &server, &Server::finishServer);
  QObject::connect(&a, &QCoreApplication::aboutToQuit, &instance, &Manager::closeManager);

  int result = a.exec();

  Manager::resetInstance();
  qDebug()<<"exit";

  return result;
}
