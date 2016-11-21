#include "eewidget.h"
#include "ui_eewidget.h"

EEWidget::EEWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EEWidget)
{
    ui->setupUi(this);
}

EEWidget::~EEWidget()
{
    delete ui;
}
