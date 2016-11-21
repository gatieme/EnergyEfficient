#ifndef DESDESMainWindow_H
#define DESDESMainWindow_H

#include <QMainWindow>
#include "fpga/fpgaCG.h"

namespace Ui {
class DESMainWindow;
}

class DESMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DESMainWindow(QWidget *parent = 0);
    ~DESMainWindow();

    struct CGTimeInfo m_time;
    struct CGCalTaskReturn m_taskreturn;

    unsigned char m_key[8];
    unsigned int m_isFPGA;
    QString fileName;

private slots:
    void on_encryptButton_clicked(); //

    void on_armRadioButton_clicked();

    void on_fpgaRadioButton_clicked();

    void on_decryptButton_clicked();

    void on_exitButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_armRadioButton_2_clicked();

    void on_fpgaRadioButton_2_clicked();

    void on_pushButton_3_clicked();

    void show1();//正确性验证
    void show2();//性能测试
private:
    Ui::DESMainWindow *ui;

    QString mRadioButtonSelected;

    QString desFilePath;
};

#endif // MAINWINDOW_H
