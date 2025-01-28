#include "mainwindow.h"

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //!!Wichtig Progamm nicht schließen wenn es nicht sichtbar ist
    QApplication::setQuitOnLastWindowClosed(false);


    MainWindow w;
    //kein w.show() damit es nicht geöffnet wird

    //TrayIcon
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(&w);
    trayIcon->setIcon(QIcon(":/trayIcon"));
    trayIcon->setToolTip("AFK-Checker");

    //TrayIcon Menu
    QMenu *trayMenu = new QMenu();

    //Aktionen
    //fenster öffnen
    QAction *oeffnenAction = new QAction("Fenster öffnen", trayMenu);
    QObject::connect(oeffnenAction, SIGNAL(triggered()), &w, SLOT(trayIconOeffnen()));
    trayMenu->addAction(oeffnenAction);

    //beenden
    QAction *beendenAction = new QAction("Beenden", trayMenu);
    QObject::connect(beendenAction, SIGNAL(triggered()), &w, SLOT(trayIconBeenden()));
    trayMenu->addAction(beendenAction);

    //Menu dem TrayIcon zuweisen
    trayIcon->setContextMenu(trayMenu);

    //Signal und Slot
    QObject::connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), &w, SLOT(trayIconAktiviert(QSystemTrayIcon::ActivationReason)));

    //TrayIcon anzeigen
    trayIcon->show();

    return a.exec();

}
