#include <pthread.h>
#include <sys/ipc.h> 
#include <sys/sem.h>
#include <sys/shm.h>  
#include <sys/ipc.h>  
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ipc.h> 
#include <sys/sem.h>
#include <sys/shm.h>  
#include <sys/ipc.h>  
#include <errno.h> 
#ifdef DEBUG
//#define printf_debug( ...) printf(##__VA_ARGS__)
#define printf_debug(fmt,arg...) printf(fmt,##arg)
#else
#define printf_debug(fmt,arg...)  
#endif

/*-------------------------------------信号量的基本操作----------------------------------------*/

/*定义联合体*/
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

/*信号量初始化（赋值）函数*/
int init_sem(int sem_id,int init_value)
{
	union semun sem_union;
	sem_union.val=init_value;  /*init_value为初始值*/
	if(semctl(sem_id,0,SETVAL,sem_union)==-1)
	{
		perror("Initialize semaphore");
		return -1;
	}
	return 0;
}

/*从系统中删除信号量的函数*/
int del_sem(int sem_id)
{
	union semun sem_union;
	if(semctl(sem_id,0,IPC_RMID,sem_union)==-1)
	{
		perror("Delete semaphore");
		return -1;
	}
	return 0;
}

/*P 操作函数*/
int sem_p(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num=0;  /*信号量编号，这里单个信号量的编号应该为0*/
	sem_b.sem_op=-1; /*信号量操作，取值为-1表示P操作*/
	sem_b.sem_flg=SEM_UNDO; /*在进程没释放信号量而退出时，系统自动释放该进程中
							未释放的信号量*/
	if(semop(sem_id,&sem_b,1)==-1)	/*进行Ｐ操作*/
	{
		perror("P operation");
		return -1;
	}
	return 0;
}

/*V 操作函数*/
int sem_v(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num=0;  /*信号量编号，这里单个信号量的编号应该为0*/
	sem_b.sem_op=1; /*信号量操作，取值为+1表示V操作*/
	sem_b.sem_flg=SEM_UNDO; /*在进程没释放信号量而退出时，系统自动释放该进程中
							未释放的信号量*/
	if(semop(sem_id,&sem_b,1)==-1)	/*进行V 操作*/
	{
		perror("V operation");
		return -1;
	}
	return 0;
}


/*---------------------辅助函数----------------------------------*/
unsigned long get_file_size(const char *path)  
{  
    unsigned long filesize = -1;      
    struct stat statbuff;  
    if(stat(path, &statbuff) < 0){  
        return -1;  
    }else{  
        filesize = statbuff.st_size;  
    }  
    return filesize;  
} 
//检查1个字符串，是否为16进制字符串
//返回：1--是16进制字符串，其它--不是16进制字符串
int isStringBits(char* pstr){
	
	int i=0;
	int len = strlen(pstr);
	if(len%2 ==1) return -1;//不是偶数个字符，不能转换
	int flag=0;
	while(pstr[i]!='\0'){
		flag=0;
		if(pstr[i]>='0' && pstr[i]<='9') flag=1;
		if(pstr[i]>='A' && pstr[i]<='F'){
			pstr[i] = pstr[i]-'A'+'a';
			flag=1;
		} 
		if(pstr[i]>='a' && pstr[i]<='f') flag=1;
		if(flag!=1) return -2;
		i++;
	}
	
	return 1;
}
//16进制转成字符串,记得free内存
char* BitsToString(char* Bits,int len){
	if(Bits==NULL || len<=0) return NULL;
		
	char* ret = (char*)malloc(len*2+1);
	int i=0;
	for(i=0;i<len;i++){
		sprintf(&(ret[i*2]),"%02x",(unsigned char)Bits[i]);	
	}
	ret[len*2]=0x0;	
	return ret;
}

//字符串转成16进制,记得free内存
unsigned char* StringToBits(char* pstr,int* bitslen){
	
	//1. 检查是否有不合法字符，同时大写字符转小写
	int ret = isStringBits(pstr);

	if(ret!=1) return NULL;
	
	//2. 每两个字符，变为一字节
	int i=0;int len=0;
	len = strlen(pstr);
	*bitslen = len/2;
	
	unsigned char* bits=malloc(len/2);
	unsigned char highBit;
	unsigned char lowBit;
	for(i=0;i<len;i+=2){
		highBit=pstr[i];
		lowBit=pstr[i+1];
		
		if(highBit>='0'&& highBit<='9') highBit=highBit-'0';
		else highBit=10+highBit-'a';
			
		if(lowBit>='0'&& lowBit<='9') lowBit=lowBit-'0';
		else lowBit=10+lowBit-'a';
			
		bits[i/2]=16*highBit+lowBit;
	}
	return bits;
}


/*-----------------------------共享内存相关的函数等---------------------------------*/
void PrintfShmidDs(int shmid,int key );
 //获得一个内存区段的信息  
void PrintfShmidDs(int shmid,int key ){
	
	
	if(shmid == 0 || shmid <-1) return;
	struct shmid_ds shmds;  
	//shmid=shmget( MY_SHM_ID,0,0 );//示例怎样获得一个共享内存的标识符  
	int ret=shmctl( shmid,IPC_STAT,&shmds );  	
	if( ret==0 ){  
		
		printf_debug( "\n-----------shmid_ds key(%08x) -------------\n" ,key);  
		//获得系统中页面的大小  
	 printf_debug( "page size=%d\n",getpagesize(  ) );  
	 printf_debug( "size of segment (bytes): %d\n",shmds.shm_segsz );  
   printf_debug( "no. of current attaches: %d\n",( int )shmds.shm_nattch );  
   printf_debug( "pid of creator : %d\n",( int )shmds.shm_cpid ); 
   printf_debug( "pid of last operator : %d\n",( int )shmds.shm_lpid );
   printf_debug( "-----------shmid_ds end-------------\n" );     
 		}else  {
 	
 		 printf( "[WARING]:shmctl(  ) call failed\n" );  
 		}
}
