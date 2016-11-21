#ifndef JPEGMainWindow_H
#define JPEGMainWindow_H

#include <QMainWindow>
#include "fpga/fpgaCG.h"
namespace Ui {
class JPEGMainWindow;
}

class JPEGMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit JPEGMainWindow(QWidget *parent = 0);
    ~JPEGMainWindow();
    int m_isFPGA;
    struct CGTimeInfo M_timeinfo;

private slots:

    void on_armRadioButton_clicked();

    void on_fpgaRadioButton_clicked();

    void on_selectPathButton_clicked();

    void on_pictureCompressionButton_clicked();



private:
    Ui::JPEGMainWindow *ui;

    QString mRadioButtonSelected;
    QString mPixmapPath; //原图路径
    QPixmap mPixmap;
    QPixmap mPixmapafter;
    QString mImageInfo;
};

#endif // MAINWINDOW_H
