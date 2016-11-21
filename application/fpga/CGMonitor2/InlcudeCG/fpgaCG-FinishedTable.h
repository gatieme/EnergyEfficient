#ifndef FPGACG_FINISHEDTABLE

#define FPGACG_FINISHEDTABLE
#include <time.h>



#include "fpgaCG-OngoingTable.h"

/****************�ṹ�����˵��*********************/

#define MAXFTnum 10  //ֻ�������´����ǰ10���¼

//���е�ÿһ��
struct FinishedTask{
	int index; //��ţ�Ψһ������
	int optType;//��������
	int ArmOrFPGA;//������:1.ARM 2,FPGA, ����������Ĭ��ARM����
	
	int UsedTime; //����ʱ�䣨��ȷ��ms��
	int Cli_pid; //�ͻ���PID
	
	
	int sourMemSize;//��������С
  char sourOpt[8];
	int tarMemSize; //���ʵ��ռ�õĿռ��С
	char tarOpt[8];
		
}; 



//��ʾ������һ��ѭ������
typedef struct  CGFinishedTable {
	  
	struct FinishedTask  data[MAXFTnum]; /* ���飬�洢����Ԫ�� */
	
	int head;               /*ѭ�������һ��Ԫ��*/
	int end;                /*ѭ���������һ��Ԫ��*/
	//head������end�Ϳ��Ա�������end+1%MAXFTnum��һ��Ԫ��
} FTTable;

//ȫ�ֱ��� 



/********************����˵��******************/



/*���ܣ����һ��Task��FinishedTable�б���
������task����tarMemSize
����ֵ��������ţ����ڲ������񣬲�������*/
int CGFTAddOne(struct OngoningTask* task,int tarMemSize);

/*���ܣ�������������ӡ����*/
void PrintfFT();


/*���ܣ�����������FinshedTable��
  ����������ָ��
  ����ֵ�� void*/
void CGFTTraverse(void (*pVisit)(struct FinishedTask*));

/*���ܣ��ɱ�Ų�����������*/
struct FinishedTask* CGFTFindTaskByIndex(int index);

#endif