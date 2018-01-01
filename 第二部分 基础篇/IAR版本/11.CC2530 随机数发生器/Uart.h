#ifndef __Uart_H
#define	__Uart_H

#include <ioCC2530.h>
#include <string.h>

#define uint unsigned int 
#define uchar unsigned char

void InitUART(void);
void Send_char(uchar c);
void UartSend_String(char *Data,int len);
void SetSysClock(void);
void Delayms(uint xms);

#endif 

/*********************************************END OF FILE**********************/
