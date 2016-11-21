#ifndef FPGACG_ONGONGINGTABLE

#define FPGACG_ONGONGINGTABLE
#include <time.h>



#include "fpgaCG-communication.h"
#include "fpgaCG-SharMemForStatus.h"

/****************结构体变量说明*********************/

#define MAXOGTnum 20  //最多同时处理20项任务


//表中的每一项
struct OngoningTask{
	int index; //序号，唯一就行了
	int optType;//操作类型
	int ArmOrFPGA;//处理方法:1.ARM 2,FPGA, 其它出错：但默认ARM处理
	int state; //当前的状态（1.待处理 2.进行中 3.已完成 其它：空闲位（可复用表格））
	clock_t StartTime; //开始时间（精确到ms）
	int Cli_pid; //客户端PID
	pthread_t SVR_tid; //服务端处理的线程TID
	
	int semaphoreKey; //信号量的sem_id,可以直接使用的
	
	int sourMemKey; //操作数共享内存的大小
	int sourMemOffset;//操作数源，在共享内存中的偏移
	int sourMemSize;//操作数大小
	void* sourMem; //共享内存挂载后的首地址
	
	int tarMemKey; //保存目的操作数的那一堆
	int tarMemOffset;
	int tarMemSize; //结果所能占的最大空间
	void* tarMem;
		
	void* control;//控制字段，同时兼值返回的信息
	
	int port; //本地新开的端口
	int socket; //本项任务与客户端通信使用的套接字
	
} ; 

typedef struct OngoningTask ElemType;  //链表中元素类型


//表示整个表
typedef struct  CGOngoingTable {
	  
	ElemType data[MAXOGTnum]; /* 数组，存储数据元素 */
	int length;             /* 线性表当前长度 */
	
} CGOGT;





/********************函数说明******************/


/*功能：初始化“正在进行任务表格”
       其实就是置0*/
int CGOGTInit();

/*功能：添加一项Task到Ongoing列表中
参数：task任务，howTo，信号量（与客户端商量好的）
返回值：返回序号，用于查找任务，操作任务*/
int CGOGTAddOne(struct CGOptTask* task,int howTO, int semaphoreKey);

/*功能：遍历整个表，打印出来*/
void PrintfOGT();

/*功能：由序列号，返回信号量SemaID*/
int CGOGTGetSemaID(int index);

/*功能：获得index从开始手里到现在为止，经过的时间，单位ms*/
int CGOGTLastedTime(int index);

/*功能：设置index项对应，state值*/
int CGOGTSetState(int index, int state);

/*功能：取回index项对应，state值*/
int CGOGTGetState(int index);

int/*功能：设置index项对应，srv_tid值*/
 CGOGTSetTid(int index, pthread_t tid1);

/*功能：遍历整个“onGoingTable”
  参数：函数指针
  返回值： void*/
void CGOGTTraverse(void (*pVisit)(struct OngoningTask*));


/*功能：由编号查找整个任务*/
struct OngoningTask* CGOGTFindTaskByIndex(int index);

#endif