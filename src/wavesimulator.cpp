#include "wavesimulator.h"

WaveSimulator::WaveSimulator(QMultiMap<QString, QTcpSocket*> clients) {
    m_clients = clients;
    m_countPoint = -100;
}

void WaveSimulator::run()
{
    creatingWave();
}

void WaveSimulator:: creatingWave()
{
    if(m_clients.size() != 0)
    {
        if(m_countPoint >= 100){
            m_countPoint = -100;
        }
        QPoint Point(m_countPoint, 0);
        for(auto i = m_clients.begin(); i != m_clients.end(); i++)
        {
            if(!i.value()->isOpen())
            {
                continue;
            }

            if (i.key() == "sin")
            {
                Point.setY(50 * std::sin(m_countPoint * M_PI / 50));
            }
            else if (i.key() == "cos")
            {
                Point.setY(50 * std::cos(m_countPoint * M_PI / 50));
            }
            else if (i.key() == "tan")
            {
                Point.setY(50 * std::tan(m_countPoint * M_PI / 50));
            }
            else if (i.key() == "atan")
            {
                Point.setY(50 * std::atan(m_countPoint * M_PI / 50));
            }
            else if (i.key() == "acos")
            {
                Point.setY(30 * std::acos(m_countPoint / 150.0));
            }
            else if (i.key() == "asin")
            {
                Point.setY(40 * std::asin(m_countPoint / 100.0));
            }

            QByteArray Data;
            QDataStream out(&Data, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_15);
            out << Point;
            i.value()->write(Data);
            i.value()->flush();

            QThread::msleep(100);
        }
    }
}
