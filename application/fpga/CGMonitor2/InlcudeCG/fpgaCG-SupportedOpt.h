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
	int datasize; //单位字节
	int armtime;//单位ms
	int fpgatime;	//单位ms
	
	struct CGOptTime* pNext;
};

//显示重构操作的基本信息，从配置文件解析出来的信息保存到这里
//整个重构操作表，是链表操作
struct CGOptBaseInfo{ 
	char OptName[NAMELEN];
	char CliOptSoPath[PATHLEN];
	char SrvOptSoPath[PATHLEN];
	char IpCorePath[PATHLEN];
	char CliFuncName[16];
	char SrvArmFuncName[16];
	char SrvFPGAFuncName[16];
	char Describe[DESCRIPBELEN];
	
	int InitTime; //IP核的加载时间
	struct CGOptTime* time;  //指向操作时间的链表
	struct CGOptBaseInfo* pNext; //下一项
};

//声明函数指针，标准的函数指针模板（源数据指针，目的数据指针，源大小，目的最大值【返回结果大小】，控制字段【自定义】）

typedef void (*CGFunc)(char*,char*,int,int*,void*) ;


//内存中的重构函数指针表
struct CGOptFuncPointer{
	int index;                 //编号，fpga_status 加载的IP核编号
	char* OptName;     //操作名
	char* IpCorePath; //IP核路径,指针，指向baseinfo中的IpCore字符串
	void *handle ; //srv库的指针
	
	CGFunc arm_Func; //ARM操作的函数指针
	CGFunc fpga_Func; //FPGA操作的函数指针
	
	struct CGOptBaseInfo* baseinfo; //其它的基本信息
}; 



//表示 整个函数指针表,保存在共享内存中
typedef struct  CGOptFuncPointerTable {
	  
	struct CGOptFuncPointer  data[MAXOPFPT]; /* 数组，存储数据元素 */
	int length;             /* 线性表当前长度 */
	
} CGOPFPT;


extern struct CGALLTable* g_CGallTable; 

/*****************  CGOptBaseInfo  函数***************************/

/*功能：读配置文件，写入到支持操作表格中*/
int CGSOInitConf();



/*功能：根据操作名，搜索g_CGOptHead重构操作链表，*/
struct CGOptBaseInfo* CGSOSearch(char* optName);


/*打印操作*/
//void VisitPrintf(struct CGOptBaseInfo* task);

/*功能：遍历整个表，打印出来*/
extern void PrintfSOT();



/*****************对内存中的函数指针表的操作***************************/
/*功能：由已初始化好的g_CGOptHead链表，填写函数指针表*/
int CGOPFPTInit();

void PrintfOPFPTable();

/*功能：由重构的操作名，找到对应的整个表项
返回：NULL 失败*/
struct CGOptFuncPointer* CGOPFOTFindTable(char* name);


/*功能：由编号查找 IP核路径*/
char* CGOPFOFindIPCorePathByIndex(int index);

/*功能：由操作名字，查找对应的编号*/
int  CGOPFOTFindIndexByName(char* name);

/*功能：由编号查找 操作的名字
返回：NULL ---没找到
     名字指针，指向共享内存区间*/
char* CGOPFOFindOptNameByIndex(int index);

//指针转换，由srv中的指针，准备为新指针
void* pointerConverter(void* old);
#endif
