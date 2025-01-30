#ifndef INAKTIVCHECKER_H
#define INAKTIVCHECKER_H

#include <QObject>
#include <QTimer>
#include <Windows.h>  // Für GetLastInputInfo, GetTickCount
#include <QDebug>
#include <QProcess>
#include <QApplication>

#include "shutdownwarnung.h"

class InaktivChecker : public QObject {

    Q_OBJECT


public:
    explicit InaktivChecker(QObject *parent = nullptr);



public slots:
    void startChecking();
    void stopChecking();

    void setTimeInaktiv(int eingabe);
    void setTimeDialog(int eingabe);


private slots:
    void checkAktivitaet();

private:
    QTimer m_timer;

    int m_timeInaktiv = 60; // default werte;
    int m_timerDialog = 10; // default werte;

    int m_timeBackup;

};



#endif // INAKTIVCHECKER_H
