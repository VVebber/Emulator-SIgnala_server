#include "server.h"

#include <QCoreApplication>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qRegisterMetaType<qintptr>("qintptr");
    Manager::getInstance()->start();

    Server* server = nullptr;

    qDebug() << argv[0];
    int Port = QString(argv[a.arguments().indexOf("-p") + 1]).toInt();
    server = new Server(Port != 0? Port : 1024);
    server->connection();

    return a.exec();
}
