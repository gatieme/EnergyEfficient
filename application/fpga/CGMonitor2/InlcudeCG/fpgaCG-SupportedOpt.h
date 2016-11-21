#ifndef FPGACG_SUPPORTEDOPT
#define FPGACG_SUPPORTEDOPT


#include "fpgaCG-SharMemForStatus.h"
#include<dlfcn.h>  



#define NAMELEN 8 
#define PATHLEN 32
#define DESCRIPBELEN 128
#define CONFPATH "./fpgaCG.conf"
#define MAXOPFPT 8



struct CGOptTime{
	int datasize; //��λ�ֽ�
	int armtime;//��λms
	int fpgatime;	//��λms
	
	struct CGOptTime* pNext;
};

//��ʾ�ع������Ļ�����Ϣ���������ļ�������������Ϣ���浽����
//�����ع����������������
struct CGOptBaseInfo{ 
	char OptName[NAMELEN];
	char CliOptSoPath[PATHLEN];
	char SrvOptSoPath[PATHLEN];
	char IpCorePath[PATHLEN];
	char CliFuncName[16];
	char SrvArmFuncName[16];
	char SrvFPGAFuncName[16];
	char Describe[DESCRIPBELEN];
	
	int InitTime; //IP�˵ļ���ʱ��
	struct CGOptTime* time;  //ָ�����ʱ�������
	struct CGOptBaseInfo* pNext; //��һ��
};

//��������ָ�룬��׼�ĺ���ָ��ģ�壨Դ����ָ�룬Ŀ������ָ�룬Դ��С��Ŀ�����ֵ�����ؽ����С���������ֶΡ��Զ��塿��

typedef void (*CGFunc)(char*,char*,int,int*,void*) ;


//�ڴ��е��ع�����ָ���
struct CGOptFuncPointer{
	int index;                 //��ţ�fpga_status ���ص�IP�˱��
	char* OptName;     //������
	char* IpCorePath; //IP��·��,ָ�룬ָ��baseinfo�е�IpCore�ַ���
	void *handle ; //srv���ָ��
	
	CGFunc arm_Func; //ARM�����ĺ���ָ��
	CGFunc fpga_Func; //FPGA�����ĺ���ָ��
	
	struct CGOptBaseInfo* baseinfo; //�����Ļ�����Ϣ
}; 



//��ʾ ��������ָ���,�����ڹ����ڴ���
typedef struct  CGOptFuncPointerTable {
	  
	struct CGOptFuncPointer  data[MAXOPFPT]; /* ���飬�洢����Ԫ�� */
	int length;             /* ���Ա�ǰ���� */
	
} CGOPFPT;


extern struct CGALLTable* g_CGallTable; 

/*****************  CGOptBaseInfo  ����***************************/

/*���ܣ��������ļ���д�뵽֧�ֲ��������*/
int CGSOInitConf();



/*���ܣ����ݲ�����������g_CGOptHead�ع���������*/
struct CGOptBaseInfo* CGSOSearch(char* optName);


/*��ӡ����*/
//void VisitPrintf(struct CGOptBaseInfo* task);

/*���ܣ�������������ӡ����*/
extern void PrintfSOT();



/*****************���ڴ��еĺ���ָ���Ĳ���***************************/
/*���ܣ����ѳ�ʼ���õ�g_CGOptHead������д����ָ���*/
int CGOPFPTInit();

void PrintfOPFPTable();

/*���ܣ����ع��Ĳ��������ҵ���Ӧ����������
���أ�NULL ʧ��*/
struct CGOptFuncPointer* CGOPFOTFindTable(char* name);


/*���ܣ��ɱ�Ų��� IP��·��*/
char* CGOPFOFindIPCorePathByIndex(int index);

/*���ܣ��ɲ������֣����Ҷ�Ӧ�ı��*/
int  CGOPFOTFindIndexByName(char* name);

/*���ܣ��ɱ�Ų��� ����������
���أ�NULL ---û�ҵ�
     ����ָ�룬ָ�����ڴ�����*/
char* CGOPFOFindOptNameByIndex(int index);

//ָ��ת������srv�е�ָ�룬׼��Ϊ��ָ��
void* pointerConverter(void* old);
#endif
