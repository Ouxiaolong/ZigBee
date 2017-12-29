/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       串口通信-发送字符串
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>
#include <string.h>

/**宏定义***********************************************************************/
//定义数据类型
#define  uint  unsigned int
#define  uchar unsigned char

//定义控制灯的端口
#define LED1  P1_0

/**函数声明*********************************************************************/
void Delay(uint);
void initUARTSEND(void);
void IO_Init(void);
void UartTX_Send_String(char *Data,int len);

/**全局变量*********************************************************************/
char Txdata[25];

/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void)
{
  //uchar i;  	
  initUARTSEND();
  IO_Init();
  
  //UartTX_Send_String(Txdata,25);	       
  //for(i=0;i<30;i++)
  // Txdata[i]=' ';
  strcpy(Txdata,"LONGCHUANGKEJI!\r\n");      //将UART0 TX test赋给Txdata;
  while(1)
  {
    UartTX_Send_String(Txdata,strlen(Txdata)); //串口发送数据
    Delay(1000);                                //延时
    LED1=!LED1;                                 //D1灯在闪，标志发送状态
    Delay(1000);
  }
}

/**
  * @brief     延时函数
  * @param     xms 延时大小
  * @retval    None
  */
void Delay(uint xms)
{
  uint i,j;
  for(i=xms;i>0;i--)
    for(j=587;j>0;j--); 
}

/**
  * @brief     初始化函数
  * @param     None
  * @retval    None
  */
void IO_Init()
{
  P1DIR = 0x01; //P1控制LED	
  LED1 = 1;     //关LED
}

/**
  * @brief     串口初始化函数
  * @param     None
  * @retval    None
  */
void initUARTSEND(void)
{
    //时钟配置
    CLKCONCMD &= ~0x40;        //设置系统时钟源为32MHZ晶振
    while(CLKCONSTA & 0x40);   //等待晶振稳定
    CLKCONCMD &= ~0x47;        //设置系统主时钟频率为32MHZ
    //端口配置
    PERCFG = 0x00;	       //位置1 P0口
    P0SEL = 0x0c;				//P0_2,P0_3用作串口
    P2DIR &= ~0XC0;                             //P0优先作为UART0
   //串口配置
    U0CSR |= 0x80;				//UART方式
    U0GCR |= 11;				 //U0GCR.BAUD_E
    U0BAUD |= 216;				//波特率设为115200 UxBAUD.BAUD_M
    UTX0IF = 0;                                 //UART0 TX中断标志初始置位0
}

/**
  * @brief     串口发送字符串函数
  * @param     Date 数据
               len 长度
  * @retval    None
  */
void UartTX_Send_String(char *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
}
