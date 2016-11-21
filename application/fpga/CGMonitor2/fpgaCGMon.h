#ifndef FPGACGMON__
#define FPGACGMON__




#ifdef __cplusplus
extern "C"{
#endif
/*IO 模块*/
//int CGIOOpen();
int CGIOMon();
int CGIOSetSubType(int fd, int IO_TYPE,int isValid);

/*初始化*/
int CGCliSMFSInit();
void CGOPCliInit();

void* pointerConverter(void* old)   ;
/*支持操作链表*/
#define NAMELEN 8
#define PATHLEN 32
#define DESCRIPBELEN 128
#define CONFPATH "./fpgaCG.conf"
#define MAXOPFPT 8
struct CGOptTime{
    int datasize; //µ¥Î»×ÖœÚ
    int armtime;//µ¥Î»ms
    int fpgatime;	//µ¥Î»ms

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
void CGSOTraverse(void (*pVisit)(struct CGOptBaseInfo*));
char* CGOPFOFindOptNameByIndex(int index);
char* CGOPFOFindIPCorePathByIndex(int index);
void  PrintfSOT();


/*正在进行的任务*/
#define MAXOGTnum 20  //×î¶àÍ¬Ê±ŽŠÀí20ÏîÈÎÎñ
/*功能：遍历整个“onGoingTable”
  参数：函数指针
  返回值： void*/
//表中的每一项
//表中的每一项
struct OngoningTask{
    int index; //序号，唯一就行了,服务端编号
    int optType;//操作类型
    int ArmOrFPGA;//cli要求的处理方法:1.ARM 2,FPGA, 其它出错：但默认ARM处理
    int realHow; //实际的处理方法：1.ARM 2,FPGA, 3. 混合 其它未处理
    int state; //当前的状态（1.待处理 2.进行中 3.已完成 其它：空闲位（可复用表格））
    clock_t StartTime; //开始时间（精确到ms）
    int Cli_pid; //客户端PID
    int Cli_index; //客户端任务序号
    int parent_index; //任务的母任务index，没有

    int storeType; //2--sourMem指向源操作数字符串，1--sourMem指向文件
    int sourOffset; //操作的偏移，母任务用于判断是否完成
    int sourMemSize;//操作数大小
    char* sourMem; //源操作数

    char* tarFilePath;//
    char* control;//其它信息
    int controlSize;
    int other;//其它附加信息， 对于DES 1--加密 2--解密
    int socket; //本项任务与客户端通信使用的套接字

    int armTime; //arm计算时间
    int fpgaTime; //FPGA计算时间
    int ret;     //返回值

} ;
void CGOGTTraverse(void (*pVisit)(struct OngoningTask*));
void PrintfOGT();


/*以完成任务的任务*/
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
/*功能：遍历整个“FinshedTable”
  参数：函数指针
  返回值： void*/
void CGFTTraverse(void (*pVisit)(struct FinishedTask*));
void PrintfFT();


/*历史统计数据*/
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

void PrintfCHST();
//遍历汇总信息表，
void CGHSTTraverse(void (*pVisit)(struct SummaryItem*,struct SummaryItem*));


/*历史统计数据*/


/*fpgaStatus结构就是占八个字节的字符串数组
 unsigned char CGFPGAStatus[8]
 CGFPGAStatus[0] --- 当前加载的IP核类型
 CGFPGAStatus[1] --- 当前插入的IO子板类型
 CGFPGAStatus[2] --- FPGA状态字（空闲，配置中，使用中）
 CGFPGAStatus[3] --- FPGA（数据重构）控制字（正常，禁用，强制）

 CGFPGAStatus[4] --- FPGA（IO重构）控制字（暂时未定义）
 CGFPGAStatus[5] --- 优先级定义（暂时未定义）
 其它的未使用
 */
#define MAXFPGAStatusNum 8


//对fpga状态的写操作要做到同步，每次只能有一个写线程
struct CGFPGAStatus{
    char status[MAXFPGAStatusNum];//存储状态字
    pthread_mutex_t  mutex[MAXFPGAStatusNum]; //信号量
};
/*定义IO子板的插入类型*/
#define IO_NULL 0x00
#define IO_RS232 0x01
#define IO_RS422 0x02
#define IO_RS485 0x03
#define IO_CAN  0x04


#define IPCORE_TYPE_RS232 0xcd
#define IPCORE_TYPE_RS422 0xce
#define IPCORE_TYPE_RS485 0xcf
#define IPCORE_TYPE_CAN 0xca

#define IPCORE_PATH_CAN "/usr/fpga/can.bit"
#define IPCORE_PATH_RS232 "/usr/fpga/rs232.bit"
#define IPCORE_PATH_RS422 "/usr/fpga/rs422.bit"
#define IPCORE_PATH_RS485 "/usr/fpga/rs485.bit"

/*功能：初始化fpgastatus数组*/
int CGFPGAStautsInit();
void PrintfFPGAStatus();

//设置fpga调度控制字(0--正常，1--强制fpga加速，2--进制fpga加速)
//客户端可以设置本字段
//int FPGAStatusWriteDataControl(char control);
int FPGAStatusReadIpType();
int FPGAStatusReadSubType();
//解释fpga状态（空闲（1），配置中（2）
//，使用中（3），未初始化（其它所有值）
int FPGAStatusReadUsedState();
int FPGAStatusReadDataControl();
char FPGAStatusReadIOControl();


int machine_init(struct statics * statics);
void get_system_info(struct system_info *info);
void read_one_proc_stat(pid_t pid, struct top_proc *proc);
char *format_next_process(struct top_proc *p);


void PrintfOPFPTable();




/*IO*/

int CGCliSendSetDataControl(int status);

#ifdef __cplusplus
}
#endif

#endif


