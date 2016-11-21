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

/*-------------------------------------�ź����Ļ�������----------------------------------------*/

/*����������*/
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

/*�ź�����ʼ������ֵ������*/
int init_sem(int sem_id,int init_value)
{
	union semun sem_union;
	sem_union.val=init_value;  /*init_valueΪ��ʼֵ*/
	if(semctl(sem_id,0,SETVAL,sem_union)==-1)
	{
		perror("Initialize semaphore");
		return -1;
	}
	return 0;
}

/*��ϵͳ��ɾ���ź����ĺ���*/
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

/*P ��������*/
int sem_p(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num=0;  /*�ź�����ţ����ﵥ���ź����ı��Ӧ��Ϊ0*/
	sem_b.sem_op=-1; /*�ź���������ȡֵΪ-1��ʾP����*/
	sem_b.sem_flg=SEM_UNDO; /*�ڽ���û�ͷ��ź������˳�ʱ��ϵͳ�Զ��ͷŸý�����
							δ�ͷŵ��ź���*/
	if(semop(sem_id,&sem_b,1)==-1)	/*���Ув���*/
	{
		perror("P operation");
		return -1;
	}
	return 0;
}

/*V ��������*/
int sem_v(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num=0;  /*�ź�����ţ����ﵥ���ź����ı��Ӧ��Ϊ0*/
	sem_b.sem_op=1; /*�ź���������ȡֵΪ+1��ʾV����*/
	sem_b.sem_flg=SEM_UNDO; /*�ڽ���û�ͷ��ź������˳�ʱ��ϵͳ�Զ��ͷŸý�����
							δ�ͷŵ��ź���*/
	if(semop(sem_id,&sem_b,1)==-1)	/*����V ����*/
	{
		perror("V operation");
		return -1;
	}
	return 0;
}


/*---------------------��������----------------------------------*/
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
//���1���ַ������Ƿ�Ϊ16�����ַ���
//���أ�1--��16�����ַ���������--����16�����ַ���
int isStringBits(char* pstr){
	
	int i=0;
	int len = strlen(pstr);
	if(len%2 ==1) return -1;//����ż�����ַ�������ת��
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
//16����ת���ַ���,�ǵ�free�ڴ�
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

//�ַ���ת��16����,�ǵ�free�ڴ�
unsigned char* StringToBits(char* pstr,int* bitslen){
	
	//1. ����Ƿ��в��Ϸ��ַ���ͬʱ��д�ַ�תСд
	int ret = isStringBits(pstr);

	if(ret!=1) return NULL;
	
	//2. ÿ�����ַ�����Ϊһ�ֽ�
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


/*-----------------------------�����ڴ���صĺ�����---------------------------------*/
void PrintfShmidDs(int shmid,int key );
 //���һ���ڴ����ε���Ϣ  
void PrintfShmidDs(int shmid,int key ){
	
	
	if(shmid == 0 || shmid <-1) return;
	struct shmid_ds shmds;  
	//shmid=shmget( MY_SHM_ID,0,0 );//ʾ���������һ�������ڴ�ı�ʶ��  
	int ret=shmctl( shmid,IPC_STAT,&shmds );  	
	if( ret==0 ){  
		
		printf_debug( "\n-----------shmid_ds key(%08x) -------------\n" ,key);  
		//���ϵͳ��ҳ��Ĵ�С  
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
