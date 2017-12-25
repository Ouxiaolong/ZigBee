/*******************************************************************************
*文件名   ： Uart.h
*实现功能 ： USART底层驱动
*实验平台 ： 烽火 Zigbee 开发板
*硬件连接 ： Usart0_Rx  P0_2 
             Usart0_Tx  P0_3
*作者     ： 烽火团队
*创建时间 ： 2013/8/4 
*联系方式 ：  QQ   449199327 @Cavani
             淘宝  烽火物联科技
                   http://shop110226727.taobao.com
*******************************************************************************/

#ifndef __Uart_H
#define	__Uart_H

#include <ioCC2530.h>
#include <string.h>

#define uint unsigned int 
#define uchar unsigned char

void InitUART(void);
void Send_char(uchar c);
void UartSend_String(char *Data,int len);
//void SetSysClock(void);
void Delayms(uint xms);

#endif 

/*********************************************END OF FILE**********************/
