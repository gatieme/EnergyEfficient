#ifndef FPGAMAINWINDOW_H
#define FPGAMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class FPGAMainWindow;
}

class FPGAMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FPGAMainWindow(QWidget *parent = 0);
    ~FPGAMainWindow();

private:
    Ui::FPGAMainWindow *ui;
};

#endif // FPGAMAINWINDOW_H
