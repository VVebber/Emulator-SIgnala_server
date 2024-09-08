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


protected:/*PROTECTED*/
    void run();

public:/*PUBLIC*/
    WaveSimulator(QMultiMap<QString, QTcpSocket*> clients);

public slots:
    void  creatingWave();

private:/*PRIVATE*/

    QMultiMap<QString, QTcpSocket*> m_clients;

    int m_countPoint;
};

#endif
