#ifndef FPGACG_SUMMARYTABLE_H
#define  FPGACG_SUMMARYTABLE_H

#include "fpgaCG-SupportedOpt.h"

struct SummaryItem{
	int index; //�ع������ı��
	char* optname; //�ع����������� ָ��
	
	int num; //�������
	int time; //ʱ��,��λ����
	int sourbytesize; //Դ�������ֽ���
	int tarbytesize; //Ŀ�Ĳ��� �ֽ���
};


struct CGHitoryTable{
	struct SummaryItem Arm_item[MAXOPFPT+1]; //����item[0]--fpga��������Ļ�����Ϣ�����-2
	                                     //item[1] -- arm ��������Ļ�����Ϣ�����-3
	struct SummaryItem FPGA_item[MAXOPFPT+1];
	int length; //��ʾ�������������ĸ���
};


/*���ܣ���supported�ع��������ѳ�ʼ����ϵ�ǰ���£�
       ��ʼ��Summary��Ϣ*/
int CGHSTSvrInit();


/*���ܣ���һ������ɵ�������Ϣ�����ܵ��������*/
int CGHSTCalOneFininshedTask(struct FinishedTask* task);


/*���ܣ���ӡ���е��ع���ʷ��Ϣ���ܱ�*/
void PrintfCHST();


//����������Ϣ��
void CGHSTTraverse(void (*pVisit)(struct SummaryItem*,struct SummaryItem*));
#endif