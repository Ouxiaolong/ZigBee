#ifndef _UART_H_
#define _UART_H_

#define uint unsigned int   
#define uchar unsigned char 

extern void UARTInit(void);
extern void UARTSend(char *data,int length);

#endif