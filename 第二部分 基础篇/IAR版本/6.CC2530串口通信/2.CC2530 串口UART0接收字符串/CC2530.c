/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       串口接收数据
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>
#include "Uart.h"

/**宏定义***********************************************************************/
//定义数据类型
#define uint unsigned int 
#define uchar unsigned char

#define LED1  P1_0    //P1_0连接LED1
#define LED2  P1_1    //P1_1连接LED2
#define LED3  P0_4    //P1_4连接LED3

/**函数声明*********************************************************************/
void Send_ReceicedData(void);
void Initial_IO(void);
void Delayms(uint xms);

/**全局变量*********************************************************************/
//定义待发送的数据
char Txdata0[]={"龙创科技欢迎您\n"}; //存放"龙创科技欢迎您"
char Txdata1[]={"This is a Uart test.\n"};
char Txdata2[]={"The data CC2530 has received is: \n"};
char Txdata3[]={"\r\n"};
char Rxdata = '\0'; 


/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void)
{
    SetSysClock();               //设置系统时钟为32MHz
     
    InitUART();                  //调用初始化函数 
    
    Initial_IO();		 //调用初始化函数
    
    
    UartSend_String(Txdata0,sizeof("龙创科技欢迎您\n"));
    Delayms(500);
    UartSend_String(Txdata1,sizeof("This is a Uart test.\n"));
    
    while(1)
    { 
        Send_ReceicedData();      
    }
  
}

/**
  * @brief     USART接收中断
  * @param     None
  * @retval    None
  */
#pragma vector = URX0_VECTOR 
  __interrupt void UART0_ISR(void) 
 { 
    Rxdata = U0DBUF;   //接收数据并存于Rxdata

    URX0IF = 0;    // 清中断标志 
 }

/**
  * @brief     将接收到的数据发回给电脑
  * @param     None
  * @retval    None
  */
void Send_ReceicedData(void)
{  
    if ( Rxdata != '\0' ) 
    {
      UartSend_String(Txdata2,sizeof("The data CC2530 has received is: ")); //提示接收到数据
      Send_char(Rxdata);
      UartSend_String(Txdata3,sizeof("\n"));
      
      if (Rxdata=='1')
      {
        LED1=0;
        Delayms(500);
        LED1=1;        
      }
      
      if (Rxdata=='2')
      {
        LED2=0;
        Delayms(500);
        LED2=1;        
      }

      if (Rxdata=='3')
      {
        LED3=0;
        Delayms(500);
        LED3=1;        
      }  
  
      Rxdata='\0';    
      
    }

}
/**
  * @brief     IO初始化函数
  * @param     None
  * @retval    None
  */
void Initial_IO(void)
{
    P1DIR |= 0xff;     //P1为输出
    P0DIR |= 0xff;
}

/**
  * @brief     普通延时函数
  * @param     xms 延时长度
  * @retval    None
  */
void Delayms(uint xms)   
{
    uint i,j;
    for(i=xms;i>0;i--)
        for(j=587;j>0;j--);
}
