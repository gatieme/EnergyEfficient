#ifndef FPGACG_FPGASTATUS_H
#define FPGACG_FPGASTATUS_H

#include "fpgaCG-SupportedOpt.h"


/*fpgaStatus�ṹ����ռ�˸��ֽڵ��ַ�������
 unsigned char CGFPGAStatus[8]
 CGFPGAStatus[0] --- ��ǰ���ص�IP������
 CGFPGAStatus[1] --- ��ǰ�����IO�Ӱ�����
 CGFPGAStatus[2] --- FPGA״̬�֣����У������У�ʹ���У�
 CGFPGAStatus[3] --- FPGA�������ع��������֣����������ã�ǿ�ƣ�
 
 CGFPGAStatus[4] --- FPGA��IO�ع��������֣���ʱδ���壩
 CGFPGAStatus[5] --- ���ȼ����壨��ʱδ���壩
 ������δʹ��
 */
#define MAXFPGAStatusNum 8


//��fpga״̬��д����Ҫ����ͬ����ÿ��ֻ����һ��д�߳�
struct CGFPGAStatus{
	char status[MAXFPGAStatusNum];//�洢״̬��
	pthread_mutex_t  mutex[MAXFPGAStatusNum]; //�ź��� 
};




/*����IO�Ӱ�Ĳ�������*/
#define IO_NULL 0x00
#define IO_RS232 0x01
#define IO_RS422 0x02
#define IO_RS485 0x03
#define IO_CAN  0x04






/*���ܣ���ʼ��fpgastatus����*/
int CGFPGAStautsInit();


void PrintfFPGAStatus();




//д�뵱ǰ���ص�IP������
int FPGAStatusWriteIpType(char iptype);

//���ò���Ľӿ��Ӱ�����
int FPGAStatusWriteSubType(char subType);


//����fpgaʹ��״̬�����У�1���������У�2����ʹ���У�3����δ��ʼ������������ֵ����
//δ��ȫʵ��
int FPGAStatusWriteUsedState(char status);

//����fpga���ȿ�����(0--������1--ǿ��fpga���٣�2--����fpga����)
//�ͻ��˿������ñ��ֶ�
int FPGAStatusWriteDataControl(char control);





int FPGAStatusReadIpType();

int FPGAStatusReadSubType();


int FPGAStatusReadUsedState();


int FPGAStatusReadDataControl();


#endif