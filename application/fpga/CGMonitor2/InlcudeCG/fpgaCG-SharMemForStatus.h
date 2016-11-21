#ifndef  fpgaCG_SharMemForStatus
#define fpgaCG_SharMemForStatus

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h> // for close
#include <arpa/inet.h>
 
#define ATSMKEY 9080  //服务端共享内存的编号，内置好的

#define SHAREMEMSIZE 8192
#define MAXSMFSSIZE SHAREMEMSIZE/64 //4096字节，

//在服务端，共享内存中，记录所有表格偏移的结构体体
struct CGALLTable{
	int MemMan_off; //内存管理结构体,相对于共享内存首地址
	int MemMan_byteSize;//字节偏移
	
	int FpgaStatus_off;//fpga状态偏移,偏移为-1表示未使用
	int FpgaStatus_num; //个数，所占空间sizeof*num
	
	int OnGoingTable_off; //正在进行的 task表
	int OnGoingTask_num;
	
	int FinishedTable_off;//已完成 task表
	int FinishedTask_num;
	
	int SupportedCGOptTable_off;//支持的重构操作 task表
	int SupportedCGOptTable_num;
	
	int HistorySummaryTable_off;//所有重构操作的 信息汇总表
	int HistorySummaryTable_num;
	
	void* srvPointer; //记录服务端指针
};

//管理是将共享内存分块的，每8字节一块，用来表示内存是否被占用
struct CGMemMange{
	void* mem_address; //内存空间的首地址,可分配空间的首地址
	int size; //内存的总大小
	
	int remainSize; //剩余空间的总大小，字节数
	//采用的bitmap形式，每8字节表示是否被占用	
  unsigned char bitmap[MAXSMFSSIZE]; //0表示没有使用，1表示使用了
};
/*功能：服务端申请共享内存*/
int CGCliSMFSInit();



void PrintfMemBitMap();
void PrintfAllTable();

//申请共享内存空间
void * CGCliSMFSMalloc(int size);

//由指针计算到共享内存处的偏移
int  CGSMFSCaculateOffset(void* point);

//由偏移，计算在共享内存处的偏移
//成功返回指针，失败返回NULL
void* CGSMFSGetPointer(int offset);

#endif