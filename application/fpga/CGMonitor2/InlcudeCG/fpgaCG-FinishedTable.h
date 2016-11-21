#ifndef FPGACG_FINISHEDTABLE

#define FPGACG_FINISHEDTABLE
#include <time.h>



#include "fpgaCG-OngoingTable.h"

/****************结构体变量说明*********************/

#define MAXFTnum 10  //只保留最新处理的前10项纪录

//表中的每一项
struct FinishedTask{
	int index; //序号，唯一就行了
	int optType;//操作类型
	int ArmOrFPGA;//处理方法:1.ARM 2,FPGA, 其它出错：但默认ARM处理
	
	int UsedTime; //处理时间（精确到ms）
	int Cli_pid; //客户端PID
	
	
	int sourMemSize;//操作数大小
  char sourOpt[8];
	int tarMemSize; //结果实际占用的空间大小
	char tarOpt[8];
		
}; 



//表示整个表，一个循环链表
typedef struct  CGFinishedTable {
	  
	struct FinishedTask  data[MAXFTnum]; /* 数组，存储数据元素 */
	
	int head;               /*循环链表第一个元素*/
	int end;                /*循环链表最后一个元素*/
	//head递增到end就可以遍历链表，end+1%MAXFTnum下一个元素
} FTTable;

//全局变量 



/********************函数说明******************/



/*功能：添加一项Task到FinishedTable列表中
参数：task任务，tarMemSize
返回值：返回序号，用于查找任务，操作任务*/
int CGFTAddOne(struct OngoningTask* task,int tarMemSize);

/*功能：遍历整个表，打印出来*/
void PrintfFT();


/*功能：遍历整个“FinshedTable”
  参数：函数指针
  返回值： void*/
void CGFTTraverse(void (*pVisit)(struct FinishedTask*));

/*功能：由编号查找整个任务*/
struct FinishedTask* CGFTFindTaskByIndex(int index);

#endif