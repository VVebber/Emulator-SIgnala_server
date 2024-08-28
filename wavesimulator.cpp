#include "wavesimulator.h"

WaveSimulator::WaveSimulator(QTcpSocket* socket) :
    socket(socket) {}

void WaveSimulator::run(){
    Waves();
}

void WaveSimulator::Waves() {
    for (int x = -100; ; ++x) {
        if (x >= 100)
            x = -100;

        if(!socket->isValid()){
            break;
        }

        qreal y = 0;
        if (typeSignal == "sin") {
            y = 50 * std::sin(x * M_PI / 50);
        } else if (typeSignal == "cos") {
            y = 50 * std::cos(x * M_PI / 50);
        } else if (typeSignal == "tan") {
            y = 50 * std::tan(x * M_PI / 50);
        } else if (typeSignal == "atan") {
            y = 50 * std::atan(x * M_PI / 50);
        } else if (typeSignal == "acos") {
            y = 30 * std::acos(x / 150.0);
        } else if (typeSignal == "asin") {
            y = 40 * std::asin(x / 100.0);
        }

        if (std::abs(y) > 500) {
            y = std::copysign(500.0, y);
        }

        QPoint Point(x, y);

        QByteArray Data;
        QDataStream out(&Data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_2);
        out << Point;
        socket->write(Data);
        socket->flush();

        QThread::msleep(100);

        if (!socket->isOpen()) {
            break;
        }
    }
}

void WaveSimulator::settypeSignal(QString typeSignal){
    this->typeSignal = typeSignal;
}

