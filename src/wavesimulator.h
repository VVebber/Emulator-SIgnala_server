#ifndef WAVESIMULATOR_H
#define WAVESIMULATOR_H

#include <QMessageBox>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <cmath>

class WaveSimulator : public QObject {
    Q_OBJECT


protected:/*PROTECTED*/

public:/*PUBLIC*/
    WaveSimulator();

    void connectClient();

    void setsokerDeskription(qintptr sokerDeskription);
public slots:
    void readToClient();

    void start();

    void timerEvent(QTimerEvent *event) override;


    void disconectClient();

private:/*PRIVATE*/


    QTcpSocket* m_socket;

    qintptr m_sokerDeskription;

    QString m_typeWave;

    int m_countPoint;

private:
    void  sendToClient();
};

#endif
