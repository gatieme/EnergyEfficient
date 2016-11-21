#include "DESmainwindow.h"
#include "ui_desmainwindow.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QDateTime>
#include <QTime>
#include<QShortcut>
DESMainWindow::DESMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DESMainWindow)
{
    ui->setupUi(this);
    mRadioButtonSelected = "NOMethod";

    on_fpgaRadioButton_clicked();
    m_isFPGA=2; //FPGA
    ui->fpgaRadioButton->setChecked(true);
    ui->fpgaRadioButton_2->setChecked(true);
    ui->clearText->setText(tr("4567345623451234"));
    ui->secretKey->setText(tr("0715120404100520"));
    ui->label->setWordWrap(true);
    ui->label->setAlignment(Qt::AlignTop);

    //标签切换
    QShortcut *Key1 = new QShortcut(QKeySequence(Qt::Key_1),this); //
    connect(Key1,SIGNAL(activated()),this,SLOT(show1()));

    QShortcut *Key2 = new QShortcut(QKeySequence(Qt::Key_2),this);
    connect(Key2,SIGNAL(activated()),this,SLOT(show2()));

    QShortcut *KeyQuit = new QShortcut(QKeySequence(Qt::Key_Escape),this);
    connect(KeyQuit,SIGNAL(activated()),this,SLOT(close()));

    //正确性验证
    QShortcut *KeyE = new QShortcut(QKeySequence(Qt::Key_E),this); //
    connect(KeyE,SIGNAL(activated()),this,SLOT(on_encryptButton_clicked()));

    QShortcut *KeyD = new QShortcut(QKeySequence(Qt::Key_D),this);
    connect(KeyD,SIGNAL(activated()),this,SLOT(on_decryptButton_clicked()));

    //选择加密方式
    QShortcut *Key3 = new QShortcut(QKeySequence(Qt::Key_A),this);
    connect(Key3,SIGNAL(activated()),this,SLOT(on_armRadioButton_clicked()));

    QShortcut *Key4 = new QShortcut(QKeySequence(Qt::Key_F),this);
    connect(Key4,SIGNAL(activated()),this,SLOT(on_fpgaRadioButton_clicked()));

    //选择打开文件
    QShortcut *Key7 = new QShortcut(QKeySequence(Qt::Key_Space),this);
    connect(Key7,SIGNAL(activated()),this,SLOT(on_pushButton_clicked()));

    QShortcut *Key8 = new QShortcut(QKeySequence(Qt::Key_K),this);
    connect(Key8,SIGNAL(activated()),this,SLOT(on_pushButton_2_clicked()));

    QShortcut *Key9 = new QShortcut(QKeySequence(Qt::Key_L),this);
    connect(Key9,SIGNAL(activated()),this,SLOT(on_pushButton_3_clicked()));


    //性能测试

}

DESMainWindow::~DESMainWindow()
{
    delete ui;
}

void DESMainWindow::on_encryptButton_clicked()
{
    //1. 取得文件内容
     QString mClearText = ui->clearText->toPlainText();
     mClearText = mClearText.toUpper();
     ui->clearText->setText(mClearText);
     QString mSecretKey = ui->secretKey->toPlainText();
     mSecretKey = mSecretKey.toUpper();
     ui->secretKey->setText(mSecretKey);
     if(ui->clearText->toPlainText() == ""){
         ui->statusBar->showMessage("Please type in the clear text!",5000);
         return;
     }
     if(mRadioButtonSelected == "NOMethod"){
         ui->statusBar->showMessage("Please select a method!",5000);
         return;
     }
     ui->ciphertText->setText("");

     /********/
     //2. 文本内容转化
    int datalen = mClearText.length();
    char* data = mClearText.toLatin1().data();
    data = (char*)StringToBits(data,&datalen);

    int keylen=16;
    char*  key=mSecretKey.toLatin1().data();
    key = (char*)StringToBits(key,&keylen);
     //3. 加密解密
     unsigned char* fileretur = DESEncryption ( (unsigned char*)data,datalen,(unsigned char*)key,keylen, m_isFPGA,&m_time);
     /********/
     char* dataenc = (char*)BitsToString((char*)fileretur,datalen);
    //4. 显示加密后内容
     ui->ciphertText->setText(QString(dataenc));
     ui->methodLabel->setText("METHOD: " + mRadioButtonSelected);
     ui->timeLabel->setText("TIME: " + QString::number(1) );//to edit

     if(m_time.howTo==1){ //ARM
        ui->methodLabel->setText(tr("实际计算方式: \n  FPGA(0%) \n  ARM(100%)"));
     }else if(m_time.howTo==2){//FPGA
          ui->methodLabel->setText(tr("实际计算方式: \n  FPGA(100%) \n  ARM(0%)"));
     }else{

     }
    // ui->methodLabel->setText(tr("实际计算方式: \n  FPGA(100%) \n  ARM(0%)").append();
     ui->timeLabel->setText(tr("计算时间: %1 ms").arg(m_time.armtime+m_time.fpgatime) );//to edit
     free(fileretur);
     free(data);
     free(key);
     free(dataenc);
}
void DESMainWindow::on_decryptButton_clicked()
{
    //1. 取得文件内容
    QString mClearText = ui->ciphertText->toPlainText();
    mClearText = mClearText.toUpper();
    ui->ciphertText->setText(mClearText);
    QString mSecretKey = ui->secretKey->toPlainText();
    mSecretKey = mSecretKey.toUpper();
    ui->secretKey->setText(mSecretKey);
    if(ui->ciphertText->toPlainText() == ""){
        ui->statusBar->showMessage("Please type in the ciphert text!",5000);
        return;
    }
    if(mRadioButtonSelected == "NOMethod"){
        ui->statusBar->showMessage("Please select a method!",5000);
        return;
    }
    ui->clearText->setText("");

    /********/
    //2. 文本内容转化
   int datalen = mClearText.length();
   char* data = mClearText.toLatin1().data();
   data = (char*)StringToBits(data,&datalen);

   int keylen=16;
   char*  key=mSecretKey.toLatin1().data();
   key = (char*)StringToBits(key,&keylen);
    //3. 加密解密
    unsigned char* fileretur = DESDecryption ( (unsigned char*)data,datalen,(unsigned char*)key,keylen, m_isFPGA,&m_time);
    /********/
    char* dataenc = (char*)BitsToString((char*)fileretur,datalen);
   //4. 显示加密后内容
    ui->clearText->setText(QString(dataenc));
    ui->methodLabel->setText("METHOD: " + mRadioButtonSelected);
    ui->timeLabel->setText("TIME: " + QString::number(1) );//to edit

    if(m_time.howTo==1){ //ARM
       ui->methodLabel->setText(tr("实际计算方式: \n  FPGA(0%) \n  ARM(100%)"));
    }else if(m_time.howTo==2){//FPGA
         ui->methodLabel->setText(tr("实际计算方式: \n  FPGA(100%) \n  ARM(0%)"));
    }else{

    }
   // ui->methodLabel->setText(tr("实际计算方式: \n  FPGA(100%) \n  ARM(0%)").append();
    ui->timeLabel->setText(tr("计算时间: %1 ms").arg(m_time.armtime+m_time.fpgatime) );//to edit
    free(fileretur);
    free(data);
    free(key);
    free(dataenc);
}

void DESMainWindow::on_armRadioButton_clicked()
{
    mRadioButtonSelected = "ARM";//ARM
    m_isFPGA=0; //ARM
    ui->statusBar->showMessage("ARM method selected.",1000);
    ui->armRadioButton->setChecked(true);

    ui->armRadioButton_2->setChecked(true);
    on_armRadioButton_2_clicked(); //两边同时选
}

void DESMainWindow::on_fpgaRadioButton_clicked()
{
    mRadioButtonSelected = "FPGA";//FPGA
     m_isFPGA=2; //FPGA
    ui->statusBar->showMessage("FPGA method selected.",1000);
    ui->fpgaRadioButton->setChecked(true);
    ui->fpgaRadioButton_2->setChecked(true);
    on_fpgaRadioButton_2_clicked();//两边同时选
}

void DESMainWindow::on_exitButton_clicked()
{
    this->close();
}


void DESMainWindow::on_armRadioButton_2_clicked()
{
    mRadioButtonSelected = "ARM";//ARM
    m_isFPGA=0; //ARM
    ui->statusBar->showMessage("ARM method selected.",1000);
}

void DESMainWindow::on_fpgaRadioButton_2_clicked()
{
    mRadioButtonSelected = "FPGA";//FPGA
     m_isFPGA=2; //FPGA
    ui->statusBar->showMessage("FPGA method selected.",1000);
}


void DESMainWindow::on_pushButton_clicked()
{
    //1. 选择文件
#if 0
    fileName = QFileDialog::getOpenFileName(
                      "./map/",
                      "Images (*.bmp);;"
                      "Any files (*.*)",
                      this);
#endif
    fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "/home",
                tr("Images (*.png *.xpm *.jpg)"));

    if (!fileName.isEmpty())
    {
        QFileInfo fileinfo(fileName);
        desFilePath = fileName;
//        mImageInfo += ("\nLast read:" + fileinfo.lastRead().toString());
        ui->lineEdit->setText(fileName);
        ui->PlainSize_4->setText(QString(tr("明文大小: %1")).arg(fileinfo.size ()/1024) + "KB");

    }
    else
    {
        //statusBar()->message(tr("Opening aborted"), 2000);
    }


}

void DESMainWindow::on_pushButton_2_clicked()
{
   // ui->cipherSize->setText(QString(tr("密文大小： %1")).arg(1024) + "KB");
 m_time.howTo=0;
 m_time.armtime=0;
 m_time.fpgatime=0;
  if (fileName.isEmpty()) return;
    //2. 加密啊
//unsigned char* DESEncryptionFile
  //      (unsigned char* inputPath, int isFPGA,struct CGTimeInfo* timeinfo);

    char* inputPath = fileName.toLatin1().data();
    char* retuFile = (char*)DESEncryptionFile((unsigned char*)inputPath,m_isFPGA,&m_time);
    //3. 填写结果
    if(retuFile==NULL){

     }else{
        QFileInfo fileinfoa(retuFile);
        ui->label->setText(tr("加解密后路径:\n")+QString(retuFile));
        ui->cipherSize->setText(QString(tr("密文大小: %1")).arg(fileinfoa.size ()/1024) + "KB");
     }
    if(m_time.howTo==1){ //ARM
       ui->methodLabel_2->setText(tr("实际计算方式: \n  FPGA(0%) \n  ARM(100%)"));
    }else if(m_time.howTo==2){//FPGA
         ui->methodLabel_2->setText(tr("实际计算方式: \n  FPGA(100%) \n  ARM(0%)"));
    }else{
        // ui->methodLabel_2->setText(tr("实际计算方式: \n  FPGA(100%) \n  ARM(0%)").append();
    }
    ui->timeLabel_3->setText(tr("计算时间: %1 ms").arg(m_time.armtime+m_time.fpgatime) );//to edit
}


void DESMainWindow::on_pushButton_3_clicked()
{
    // ui->cipherSize->setText(QString(tr("密文大小： %1")).arg(1024) + "KB");
  m_time.howTo=0;
  m_time.armtime=0;
  m_time.fpgatime=0;
  if (fileName.isEmpty()) return;
     //2. 加密啊
 //unsigned char* DESEncryptionFile
   //      (unsigned char* inputPath, int isFPGA,struct CGTimeInfo* timeinfo);

     char* inputPath = fileName.toLatin1().data();
     char* retuFile = (char*)DESDecryptionFile((unsigned char*)inputPath,m_isFPGA,&m_time);
     //3. 填写结果
     if(retuFile==NULL){

      }else{
         QFileInfo fileinfoa(retuFile);
         ui->label->setText(tr("加解密后路径:\n")+QString(retuFile));
         ui->cipherSize->setText(QString(tr("密文大小: %1")).arg(fileinfoa.size ()/1024) + "KB");
      }
     if(m_time.howTo==1){ //ARM
        ui->methodLabel_2->setText(tr("实际计算方式: \n  FPGA(0%) \n  ARM(100%)"));
     }else if(m_time.howTo==2){//FPGA
          ui->methodLabel_2->setText(tr("实际计算方式: \n  FPGA(100%) \n  ARM(0%)"));
     }else{
         // ui->methodLabel_2->setText(tr("实际计算方式: \n  FPGA(100%) \n  ARM(0%)").append();
     }
     ui->timeLabel_3->setText(tr("计算时间: %1 ms").arg(m_time.armtime+m_time.fpgatime) );//to edit
}


void DESMainWindow::show1(){
    printf("void DESMainWindow::show1()\n");
    ui->tabWidget->setCurrentIndex(1);
}

void DESMainWindow::show2(){
    printf("void DESMainWindow::show2()\n");
    ui->tabWidget->setCurrentIndex(2);
}
