#include "JPEGmainwindow.h"
#include "ui_jpegmainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDateTime>
#include <QTime>
#include <QShortcut>
JPEGMainWindow::JPEGMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JPEGMainWindow)
{
    ui->setupUi(this);
    ui->fpgaRadioButton->setChecked(true);
    mRadioButtonSelected = "FPGA";//FPGA
    m_isFPGA=2;//默认选中FPGA

    //设置快捷键
    QShortcut *quitKey = new QShortcut(QKeySequence(Qt::Key_Escape),this);
    connect(quitKey,SIGNAL(activated()),this,SLOT(close()));

    QShortcut *Key1 = new QShortcut(QKeySequence(Qt::Key_Space),this);
    connect(Key1,SIGNAL(activated()),this,SLOT(on_selectPathButton_clicked()));

    QShortcut *Key2 = new QShortcut(QKeySequence(Qt::Key_1),this);
    connect(Key2,SIGNAL(activated()),this,SLOT(on_pictureCompressionButton_clicked()));
}

JPEGMainWindow::~JPEGMainWindow()
{
    delete ui;
}

void JPEGMainWindow::on_armRadioButton_clicked()
{
    mRadioButtonSelected = "ARM";//ARM
     m_isFPGA=1;//选中ARM
    ui->statusBar->showMessage("ARM method selected.",1000);
}

void JPEGMainWindow::on_fpgaRadioButton_clicked()
{
    mRadioButtonSelected = "FPGA";//FPGA
     m_isFPGA=2;//默认选中FPGA
    ui->statusBar->showMessage("FPGA method selected.",1000);
}

void JPEGMainWindow::on_selectPathButton_clicked()
{
    //statusBar()->message(tr("Opening file..."));
#if 0
    QString fileName = QFileDialog::getOpenFileName(
                      "./map/",
                      "Images (*.bmp);;"
                      "Any files (*.*)",
                      this);
#endif
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "/home",
                tr("Images (*.png *.xpm *.jpg)"));

    if (!fileName.isEmpty()){

        mPixmapPath = fileName;

        mPixmap.load(mPixmapPath);
        ui->originalPicturePath->setText(mPixmapPath);
        //mPixmap.resize(0.9 * ui->originalPicture->width(),0.9 * ui->originalPicture->height());
        QGraphicsScene *mScence = new QGraphicsScene;

        mPixmap = mPixmap.scaled(0.9 * ui->originalPicture->width(),0.9 * ui->originalPicture->height());
        mScence->addPixmap(mPixmap);
        ui->originalPicture->setScene(mScence);
        ui->originalPicture->show();

        QString message=tr("Loaded document: ") + fileName;
        //statusBar()->message(message, 2000);
        QFileInfo fileinfo(mPixmapPath);

        ui->originalLabel->setText(QString("%1").arg((double)fileinfo.size()/(1024 )) + "KB");
    }else{
        //statusBar()->message(tr("Opening aborted"), 2000);
    }
}

void JPEGMainWindow::on_pictureCompressionButton_clicked()
{
    //1.检查参数
    if(mRadioButtonSelected == "NOMethod"){
        ui->statusBar->showMessage("Please select a method!",5000);
        return;
    }
    if(mPixmapPath.isEmpty()){
        ui->statusBar->showMessage("No BMP Picuture Selected!",5000);
        return;
    }

    /*if(ui->compressedPicture->scene()!=NULL){
        ui->compressedPicture->scene()->clear();
    }*/
   // ui->compressedPicture->removeChild();
    //2.开始压缩
    char* data = mPixmapPath.toLatin1().data();
    char* afterPATH = (char*)JPEGCompressPicutre ((unsigned char*)data, m_isFPGA,&M_timeinfo);
    if(afterPATH == NULL) return;
    //3.显示压缩结果
     if(M_timeinfo.howTo==1){ //ARM
        ui->methodLabel->setText(tr("ARM"));
     }else if(M_timeinfo.howTo==2){//FPGA
          ui->methodLabel->setText(tr("FPGA"));
     }else{

     }
     ui->timeLabel->setText(tr("%1 ms").arg(M_timeinfo.armtime+M_timeinfo.fpgatime) );//to edit
     QString path=afterPATH;
     //mPixmapafter.load(path);
     path=mPixmapPath+"_CG";
     mPixmapafter.load(path);
     //mPixmapafter.load("/usr/cc/map/1.jpg");
     //mPixmapafter.load("/home/cc/Desktop/2015-12-10/wsphit/bin/map/hitmap1.bmp");
   // mPixmapafter.load("/home/cc/Desktop/2015-12-10/wsphit/bin/map/hitmap1.bmp_CG");
   /* mPixmapPath = fileName;

    mPixmap.load(mPixmapPath);
    ui->originalPicturePath->setText(mPixmapPath);
    //mPixmap.resize(0.9 * ui->originalPicture->width(),0.9 * ui->originalPicture->height());
    QGraphicsScene *mScence = new QGraphicsScene;

    mPixmap = mPixmap.scaled(0.9 * ui->originalPicture->width(),0.9 * ui->originalPicture->height());
    mScence->addPixmap(mPixmap);

    */
    QTime timePeriod;
    timePeriod.start();

    QGraphicsScene *mScence = new QGraphicsScene;
    mPixmapafter = mPixmapafter.scaled(ui->compressedPicture->width() * 0.9,ui->compressedPicture->height() * 0.9);
    mScence->addPixmap(mPixmapafter);
    ui->compressedPicture->setScene(mScence);
    ui->compressedPicture->show();
    ui->compressionHeightNum->setText(QString::number(mPixmapafter.height()));
    ui->compressionWidthNum->setText(QString::number(mPixmapafter.width()));

    ui->originalHeightNum->setText( QString::number(mPixmap.height()) );
    ui->originalWidthNum->setText( QString::number(mPixmap.width()) );


    QFileInfo fileinfo((const char*)afterPATH);
    mImageInfo = "";
    mImageInfo += (tr("创建时间:\n") + fileinfo.created().toString());
    mImageInfo += (tr("\n最后修改时间:\n") + fileinfo.lastModified().toString());
    ui->infomationText->setText(mImageInfo);
    ui->compressedLabel->setText(QString("%1").arg((double)fileinfo.size()/(1024 )) + "KB");

}
