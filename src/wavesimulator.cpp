#include "wavesimulator.h"

WaveSimulator::WaveSimulator() {
    m_typeWave = "cos";
    m_countPoint = -100;
    m_socket = nullptr;
}

void WaveSimulator::connectClient(){
    m_socket = new QTcpSocket;
    m_socket->setSocketDescriptor(m_sokerDeskription);

    connect(m_socket, &QTcpSocket::readyRead, this, &WaveSimulator::readToClient);
    connect(m_socket, &QTcpSocket::disconnected, this, &WaveSimulator::disconectClient);
    qDebug() <<"Connect client";

}

void WaveSimulator::setsokerDeskription(qintptr sokerDeskription){
    m_sokerDeskription = sokerDeskription;
}

void WaveSimulator::readToClient(){
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);

    if(in.status() == QDataStream::Ok)
    {
        QString str;
        in >> str;

        m_typeWave = str;
        qDebug() <<"Получен запрос: "<< str;
    }
    else
    {
        qDebug() <<"Ошибка запроса.";
    }
}

void WaveSimulator::disconectClient(){
    m_socket->deleteLater();
    m_socket = nullptr;
}

void WaveSimulator::start(){
    if(!m_socket)
    connectClient();
}

void WaveSimulator::timerEvent(QTimerEvent* event){
    sendToClient();

    startTimer(1000);
}

void WaveSimulator::sendToClient()
{

    if(m_countPoint >= 100){
        m_countPoint = -100;
    }
    QPoint Point(m_countPoint, 0);

    if(m_socket->isOpen())
    {

        if (m_typeWave == "sin")
        {
            Point.setY(50 * std::sin(m_countPoint * M_PI / 50));
        }
        else if (m_typeWave == "cos")
        {
            Point.setY(50 * std::cos(m_countPoint * M_PI / 50));
        }
        else if (m_typeWave == "tan")
        {
            Point.setY(50 * std::tan(m_countPoint * M_PI / 50));
        }
        else if (m_typeWave == "atan")
        {
            Point.setY(50 * std::atan(m_countPoint * M_PI / 50));
        }
        else if (m_typeWave == "acos")
        {
            Point.setY(30 * std::acos(m_countPoint / 150.0));
        }
        else if (m_typeWave == "asin")
        {
            Point.setY(40 * std::asin(m_countPoint / 100.0));
        }

        QByteArray Data;
        Data.clear();
        QDataStream out(&Data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_15);
        out << Point;
        m_socket->write(Data);

        if(m_socket)
        {
            m_socket->flush();
        }

        m_countPoint++;

        QThread::msleep(100);
    }
}
