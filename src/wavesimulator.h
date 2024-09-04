#ifndef WAVESIMULATOR_H
#define WAVESIMULATOR_H

#include <QMessageBox>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <cmath>

class WaveSimulator : public QThread {
    Q_OBJECT
private:/*PRIVATE*/
    QTcpSocket* socket;
    QString typeSignal;

protected:/*PROTECTED*/
    void run() override;

public:/*PUBLIC*/
    explicit WaveSimulator(QTcpSocket* socket);


    void Waves();
    /*set*/
    void settypeSignal(QString typeSignal);
    /*get*/

};

#endif
