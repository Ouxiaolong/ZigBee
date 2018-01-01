#include <ioCC2530.h>
#define uint unsigned int
#define RLED   P1_0	        //定义LED1为P10口控制
#define GLED   P1_1	        //定义LED2为P11口控制
#define YLED   P0_4	        //定义LED3为P04口控制
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

#define ADC_REF_1_25_V      0x00
#define ADC_14_BIT          0x30
#define ADC_TEMP_SENS       0x0E

#define DISABLE_ALL_INTERRUPTS() (IEN0 = IEN1 = IEN2 = 0x00)

#define ADC_SINGLE_CONVERSION(settings) \
   do{ ADCCON3 = (settings); }while(0)

#define ADC_SAMPLE_SINGLE() \
  do { ADC_STOP(); ADCCON1 |= 0x40;  } while (0)

#define ADC_SAMPLE_READY()  (ADCCON1 & 0x80)

#define ADC_STOP() \
  do { ADCCON1 |= 0x30; } while (0)

#define ADC14_TO_CELSIUS(ADC_VALUE)    ( ((ADC_VALUE) >> 4) - 335)

/**************************
系统时钟 不分频
计数时钟 32分频
**************************/
void InitClock(void)
{
    CLKCONCMD = 0x28;           //时器计数时钟设定为1M Hz,  系统时钟设定为32 MHz 
    while(CLKCONSTA & 0x40);    //等晶振稳定
}
/****************************
//初始化LED控制IO口程序
*****************************/
void InitLEDIO(void)
{
    P1DIR |= 0x03;  //P10、P11定义为输出
    P0DIR |= 0x10;  //P14定义为输出
    RLED = 0;
    GLED = 0;
    YLED = 0;	   //LED灯初始化为关    
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
	PERCFG = 0x00;				 //位置1 P0口
	P0SEL = 0x0c;				 //P0用作串口
	
	P2DIR &= ~0XC0;                           //P0优先作为UART0    
        U0CSR |= 0x80;   	                  //串口设置为UART方式
        U0GCR |= 8;				
        U0BAUD |= 59;		                  //波特率设为9600

	UTX0IF = 1;                               //UART0 TX中断标志初始置位1  
        U0CSR |= 0X40;				  //允许接收
        IEN0 |= 0x84;				  //开总中断，接收中断

}

/****************************************************************
   串口发送字符串函数						
****************************************************************/
void UartTX_Send_String(char *Data,int len)
{
  int j;

  for(j=0;j<len;j++)
  {
    U0DBUF = *Data;
    Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
//     U0DBUF = 0x0A;        // 换行
//    while(UTX0IF == 0);
//      UTX0IF = 0;
}


/****************************************************************
  延时函数				
****************************************************************/
void Delay(uint n)
{
	uint i,j;
        for(j=0; j<10; j++)
        {
          for(i=0;i<n;i++);
          for(i=0;i<n;i++);
          for(i=0;i<n;i++);
          for(i=0;i<n;i++);
          for(i=0;i<n;i++);
          for(i=0;i<n;i++);
          for(i=0;i<n;i++);
          for(i=0;i<n; i++);
        }
}





