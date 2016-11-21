#ifndef IOMODULETAB_H
#define IOMODULETAB_H

#include <QWidget>
#include "qhexedit.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QVBoxLayout;
class QHBoxLayout;
QT_END_NAMESPACE

//! [0]
class IOModuleTab : public QWidget
{
    Q_OBJECT

public:
    IOModuleTab(QWidget *parent=0);


private:
    QHexEdit* sendBuffer;
    QHexEdit* recvBuffer;
    QLabel *SubTypeLabel;
    QLabel *RecvNumberLabel;
    QLabel *SendNumberLabel;


    QHBoxLayout *mainLayout;
    QVBoxLayout*  vLayout1;
};
//! [0]
#endif // SUMMARYTAB_H
