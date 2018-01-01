/**
  ******************************************************************************
  * @file        InitUART_Timer.h
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       初始化
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**宏定义******************************************************/
//定义数据类型
#define uint unsigned int
#define uchar unsigned char

//定义IO口
#define LED1   P1_0	        //定义LED1为P10口控制
#define LED2   P1_1	        //定义LED2为P11口控制
#define LED3   P1_4	        //定义LED3为P14口控制
// Data
typedef unsigned char       BYTE;

// Unsigned numbers
typedef unsigned char       UINT8;
typedef unsigned char       INT8U;
typedef unsigned short      UINT16;
typedef unsigned short      INT16U;
typedef unsigned long       UINT32;
typedef unsigned long       INT32U;

// Signed numbers
typedef signed char         INT8;
typedef signed short        INT16;
typedef signed long         INT32;

#define DISABLE_ALL_INTERRUPTS() (IEN0 = IEN1 = IEN2 = 0x00)//三个

/**************************
系统时钟 不分频
计数时钟 32分频
**************************/
void InitClock(void)
{  
  CLKCONCMD &= ~0x40; // 设置系统时钟源为 32MHZ晶振
  while(CLKCONSTA & 0x40);                     // 等待晶振稳定 
  CLKCONCMD &= ~0x47;                          // 设置系统主时钟频率为 32MHZ
}
/****************************
//初始化程序
*****************************/
void InitLed(void)
{
  P1DIR |= 0x13; //P1_0、P1_1定义为输出
  LED1 = 0;       //LED1灯熄灭
  LED2 = 0;    
  LED3 = 0;
}
/****************************
T3初始化
****************************/
void InitT3(void)
{
  T3CCTL0 = 0X44;        // T3CCTL0 (0xCC)，CH0 中断使能，CH0 比较模式
  T3CC0 = 0xFA;          // T3CC0设置为250
  T3CTL |= 0x9A;         // 启动T3计数器，计数时钟为16分频。使用MODULO模式
  IEN1 |= 0X08;     
  IEN0 |= 0X80;          //开总中断，开T3中断
}
/*****************************************
 串口初始化函数：初始化串口 UART0		
*****************************************/
void InitUART0(void)
{
  PERCFG = 0x00;	           //位置1 P0口
  P0SEL = 0x3c;	                   //P0用作串口
  P2DIR &= ~0XC0;                  //P0优先作为UART0    
  U0CSR |= 0x80;   	           //串口设置为UART方式
  U0GCR |= 11;				
  U0BAUD |= 216;		    //波特率设为115200
  UTX0IF = 1;                       //UART0 TX中断标志初始置位1  
  U0CSR |= 0X40;                     //允许接收      
  IEN0 |= 0x84;		             //开总中断，接收中断
        

}

/****************************************************************
   串口发送字符串函数						
****************************************************************/
void UartTX_Send_String(char *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
     U0DBUF = 0x0A;        // 换行
    while(UTX0IF == 0);
      UTX0IF = 0;
}


/****************************************************************
  延时函数				
************************************************************/
void Delay(uint n)
{
	uint i;
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
}

/****************************
//延时函数
*****************************/
void Delayms(uint xms)   //i=xms 即延时i毫秒 (16M晶振时候大约数，32M需要修改，系统不修改默认使用内部16M)
{
 uint i,j;
 for(i=xms;i>0;i--)
   for(j=587;j>0;j--);
} 






