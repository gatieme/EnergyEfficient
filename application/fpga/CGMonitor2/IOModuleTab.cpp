
#include <QtGui>
#include "IOModuleTab.h"

//! [0]
IOModuleTab::IOModuleTab(QWidget *parent)
{
    Q_UNUSED(parent);

    SubTypeLabel = new QLabel(tr("IO子板类型：           "));
    RecvNumberLabel = new QLabel(tr("接收总字节：         "));
    SendNumberLabel = new QLabel(tr("发送总字节：         "));


    mainLayout = new QHBoxLayout;
    vLayout1 = new QVBoxLayout;


    sendBuffer =new QHexEdit();
    recvBuffer =new QHexEdit();


    //布局
    vLayout1->addStretch(1);
    vLayout1->addWidget(SubTypeLabel);
    vLayout1->addWidget(RecvNumberLabel);
    vLayout1->addWidget(SendNumberLabel);
    vLayout1->addStretch(1);
    mainLayout->addItem(vLayout1);
    mainLayout->addWidget(sendBuffer);
    mainLayout->addWidget(recvBuffer);

    setLayout(mainLayout);
}
//! [0]
