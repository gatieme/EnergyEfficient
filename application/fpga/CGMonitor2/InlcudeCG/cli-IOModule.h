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


/********************客户端 看的见的函数接口***********************/


/*功能：打开重构IO口
  返回：成功---返回一个正数，作为重构IO口的句柄
        失败--返回一个小于的数
        返回0 --- IO端口使用中，稍后再试*/
int CGIOOpen();

/*功能：通过重构IO口，发送一串字符
  返回：已发送字符的长度
  说明：字符长度不要256字节*/
int CGIOSend(int fd,char* buf, int len);


/*功能：通过重构IO口，接收到字符
  返回：已发送字符的长度
  说明：类似于socket的recv，需要上层主动来取，
        请及时取走数据，否则可能会被新数据覆盖*/
int CGIORecv(int fd,char* buf, int len);

/*功能:通知服务器，我要释放掉对IO的使用*/
int CGIOClose(int fd);


/*功能：客户端主动配置IO模块的IP核*/
char* g_IO_IP[] = {
			"RS232",
			"RS422",
			"RS485",
			"CAN",
			"NULL"}; //空的IP核
int CGIOConfig(int fd, char* ipname);

/*功能：获得 当前fpga中，加载的IO IP核类型
  返回： 0 ---成功
         g_io_index---当前IO核在IO中的状态*/
int CGIOGetType(int fd,int* g_io_index);

/*功能：从服务器中读取IO模块  历史send数据
  返回：<0 出错了
        ==buf中第一字节，在总发送记录的序号
        *len  输入buf最大长度，输出buf取到数据的长度
  */
int CGIOGetSendHis(int fd,char* buf, int* len);

/*功能：从服务器中读取IO模块  历史recv数据
  返回：<0 出错了
        ==buf中第一字节，在总发送记录的序号
        *len  输入buf最大长度，输出buf取到数据的长度
  */
int CGIOGetRecvHis(int fd,char* buf, int* len);
