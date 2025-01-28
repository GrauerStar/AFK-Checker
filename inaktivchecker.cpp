#include "inaktivchecker.h"



InaktivChecker::InaktivChecker(QObject *parent) : QObject(parent), m_timeOutSec(60) // Standard 60 Sek
{
    //timer checkt alle 5 min = 300 sec = 300000 msec
    //m_timer.setInterval(300000);
    m_timer.setInterval(5000);
    connect(&m_timer, &QTimer::timeout, this, &InaktivChecker::checkAktivitaet);
}



void InaktivChecker::setTimeoutSec(int seconds)
{
    m_timeOutSec = seconds;
}

int InaktivChecker::timeoutSec() const
{
    return m_timeOutSec;
}

void InaktivChecker::startChecking()
{
    m_timer.start();
}

void InaktivChecker::stopChecking()
{
    m_timer.stop();  // Timer anhalten
}


void InaktivChecker::checkAktivitaet()
{
    //Letzen Eingabe auslsesn
    LASTINPUTINFO lii;
    lii.cbSize = sizeof(LASTINPUTINFO);

    if(GetLastInputInfo(&lii))
    {
        DWORD tickCount = GetTickCount(); //Aktuelle Tiks
        DWORD lastInputTicks = lii.dwTime;
        DWORD elapsed = tickCount - lastInputTicks; // unterschied in MS

        // umrechnen in Sekunden
        unsigned long elapsedSec = elapsed / 1000;


        if(elapsedSec >= static_cast<unsigned long>(m_timeOutSec))
        {
            //TODO hier muss ein shutdown rein
            //QProcess::execute("shutdown", {"/s", "/t", "0"});
            // oder via WinAPI: ExitWindowsEx(EWX_SHUTDOWN, 0);
            QProcess::execute("msg %username% Hier sollte ein Shutdown sein");

            //Timer anhalten
            m_timer.stop();
        }
        else
        {
            //Nothing
        }
    }
}
