#ifndef INAKTIVCHECKER_H
#define INAKTIVCHECKER_H

#include <QObject>
#include <QTimer>
#include <Windows.h>  // Für GetLastInputInfo, GetTickCount
#include <QDebug>
#include <QProcess>

class InaktivChecker : public QObject {

    Q_OBJECT


public:
    explicit InaktivChecker(QObject *parent = nullptr);

    //Zeit in Sec nachdem die Warnung kommen soll
    void setTimeoutSec(int seconds);
    int timeoutSec() const;

public slots:
    void startChecking();
    void stopChecking();

private slots:
    void checkAktivitaet();

private:
    QTimer m_timer;
    int m_timeOutSec;

};



#endif // INAKTIVCHECKER_H
