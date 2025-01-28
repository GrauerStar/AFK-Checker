#ifndef SHUTDOWNWARNUNG_H
#define SHUTDOWNWARNUNG_H

#include <QDialog>

namespace Ui {
class ShutdownWarnung;
}

class ShutdownWarnung : public QDialog
{
    Q_OBJECT

public:
    explicit ShutdownWarnung(QWidget *parent = nullptr);
    ~ShutdownWarnung();

private:
    Ui::ShutdownWarnung *ui;
};

#endif // SHUTDOWNWARNUNG_H
