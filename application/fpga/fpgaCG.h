//#include "fpgaCG-SupportedOpt.h"
//#include "fpgaCG-FinishedTable.h"
//#include "fpgaCG-SupportedOpt.h"
//#include "fpgaCG-SummaryTable.h"
//#include "fpgaCG-OngoingTable.h"
#ifndef FPGACG_H
#define FPGACG_H
extern "C" {
struct CGTimeInfo{
	unsigned int armtime; 
	unsigned int fpgatime; 
	unsigned int howTo; //ÈçºÎœøÐÐ²Ù×÷£¬1--ARM,2--FPGA,3--»ìºÏ
};
struct CGCalTaskReturn{

		char OptName[8]; //²Ù×÷Ãû³Æ£¬DES,JPEGµÈ 
		unsigned int howTo; //ÈçºÎœøÐÐ²Ù×÷£¬1--ARM,2--FPGA,3--»ìºÏ
		char result[256];
		unsigned int armtime; 
		unsigned int fpgatime; 
		int storeType; //1--socket×Ö·ûÖÐÎªœá¹û£¬2--±£ŽæÔÚÎÄŒþÖÐ	
		int index; //¿Í»§¶ËËùŽŠµÄÐòÁÐºÅ
};
typedef void (*FP_TaskReturn)(struct CGCalTaskReturn*);
extern unsigned char* DESEncryption (unsigned char* data, int datalen,unsigned char* key,int keylen,int isFPGA,struct CGTimeInfo* timeinfo);
extern unsigned char* DESDecryption (unsigned char* data, int datalen,unsigned char* key,int keylen,int isFPGA,struct CGTimeInfo* timeinfo);
extern unsigned char* DESEncryptionFile (unsigned char* inputPath, int isFPGA,struct CGTimeInfo* timeinfo);
extern unsigned char* DESDecryptionFile (unsigned char* inputPath, int isFPGA,struct CGTimeInfo* timeinfo);
extern unsigned char* DESEncryptionFileAsyn (unsigned char* inputPath, int isFPGA,struct CGTimeInfo* timeinfo,FP_TaskReturn func);
extern unsigned char* JPEGCompressPicutre (unsigned char* inputPath, int isFPGA,struct CGTimeInfo* timeinfo);
//¹Ø±ÕÁ¬œÓ
int CGCliClose();
//ÉêÇëŒà¿ØŽ°¿Ú
int CGCliMonOpen();
//È¡ÏûÈÎÎñ
int CGCliCancelTask(int item);
//ÈÎÎñÇšÒÆ
int CGCliMigrateTask(int item,int how);
//ÉèÖÃÊÇ·ñÖ§³ÖÄ³ÀàÐÍ×Ó°å
int CGCliSetSubID(int sub_type,int isSupport);
//设置调度策略 
//(0--负载均衡，1--强制fpga加速（效率优先），
//2--禁止fpga加速（能耗最低）,3--用户选择)
int CGCliSetDataControl(int status);


//ž÷ÖÖ±ížñÄ¬ÈÏŽòÓ¡º¯Êý
extern void PrintfOGT();
extern void PrintfOPFPTable();
extern void PrintfFPGAStatus();
extern void PrintfCHST();
extern void PrintfFT();
extern void PrintfSOT();

//ŽòÓ¡µÄÖØ¹¹ ×Ô¶šÒåœÓ¿Úº¯Êý



//³õÊŒ»¯º¯Êý
void CGCliInit();

int isStringBits(char* pstr);
char* BitsToString(char* Bits,int len);
unsigned char* StringToBits(char* pstr,int* bitslen);
}
#endif
