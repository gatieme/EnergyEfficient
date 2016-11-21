#ifndef BLCOREWIDGET_H
#define BLCOREWIDGET_H

#include <QWidget>

namespace Ui {
class BLCoreWidget;
}

class BLCoreWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BLCoreWidget(QWidget *parent = 0);
    ~BLCoreWidget();

private:
    Ui::BLCoreWidget *ui;
};

#endif // BLCOREWIDGET_H
