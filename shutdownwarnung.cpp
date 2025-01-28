#include "shutdownwarnung.h"
#include "ui_shutdownwarnung.h"

ShutdownWarnung::ShutdownWarnung(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShutdownWarnung)
{
    ui->setupUi(this);
}

ShutdownWarnung::~ShutdownWarnung()
{
    delete ui;
}
