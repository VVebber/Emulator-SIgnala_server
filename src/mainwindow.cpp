#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_server(nullptr)
{

    m_ui->setupUi(this);

    connect(m_ui->StartServer, &QPushButton::clicked, this, &MainWindow::onStartServerClicked);
}

MainWindow::~MainWindow()
{
    delete m_ui;
    if (m_server)
    {
        delete m_server;
    }
}

void MainWindow::onStartServerClicked()
{
    if (!m_server)
    {
        QString state = "";
        m_server = new Server(m_ui->spinPort->value());
        if(m_server->isServerRunning())
        {
            state = "1";
            qDebug()<<"Server is connected";
        }
        else
        {
            qDebug()<<"There were problems connecting to the server";
            state = "0";
            delete m_server;
            m_server = nullptr;
        }
        m_ui->StartServer->setProperty("state", state);
        style()->polish(m_ui->StartServer);
        m_ui->StartServer->update();
    }
}


