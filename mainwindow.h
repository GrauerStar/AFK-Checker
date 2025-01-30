#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QApplication>
#include <QFile>
#include <QMessageBox>

#include "inaktivchecker.h"
#include "helper.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //InaktivChecker
    InaktivChecker m_checker;

    //funktion die im Tray das Programm sichtbar macht  Ausgelagert wegen redundanz
    void oeffnenFuerTray();

    //Settings
    void exportSettings();
    void importSettings();
    void uiTextSettings();

    //Zeit Werte
    int m_timeInaktiv = 10*60; //Default 10min
    int m_timerDialog = 1*60; //Default 1 min

private slots:
    void button_einstellungenSetzen();
    void button_abbruch();

    //TrayIcon
    //aktion für Klick
    void trayIconAktiviert(QSystemTrayIcon::ActivationReason reason);

    //aktion für Öffnen
    void trayIconOeffnen();

    //beenden
    void trayIconBeenden();


};
#endif // MAINWINDOW_H
