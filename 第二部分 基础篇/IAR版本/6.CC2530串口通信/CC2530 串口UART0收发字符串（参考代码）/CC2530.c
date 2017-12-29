/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       串口收发数据
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <iocc2530.h> 
#include <string.h> 

/**宏定义***********************************************************************/
//定义数据类型
#define uint unsigned int 
#define uchar unsigned char 

//定义控制灯的端口 
#define LED1 P1_0 
#define LED2 P1_1 

/**函数声明*********************************************************************/
void initUART0(void); 
void IO_Init(void);
void UartTX_Send_String(uchar *Data,int len); 

/**全局变量*********************************************************************/
uchar Recdata[30]; 
uchar RXTXflag = 1; 
uchar temp; 
uint  datanumber = 0;  

/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void) 
{  
  IO_Init();
  initUART0(); 
  
  while(1) 
  { 
    if(RXTXflag == 1) //接收状态 
    { 
      if( temp != 0) 
      { 
        LED2 = 0; //接收状态指示 
        if((temp!='#')&&(datanumber<50)) //'＃'被定义为结束字符，最多能接收50个字符 
        {     
          Recdata[datanumber++] = temp; 
        } 
        else 
        { 
          RXTXflag = 3; //进入发送状态 
        } 
                 
        if(datanumber == 50) 
          RXTXflag = 3;  
        temp  = 0;  
      } 
    } 
    if(RXTXflag == 3) //发送状态 
    { 
      UartTX_Send_String("send:",5); 
      LED1 = 0; //发送状态指示  
      U0CSR &= ~0x40; //不能接收数据 
      UartTX_Send_String(Recdata,datanumber); 
      UartTX_Send_String("\r\n",2);//换行
      U0CSR |= 0x40; //允许接收 
      RXTXflag = 1; //恢复到接收状态 
      datanumber = 0; //指针归0 
      LED1 = 1; //关发送指示 
      LED2 = 1;  
    } 
 } 
} 

/**
  * @brief     串口发送字符串函数 
  * @param     Date  数据
               len   长度
  * @retval    None
  */
void UartTX_Send_String(uchar *Data,int len) 
{ 
  int j; 
  for(j=0;j<len;j++) 
  { 
    U0DBUF = *Data++; 
    while(UTX0IF == 0); 
    UTX0IF = 0; 
  } 
} 

/**
  * @brief     端口初始化函数
  * @param     None
  * @retval    None
  */
void IO_Init(void)
{
  P1DIR = 0x03; //P1控制LED 
  LED1 = 1; 
  LED2 = 1; //关LED 
}

/**
  * @brief     初始化串口0函数 
  * @param     None
  * @retval    None
  */
void initUART0(void) 
{ 
    //时钟配置
    CLKCONCMD &= ~0x40; //设置系统时钟源为32MHZ晶振 
    while(CLKCONSTA & 0x40); //等待晶振稳定 
    CLKCONCMD &= ~0x47; //设置系统主时钟频率为32MHZ 
    //串口配置
    PERCFG = 0x00; //位置1 P0口 
    P0SEL = 0x0c; //P0用作串口 
    P2DIR &= ~0XC0; //P0优先作为UART0         
    U0CSR |= 0x80; //串口设置为UART方式 
    U0GCR |= 11;     
    U0BAUD |= 216; //波特率设为115200
    UTX0IF = 1; //UART0 TX中断标志初始置位1  
    U0CSR |= 0X40; //允许接收 
    IEN0 |= 0x84; //开总中断，接收中断 
} 

/**
  * @brief     串口接收一个字符:
               一旦有数据从串口传至CC2530,则进入中断，
               将接收到的数据赋值给变量temp. 
  * @param     None
  * @retval    None
  */
#pragma vector = URX0_VECTOR 
 __interrupt void UART0_ISR(void) 
{ 
  URX0IF = 0; //清中断标志 
  temp = U0DBUF;                           
} 
