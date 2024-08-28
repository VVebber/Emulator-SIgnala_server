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
        server = new Server(ui->spinPort->value());
        QString state = server->isServerRunning() ? "1" : "0";
        ui->StartServer->setProperty("state", state);
        style()->polish(ui->StartServer);
        ui->StartServer->update();
    }
}

