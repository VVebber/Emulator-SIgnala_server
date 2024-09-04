#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,pServer(nullptr)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (pServer) {
        delete pServer;
    }
}

void MainWindow::on_StartServer_clicked()
{
    if (!pServer) {
        QString state = "";
        pServer = new Server(ui->spinPort->value());
        if(pServer->isServerRunning()){
            state = "1";
            qDebug()<<"Сервер поднлючен";

            // connect(server, &Server::DrawOutServer, this, &MainWindow::DrawInBrowser);
        }
        else {
            qDebug()<<"Произошли проблемы с подключением к серверу";
            state = "0";
            delete pServer;
            pServer = nullptr;
        }
        ui->StartServer->setProperty("state", state);
        style()->polish(ui->StartServer);
        ui->StartServer->update();
    }
}

