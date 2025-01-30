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

//Diese Funktion hat mir ChatGPT erstellt
int Helper::parseTimeString(const QString &input)
{
    static const QRegularExpression hhmmssRegex(R"(^(\d{1,2}):(\d{1,2}):(\d{1,2})$)");
    static const QRegularExpression unitRegex(R"((\d+)\s*(h|hour|hours|m|min|minute|minutes|s|sec|second|seconds))", QRegularExpression::CaseInsensitiveOption);

    QString trimmed = input.trimmed();

    // Prüfen, ob nur eine Zahl eingegeben wurde (direkte Sekunden)
    bool isNumber;
    int seconds = trimmed.toInt(&isNumber);
    if (isNumber)
    {
        return seconds;
    }

    // HH:MM:SS Format
    QRegularExpressionMatch match = hhmmssRegex.match(trimmed);
    if (match.hasMatch())
    {
        int hours = match.captured(1).toInt();
        int minutes = match.captured(2).toInt();
        int secs = match.captured(3).toInt();
        return (hours * 3600) + (minutes * 60) + secs;
    }

    // Xh Ym Zs Format
    int totalSeconds = 0;
    QRegularExpressionMatchIterator it = unitRegex.globalMatch(trimmed);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        int value = match.captured(1).toInt();
        QString unit = match.captured(2).toLower();

        if (unit.startsWith("h")) totalSeconds += value * 3600;
        else if (unit.startsWith("m")) totalSeconds += value * 60;
        else if (unit.startsWith("s")) totalSeconds += value;
    }

    return totalSeconds;
}
