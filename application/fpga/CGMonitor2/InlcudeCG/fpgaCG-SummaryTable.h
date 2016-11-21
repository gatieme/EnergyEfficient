#ifndef FPGACG_SUMMARYTABLE_H
#define  FPGACG_SUMMARYTABLE_H

#include "fpgaCG-SupportedOpt.h"

struct SummaryItem{
	int index; //重构操作的编号
	char* optname; //重构操作的名字 指针
	
	int num; //任务个数
	int time; //时间,单位毫秒
	int sourbytesize; //源操作的字节数
	int tarbytesize; //目的操作 字节数
};


struct CGHitoryTable{
	struct SummaryItem Arm_item[MAXOPFPT+1]; //其中item[0]--fpga所有任务的汇总信息，编号-2
	                                     //item[1] -- arm 所有任务的汇总信息，编号-3
	struct SummaryItem FPGA_item[MAXOPFPT+1];
	int length; //表示表中有意义数的个数
};


/*功能：在supported重构操作表已初始化完毕的前提下，
       初始化Summary信息*/
int CGHSTSvrInit();


/*功能：将一项已完成的任务，信息，汇总到这个表中*/
int CGHSTCalOneFininshedTask(struct FinishedTask* task);


/*功能：打印所有的重构历史信息汇总表*/
void PrintfCHST();


//遍历汇总信息表，
void CGHSTTraverse(void (*pVisit)(struct SummaryItem*,struct SummaryItem*));
#endif