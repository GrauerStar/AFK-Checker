#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QApplication>

#include "inaktivchecker.h"


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

    //Pointer
    InaktivChecker *m_checker;

    //funktion die im Tray das Programm sichtbar macht  Ausgelagert wegen redundanz
    void oeffnenFuerTray();

private slots:
    void TestButton();

    //TrayIcon
    //aktion für Klick
    void trayIconAktiviert(QSystemTrayIcon::ActivationReason reason);

    //aktion für Öffnen
    void trayIconOeffnen();

    //beenden
    void trayIconBeenden();


};
#endif // MAINWINDOW_H
