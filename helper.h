#ifndef HELPER_H
#define HELPER_H

#include <QString>
#include <QRegularExpression>



class Helper
{
public:
    Helper();

    static QString zeitInString(int eingabe);
    static int parseTimeString(const QString &input);
};

#endif // HELPER_H
