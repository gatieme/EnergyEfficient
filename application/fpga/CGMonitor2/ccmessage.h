#ifndef CCMESSAGE_H
#define CCMESSAGE_H
//class CCMessage;
#include <QMainWindow>
#include<QtGui>
class CCMessage : public QMainWindow
{
    Q_OBJECT
public:

    QLabel* m_label;
    explicit CCMessage(QWidget *parent = 0);
    void showText(QString string, int second = -1);
    void changeText(QString newstring);

    QTimer* m_timer;

signals:

public slots:
     void hideNow();

};

extern CCMessage* g_CCMessage;


#endif // CCMESSAGE_H
