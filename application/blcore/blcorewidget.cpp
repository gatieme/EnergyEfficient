#include "blcorewidget.h"
#include "ui_blcorewidget.h"

BLCoreWidget::BLCoreWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BLCoreWidget)
{
    ui->setupUi(this);
}

BLCoreWidget::~BLCoreWidget()
{
    delete ui;
}
