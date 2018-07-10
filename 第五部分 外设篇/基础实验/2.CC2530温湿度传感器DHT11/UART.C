#include <ioCC2530.h>
#include "UART.H" 

// 串口初始化函数     
void InitUart()
{
    CLKCONCMD &= ~0x40;      // 设置系统时钟源为 32MHZ晶振
    while(CLKCONSTA & 0x40); // 等待晶振稳定 
    CLKCONCMD &= ~0x47;      // 设置系统主时钟频率为 32MHZ
    
    PERCFG = 0x00;           //位置1 P0口 
    P0SEL = 0x0c;            //P0_2,P0_3用作串口,第二功能 
    P2DIR &= ~0xC0;          //P0 优先作为UART0 ，优先级
    
    U0CSR |= 0x80;           //UART 方式 
    U0GCR |= 11;             //U0GCR与U0BAUD配合     
    U0BAUD |= 216;           // 波特率设为115200
    UTX0IF = 0;              //UART0 TX 中断标志初始置位0 
    
}

//串口发送函数    
void UartSendString(unsigned char *Data, int len) 
{
    int j; 
    for(j=0;j<len;j++) 
    { 
        U0DBUF = *Data++; 
        while(UTX0IF == 0); 
        UTX0IF = 0; 
    } 
    
}