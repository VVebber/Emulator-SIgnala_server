#include "server.h"

#include <QCoreApplication>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qRegisterMetaType<qintptr>("qintptr");

    Manager::getInstance()->start();

    Server* server = nullptr;
    server = new Server(QString(argv[a.arguments().indexOf("-p") + 1]).toInt());
    server->connection();

    return a.exec();
}
