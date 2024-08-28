#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,server(nullptr)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (server) {
        delete server;
    }
}

void MainWindow::on_StartServer_clicked()
{
    if (!server) {
        QString state = "";
        server = new Server(ui->spinPort->value());
        if(server->isServerRunning()){
            state = "1";
            qDebug()<<"Сервер поднлючен";

            // connect(server, &Server::DrawOutServer, this, &MainWindow::DrawInBrowser);
        }
        else {
            q   Debug()<<"Произошли проблемы с подключением к серверу";
            state = "0";
            delete server;
            server = nullptr;
        }
        ui->StartServer->setProperty("state", state);
        style()->polish(ui->StartServer);
        ui->StartServer->update();
    }
}

