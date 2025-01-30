#ifndef SHUTDOWNWARNUNG_H
#define SHUTDOWNWARNUNG_H

#include <QDialog>
#include <QTimer>
#include <QProcess>

#include "helper.h"

namespace Ui {
class ShutdownWarnung;
}

class ShutdownWarnung : public QDialog
{
    Q_OBJECT

public:
    explicit ShutdownWarnung(QWidget *parent = nullptr);
    ~ShutdownWarnung();

    void setShutdownTimeInSec(int newShutdownTimeInSec);

private:
    Ui::ShutdownWarnung *ui;

    QTimer timer;

    int m_shutdownTimeInSec = 10; //Default wert
    QString zeitInString(int eingabe);



private slots:
    void updateCountdown();
    void button_shutdown();
    void button_Weiter();

};


#endif // SHUTDOWNWARNUNG_H
