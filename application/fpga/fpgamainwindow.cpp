#include "fpgamainwindow.h"
#include "ui_fpgamainwindow.h"

FPGAMainWindow::FPGAMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FPGAMainWindow)
{
    ui->setupUi(this);
}

FPGAMainWindow::~FPGAMainWindow()
{
    delete ui;
}
