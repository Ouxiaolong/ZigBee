/***************************************************
开发者：龙创科技

开发平台：CC2530

日期：2016.1

内容：DMA
***************************************************/

#include <ioCC2530.h>
#include "Uart.h"
#include "hal.h"

#define KEY1 P0_1 
#define KEY2 P2_0

#define LED1 P1_0
#define LED2 P1_1
#define LED3 P1_4

//函数声明
void Configure_DMADataStruct(void);
void DMA_Configure(void);
void Start_DMA(void);
void Data_Check(void);

//变量定义
DMA_DESC DMAConfigure;
char sourceString[] = "This is a test string used to demonstrate DMA transfer.";
char destString[ sizeof(sourceString) ];
uchar Flag=0;


/**************************************************
 函 数 名  : main
 功能描述  : DMA测试(手动按下KEY1进行DMA测试，将测试结果发给电脑)
 输入参数  : NONE  
 输出参数  : NONE
 返 回 值  : NONE
***************************************************/
void main(void)
{    
    SetSysClock();
    
    InitUART();
    
    memset(destString, 0, sizeof(destString) );//Clearing the destination
   
    Configure_DMADataStruct();/*1、DMA使用步骤一：DMA 配置数据结构*/
      
    DMA_Configure();/*2、DMA使用步骤二：DMA 寄存器配置*/

    Start_DMA();
   
    Data_Check();
   
    while(1);
}


/**************************************************
 函 数 名  : Configure_DMADataStruct
 功能描述  : DMA 配置数据结构
 输入参数  : NONE
 输出参数  : NONE
 返 回 值  : NONE
***************************************************/
void Configure_DMADataStruct(void)
{

    SET_WORD(DMAConfigure.SRCADDRH, DMAConfigure.SRCADDRL,   &sourceString); // 1、DMA通道源地址
    SET_WORD(DMAConfigure.DESTADDRH, DMAConfigure.DESTADDRL, &destString);   // 2、DMA通道目的地址
    SET_WORD(DMAConfigure.LENH, DMAConfigure.LENL, sizeof(sourceString));    // 3、DMA的通道传送长度
    DMAConfigure.VLEN      = VLEN_USE_LEN;  // 4、可变长度传输模式
    DMAConfigure.WORDSIZE  = WORDSIZE_BYTE; // 5、选择每个DMA传送是采用8位(0) 还是16位(1)
    DMAConfigure.TMODE     = TMODE_BLOCK;   // 6、DMA通道传送模式
    DMAConfigure.TRIG      = DMATRIG_NONE;  // 7、选择要使用的DMA触发(本例程选择由用户强制开始传送)
    DMAConfigure.SRCINC    = SRCINC_1;      // 8、源地址递增模式(每次传送之后)
    DMAConfigure.DESTINC   = DESTINC_1;     // 9、目的地址递增模式(每次传送之后)
    DMAConfigure.IRQMASK   = FALSE;         // 10、该通道的中断屏蔽    
    DMAConfigure.M8        = M8_USE_8_BITS; // 11、采用VLEN的第8位模式作为传送单位长度；仅应用在WORDSIZE=0且VLEN从000到111时
    DMAConfigure.PRIORITY  = PRI_HIGH;      // 12、DMA通道的优先级别    
}    


/**************************************************
 函 数 名  : DMA_Configure
 功能描述  : DMA 寄存器配置(本实验用DMA通道0)
 输入参数  : NONE
 输出参数  : NONE
 返 回 值  : NONE
***************************************************/
void DMA_Configure(void)
{
    DMA_SET_ADDR_DESC0(&DMAConfigure);//1、DMA 通道进入工作状态(DMA0CFGH、DMA0CFGL)
    DMA_ABORT_CHANNEL(0);//2、停止所有通道，并选择通道0(DMAARM)
    DMA_ARM_CHANNEL(0);//3、选择通道0(DMAARM)
}


/**************************************************
 函 数 名  : Start_DMA
 功能描述  : 启动DMA并等待数据传输完成
 输入参数  : NONE
 输出参数  : NONE
 返 回 值  : NONE
***************************************************/
void Start_DMA(void)
{
    UartSend_String("Start DMA.\n",sizeof("Start DMA.\n"));  //发送数据
    Delayms(100); 
    
    while(KEY1) //检测到按键KEY1，设定DMA从RAM里转出数据
    
    Delayms(100);

    DMAIRQ = 0x00;//清中断标志
    DMA_START_CHANNEL(0);//DMAREQ0置位---启动DMA
    while(!(DMAIRQ & DMA_CHANNEL_0));//等待传输完毕，中断标志置位
}


/**************************************************
 函 数 名  : Data_Check
 功能描述  : 比较源数据与目标数据是否一致
 输入参数  : NONE
 输出参数  : NONE
 返 回 值  : NONE
***************************************************/
void Data_Check(void)
{
    uchar i;
    uchar errors = 0;
    
    for(i=0;i<sizeof(sourceString);i++)
    {
        if(sourceString[i] != destString[i])
        errors++; //记录错误的数据个数
    }

    if(errors == 0)
    {
        UartSend_String("The test of DMA is successful.\n",sizeof("The test of DMA is successful.\n"));  //发送数据
        LED3=1;//用作指示

    }
    else
    {
        UartSend_String("The test of DMA is failed.\n",sizeof("The test of DMA is failed.\n"));  //发送数据
    }    
}

/*********************************************END OF FILE**********************/
