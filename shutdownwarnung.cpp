#include "shutdownwarnung.h"
#include "ui_shutdownwarnung.h"

ShutdownWarnung::ShutdownWarnung(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShutdownWarnung)
{
    ui->setupUi(this);

    connect(&timer, &QTimer::timeout, this, &ShutdownWarnung::updateCountdown);

    //Buttons
    connect(ui->pushButton_herunterfahren, &QPushButton::clicked, this, &ShutdownWarnung::button_shutdown);
    connect(ui->pushButton_weiter, &QPushButton::clicked, this, &ShutdownWarnung::button_Weiter);

    //Timer ausführen alle 1sec ( = 1000ms )
    timer.start(1000);

}


ShutdownWarnung::~ShutdownWarnung()
{
    delete ui;
}

void ShutdownWarnung::setShutdownTimeInSec(int newShutdownTimeInSec)
{
    m_shutdownTimeInSec = newShutdownTimeInSec;
    ui->label_Zeit_aendern->setText(Helper::zeitInString(m_shutdownTimeInSec));
}


void ShutdownWarnung::updateCountdown()
{
    m_shutdownTimeInSec--;

    ui->label_Zeit_aendern->setFont(QFont("Segoe UI",9 ,QFont::Bold));
    ui->label_Zeit_aendern->setText(Helper::zeitInString(m_shutdownTimeInSec));

    if(m_shutdownTimeInSec <= 0)
    {
        timer.stop(); // Danke Timer das wars
        button_shutdown();
    }


}

void ShutdownWarnung::button_shutdown()
{
    accept();
}

void ShutdownWarnung::button_Weiter()
{
    reject();
}

/*

QString ShutdownWarnung::zeitInString(int eingabe)
{
    int stunden = 0;
    int minuten = 0;

    QString ausgabe;

    // Stunden
    if(eingabe >= 1*60*60)
    {
        do
        {
            stunden++;
            eingabe -= 1*60*60;
        }
        while (eingabe >= 1*60*60);

    }
    // Minuten
    if(eingabe >= 1*60)
    {
        do
        {
            minuten++;
            eingabe -= 1*60;
        }
        while (eingabe >= 1*60);
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

*/
