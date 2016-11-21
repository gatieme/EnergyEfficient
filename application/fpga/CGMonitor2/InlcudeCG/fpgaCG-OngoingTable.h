#ifndef FPGACG_ONGONGINGTABLE

#define FPGACG_ONGONGINGTABLE
#include <time.h>



#include "fpgaCG-communication.h"
#include "fpgaCG-SharMemForStatus.h"

/****************�ṹ�����˵��*********************/

#define MAXOGTnum 20  //���ͬʱ����20������


//���е�ÿһ��
struct OngoningTask{
	int index; //��ţ�Ψһ������
	int optType;//��������
	int ArmOrFPGA;//������:1.ARM 2,FPGA, ����������Ĭ��ARM����
	int state; //��ǰ��״̬��1.������ 2.������ 3.����� ����������λ���ɸ��ñ�񣩣�
	clock_t StartTime; //��ʼʱ�䣨��ȷ��ms��
	int Cli_pid; //�ͻ���PID
	pthread_t SVR_tid; //����˴�����߳�TID
	
	int semaphoreKey; //�ź�����sem_id,����ֱ��ʹ�õ�
	
	int sourMemKey; //�����������ڴ�Ĵ�С
	int sourMemOffset;//������Դ���ڹ����ڴ��е�ƫ��
	int sourMemSize;//��������С
	void* sourMem; //�����ڴ���غ���׵�ַ
	
	int tarMemKey; //����Ŀ�Ĳ���������һ��
	int tarMemOffset;
	int tarMemSize; //�������ռ�����ռ�
	void* tarMem;
		
	void* control;//�����ֶΣ�ͬʱ��ֵ���ص���Ϣ
	
	int port; //�����¿��Ķ˿�
	int socket; //����������ͻ���ͨ��ʹ�õ��׽���
	
} ; 

typedef struct OngoningTask ElemType;  //������Ԫ������


//��ʾ������
typedef struct  CGOngoingTable {
	  
	ElemType data[MAXOGTnum]; /* ���飬�洢����Ԫ�� */
	int length;             /* ���Ա�ǰ���� */
	
} CGOGT;





/********************����˵��******************/


/*���ܣ���ʼ�������ڽ���������
       ��ʵ������0*/
int CGOGTInit();

/*���ܣ����һ��Task��Ongoing�б���
������task����howTo���ź�������ͻ��������õģ�
����ֵ��������ţ����ڲ������񣬲�������*/
int CGOGTAddOne(struct CGOptTask* task,int howTO, int semaphoreKey);

/*���ܣ�������������ӡ����*/
void PrintfOGT();

/*���ܣ������кţ������ź���SemaID*/
int CGOGTGetSemaID(int index);

/*���ܣ����index�ӿ�ʼ���ﵽ����Ϊֹ��������ʱ�䣬��λms*/
int CGOGTLastedTime(int index);

/*���ܣ�����index���Ӧ��stateֵ*/
int CGOGTSetState(int index, int state);

/*���ܣ�ȡ��index���Ӧ��stateֵ*/
int CGOGTGetState(int index);

int/*���ܣ�����index���Ӧ��srv_tidֵ*/
 CGOGTSetTid(int index, pthread_t tid1);

/*���ܣ�����������onGoingTable��
  ����������ָ��
  ����ֵ�� void*/
void CGOGTTraverse(void (*pVisit)(struct OngoningTask*));


/*���ܣ��ɱ�Ų�����������*/
struct OngoningTask* CGOGTFindTaskByIndex(int index);

#endif