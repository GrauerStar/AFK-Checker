#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "inaktivchecker.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_test, &QPushButton::clicked, this, &MainWindow::TestButton);


    //Checker erstellen
    //TEST Timeout 0,5 min
    m_checker = new InaktivChecker(this);
    m_checker->setTimeoutSec(10);

    //starten wenn das Fenster erstellt ist
    m_checker->startChecking();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TestButton()
{
    ui->label_test->setText("Ja geht, Danke");

    return;
}


//TrayIcon ------------------------------------------------------

void MainWindow::oeffnenFuerTray()
{
    show();
    //in Vordergrund
    raise();
    //Fokus aktiviert
    activateWindow();
}

void MainWindow::trayIconAktiviert(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick)
    {
        oeffnenFuerTray();
    }
}

//aktion für Öffnen
void MainWindow::trayIconOeffnen()
{
    oeffnenFuerTray();
}

//beenden
void MainWindow::trayIconBeenden()
{
    QApplication::quit();
}
