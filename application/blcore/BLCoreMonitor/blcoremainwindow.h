#ifndef BLCOREMAINWINDOW_H
#define BLCOREMAINWINDOW_H

#include <QMainWindow>

#include "blcoretabwidget.h"

namespace Ui {
class BLCoreMainWindow;
}

class BLCoreMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BLCoreMainWindow(QWidget *parent = 0);
    ~BLCoreMainWindow();

private:
    Ui::BLCoreMainWindow *ui;

protected :
    BLCoreTabWidget *m_blcoreTabWidget;
};

#endif // BLCOREMAINWINDOW_H
