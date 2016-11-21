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
 
#define ATSMKEY 9080  //����˹����ڴ�ı�ţ����úõ�

#define SHAREMEMSIZE 8192
#define MAXSMFSSIZE SHAREMEMSIZE/64 //4096�ֽڣ�

//�ڷ���ˣ������ڴ��У���¼���б��ƫ�ƵĽṹ����
struct CGALLTable{
	int MemMan_off; //�ڴ����ṹ��,����ڹ����ڴ��׵�ַ
	int MemMan_byteSize;//�ֽ�ƫ��
	
	int FpgaStatus_off;//fpga״̬ƫ��,ƫ��Ϊ-1��ʾδʹ��
	int FpgaStatus_num; //��������ռ�ռ�sizeof*num
	
	int OnGoingTable_off; //���ڽ��е� task��
	int OnGoingTask_num;
	
	int FinishedTable_off;//����� task��
	int FinishedTask_num;
	
	int SupportedCGOptTable_off;//֧�ֵ��ع����� task��
	int SupportedCGOptTable_num;
	
	int HistorySummaryTable_off;//�����ع������� ��Ϣ���ܱ�
	int HistorySummaryTable_num;
	
	void* srvPointer; //��¼�����ָ��
};

//�����ǽ������ڴ�ֿ�ģ�ÿ8�ֽ�һ�飬������ʾ�ڴ��Ƿ�ռ��
struct CGMemMange{
	void* mem_address; //�ڴ�ռ���׵�ַ,�ɷ���ռ���׵�ַ
	int size; //�ڴ���ܴ�С
	
	int remainSize; //ʣ��ռ���ܴ�С���ֽ���
	//���õ�bitmap��ʽ��ÿ8�ֽڱ�ʾ�Ƿ�ռ��	
  unsigned char bitmap[MAXSMFSSIZE]; //0��ʾû��ʹ�ã�1��ʾʹ����
};
/*���ܣ���������빲���ڴ�*/
int CGCliSMFSInit();



void PrintfMemBitMap();
void PrintfAllTable();

//���빲���ڴ�ռ�
void * CGCliSMFSMalloc(int size);

//��ָ����㵽�����ڴ洦��ƫ��
int  CGSMFSCaculateOffset(void* point);

//��ƫ�ƣ������ڹ����ڴ洦��ƫ��
//�ɹ�����ָ�룬ʧ�ܷ���NULL
void* CGSMFSGetPointer(int offset);

#endif