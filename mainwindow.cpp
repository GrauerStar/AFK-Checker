#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "inaktivchecker.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Buttons verbinden
    connect(ui->pushButton_eistellen, &QPushButton::clicked, this, &MainWindow::button_einstellungenSetzen);
    connect(ui->pushButton_abbrechen, &QPushButton::clicked, this, &MainWindow::button_abbruch);




    importSettings(); // Einstellungen aus Datei laden

    //Checker Zeit setzen
    m_checker.setTimeInaktiv(m_timeInaktiv);
    m_checker.setTimeDialog(m_timerDialog);

    //starten wenn das Fenster erstellt ist
    m_checker.startChecking();

    //Text in die line Edit setzten
    ui->lineEdit_Inaktiv->setText(QString::number(m_timeInaktiv));
    ui->lineEdit_Dialog->setText(QString::number(m_timerDialog));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::button_einstellungenSetzen()
{
    // TODO SICHERHEITSABFRAGE!!!!!!!!!!!!!!
    m_timeInaktiv = ui->lineEdit_Inaktiv->text().toInt();
    m_timerDialog = ui->lineEdit_Dialog->text().toInt();
    exportSettings();
    //Checker Zeit setzen
    m_checker.setTimeInaktiv(m_timeInaktiv);
    m_checker.setTimeDialog(m_timerDialog);
    close();
}
void MainWindow::button_abbruch()
{
    close();
}


void MainWindow::exportSettings()
{
    QFile cfg("settings.cfg"); //Datei erstellen oder öffnen

    if(cfg.open(QIODevice::WriteOnly | QIODevice::Text)) //zum schreiben
    {
        QTextStream stream(&cfg);
        stream << "InaktivTime: " << m_timeInaktiv << "\n";
        stream << "DialogTime: " << m_timerDialog << "\n";
        cfg.close();
    }
    else
    {
        QMessageBox Fehler;
        Fehler.setWindowTitle("Fehler");
        Fehler.setIcon(QMessageBox::Critical);
        Fehler.setText("Die Einstellungen konnte nicht gespeichert werden!");
        Fehler.setInformativeText("Bitte starten sie das Programm neu und prüfen sei ob sie schreibrechte in diesem Ordner haben.");
        Fehler.exec();

    }
}

void MainWindow::importSettings()
{
    QFile cfg("settings.cfg");

    if(cfg.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&cfg);
        while (!stream.atEnd()) // Zeile für zeile
        {
            QString zeile = stream.readLine();

            if(zeile.startsWith("InaktivTime:"))
            {
                m_timeInaktiv = zeile.section(":", 1,1).trimmed().toInt();
            }
            else if(zeile.startsWith("DialogTime:"))
            {
                m_timerDialog = zeile.section(":", 1, 1).trimmed().toInt();
            }

        }
        cfg.close();
    }
    else
    {
        QMessageBox Fehler;
        Fehler.setWindowTitle("Fehler");
        Fehler.setIcon(QMessageBox::Warning);
        Fehler.setText("Die Einstellungen konnte nicht geladen werden!");
        Fehler.setInformativeText("Es werden die Standard einstellungen genutzt.");
        Fehler.exec();
    }
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
