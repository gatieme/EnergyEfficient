#ifndef EEWIDGET_H
#define EEWIDGET_H

#include <QWidget>

namespace Ui {
class EEWidget;
}

class EEWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EEWidget(QWidget *parent = 0);
    ~EEWidget();

private:
    Ui::EEWidget *ui;
};

#endif // EEWIDGET_H
