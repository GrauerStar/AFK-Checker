#include "helper.h"

Helper::Helper() {}


QString Helper::zeitInString(int eingabe)
{
    int stunden = 0;
    int minuten = 0;

    QString ausgabe;

    // Stunden
    if(eingabe >= 1*60*60)
    {
        stunden = eingabe / (60*60);
        eingabe -= stunden*(60*60);
    }
    // Minuten
    if(eingabe >= 1*60)
    {
        minuten = eingabe / 60;
        eingabe -= minuten*60;
    }


    if(stunden)
    {
        ausgabe = QString::number(stunden) + "h " + QString::number(minuten) + "min " + QString::number(eingabe) + "sek";
        return ausgabe;
    }
    else if(minuten)
    {
        ausgabe = QString::number(minuten) + "min " + QString::number(eingabe) + "sek";
        return ausgabe;
    }
    else
    {
        ausgabe = QString::number(eingabe) + "sek";
        return ausgabe;
    }

}
