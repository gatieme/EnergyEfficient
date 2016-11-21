#ifndef FPGACG_FPGASTATUS_H
#define FPGACG_FPGASTATUS_H

#include "fpgaCG-SupportedOpt.h"


/*fpgaStatus结构就是占八个字节的字符串数组
 unsigned char CGFPGAStatus[8]
 CGFPGAStatus[0] --- 当前加载的IP核类型
 CGFPGAStatus[1] --- 当前插入的IO子板类型
 CGFPGAStatus[2] --- FPGA状态字（空闲，配置中，使用中）
 CGFPGAStatus[3] --- FPGA（数据重构）控制字（正常，禁用，强制）
 
 CGFPGAStatus[4] --- FPGA（IO重构）控制字（暂时未定义）
 CGFPGAStatus[5] --- 优先级定义（暂时未定义）
 其它的未使用
 */
#define MAXFPGAStatusNum 8


//对fpga状态的写操作要做到同步，每次只能有一个写线程
struct CGFPGAStatus{
	char status[MAXFPGAStatusNum];//存储状态字
	pthread_mutex_t  mutex[MAXFPGAStatusNum]; //信号量 
};




/*定义IO子板的插入类型*/
#define IO_NULL 0x00
#define IO_RS232 0x01
#define IO_RS422 0x02
#define IO_RS485 0x03
#define IO_CAN  0x04






/*功能：初始化fpgastatus数组*/
int CGFPGAStautsInit();


void PrintfFPGAStatus();




//写入当前加载的IP核类型
int FPGAStatusWriteIpType(char iptype);

//设置插入的接口子板类型
int FPGAStatusWriteSubType(char subType);


//设置fpga使用状态（空闲（1），配置中（2），使用中（3），未初始化（其它所有值））
//未完全实现
int FPGAStatusWriteUsedState(char status);

//设置fpga调度控制字(0--正常，1--强制fpga加速，2--进制fpga加速)
//客户端可以设置本字段
int FPGAStatusWriteDataControl(char control);





int FPGAStatusReadIpType();

int FPGAStatusReadSubType();


int FPGAStatusReadUsedState();


int FPGAStatusReadDataControl();


#endif