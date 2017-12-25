
#include "Uart.h"

#define uint unsigned int 
#define uchar unsigned char


/**************************************************
//CC2530串口初始化配置
***************************************************/
void InitUART(void)
{ 
    PERCFG = 0x00;          //位置1 P0口 
    P0SEL = 0x0c;           //P0_2,P0_3 用作串口,第二功能 
    P2DIR &= ~0XC0;         //P0 优先作为UART0 ，优先级
    U0CSR |= 0x80;          //UART 方式 
    U0GCR |= 11;            //U0GCR与U0BAUD配合     
    U0BAUD |= 216;          //波特率设为115200 
    UTX0IF = 0;             //UART0 TX 中断标志清0
    U0CSR |= 0X40;          //允许接收 
    URX0IE=1;               //接收中断
    EA=1;                   //开总中断，                   
}


/**************************************************
 函 数 名  : Send_char
 功能描述  : 串口向电脑发送字节
 输入参数  : c---所要发送的数据 
***************************************************/
void Send_char(uchar c)
{
    U0DBUF = c; 
    while(UTX0IF == 0);   //发送完成标志位
    UTX0IF = 0;   
}


/**************************************************
 函 数 名  : UartSend_String
 功能描述  : 串口向电脑发送字符串
 输入参数  : *Data---字符串首地址
             len---字符串长度 

***************************************************/
void UartSend_String(char *Data,int len)
{
    int j;
    for(j=0;j<len;j++)
    {
        //U0DBUF = *Data++;
        //while(UTX0IF == 0);
        //UTX0IF = 0;
      Send_char(*Data++);
    }
}


/**************************************************
 函 数 名  : SetSysClock
 功能描述  : 设置系统时钟为32MHz
***************************************************/
void SetSysClock(void)
{
    CLKCONCMD &= ~0x40;           //选择系统时钟源为外部32MHz crystal oscillator
    while(CLKCONSTA & 0x40);      //等待晶振稳定为32MHz
    CLKCONCMD &= ~0x47;           //设置系统主时钟频率为32MHZ  
}

/*********************************************END OF FILE**********************/