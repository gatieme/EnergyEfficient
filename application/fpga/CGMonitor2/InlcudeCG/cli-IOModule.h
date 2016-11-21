#include <time.h>
#include <sys/ipc.h> 
#include <sys/sem.h>
#include <sys/shm.h>  
#include <sys/ipc.h>  
#include <errno.h> 
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h> // for close
#include <arpa/inet.h>

#ifdef DEBUG
//#define printf_debug( ...) printf(##__VA_ARGS__)
#define printf_debug(fmt,arg...) printf(fmt,##arg)
#else
#define printf_debug(fmt,arg...)  
#endif


/********************�ͻ��� ���ļ��ĺ����ӿ�***********************/


/*���ܣ����ع�IO��
  ���أ��ɹ�---����һ����������Ϊ�ع�IO�ڵľ��
        ʧ��--����һ��С�ڵ���
        ����0 --- IO�˿�ʹ���У��Ժ�����*/
int CGIOOpen();

/*���ܣ�ͨ���ع�IO�ڣ�����һ���ַ�
  ���أ��ѷ����ַ��ĳ���
  ˵�����ַ����Ȳ�Ҫ256�ֽ�*/
int CGIOSend(int fd,char* buf, int len);


/*���ܣ�ͨ���ع�IO�ڣ����յ��ַ�
  ���أ��ѷ����ַ��ĳ���
  ˵����������socket��recv����Ҫ�ϲ�������ȡ��
        �뼰ʱȡ�����ݣ�������ܻᱻ�����ݸ���*/
int CGIORecv(int fd,char* buf, int len);

/*����:֪ͨ����������Ҫ�ͷŵ���IO��ʹ��*/
int CGIOClose(int fd);


/*���ܣ��ͻ�����������IOģ���IP��*/
char* g_IO_IP[] = {
			"RS232",
			"RS422",
			"RS485",
			"CAN",
			"NULL"}; //�յ�IP��
int CGIOConfig(int fd, char* ipname);

/*���ܣ���� ��ǰfpga�У����ص�IO IP������
  ���أ� 0 ---�ɹ�
         g_io_index---��ǰIO����IO�е�״̬*/
int CGIOGetType(int fd,int* g_io_index);

/*���ܣ��ӷ������ж�ȡIOģ��  ��ʷsend����
  ���أ�<0 ������
        ==buf�е�һ�ֽڣ����ܷ��ͼ�¼�����
        *len  ����buf��󳤶ȣ����bufȡ�����ݵĳ���
  */
int CGIOGetSendHis(int fd,char* buf, int* len);

/*���ܣ��ӷ������ж�ȡIOģ��  ��ʷrecv����
  ���أ�<0 ������
        ==buf�е�һ�ֽڣ����ܷ��ͼ�¼�����
        *len  ����buf��󳤶ȣ����bufȡ�����ݵĳ���
  */
int CGIOGetRecvHis(int fd,char* buf, int* len);
