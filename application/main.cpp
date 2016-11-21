#include "eewidget.h"
#include "fpga/CGmainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    CGCliSMFSInit();
    CGOPCliInit();


    QApplication a(argc, argv);



    //中文支持
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));  //支持Tr中文
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));    //支持中文文件名显示


    //设置字体
    QFont font;
    font.setPointSize(12); //
    font.setFamily("wqy-microhei");  //字库的名字要在字体路径中存在
    font.setBold(false);
    a.setFont(font);


    CGMainWindow cgw;
    cgw.show( );

    return a.exec();
}
