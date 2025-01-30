#include "inaktivchecker.h"


InaktivChecker::InaktivChecker(QObject *parent) : QObject(parent)
{
    //timer checkt alle 5 min = 300 sec = 300000 msec
    //m_timer.setInterval(300000);
    m_timer.setInterval(5000);
    connect(&m_timer, &QTimer::timeout, this, &InaktivChecker::checkAktivitaet);
}


void InaktivChecker::startChecking()
{
    m_timeBackup = m_timerDialog;
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


        if(elapsedSec >= static_cast<unsigned long>(m_timeInaktiv))
        {
            ShutdownWarnung sw;
            //todo config
            sw.setShutdownTimeInSec(m_timerDialog);
            sw.setWindowTitle("Zu lange inaktiv");

            //Dialog immer vorn halten
            sw.setWindowModality(Qt::ApplicationModal); // lässt sich nicht mehr überlappen
            sw.setWindowFlags(sw.windowFlags() | Qt::WindowStaysOnTopHint); // Immer im Vordergrund
            sw.raise(); // in den Vordergrund bringen
            sw.activateWindow(); //Fokus aktivieren

            int rueckgabe = sw.exec();

            //Timer anhalten
            m_timer.stop();

            //Restared das ganze wieder
            if(rueckgabe == QDialog::Rejected)
            {
                 //Timer wieder starten
                m_timer.start();
            }
            else
            {
                //system("shutdown -s -t 5");
                system("msg %username% Oha ich hab dich gerade noch geretted");
                QApplication::quit();

            }


        }
        else
        {
            //Nothing
        }
    }
}


//Setter funktionen
void InaktivChecker::setTimeInaktiv(int eingabe)
{
    m_timeInaktiv = eingabe;
}

void InaktivChecker::setTimeDialog(int eingabe)
{
    m_timerDialog = eingabe;
}
