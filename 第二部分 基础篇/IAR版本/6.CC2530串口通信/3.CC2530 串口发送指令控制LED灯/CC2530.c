/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       串口发送字符控制LED
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>
#include <string.h>


/**宏定义***********************************************************************/
//定义数据类型
#define uint unsigned int
#define uchar unsigned char

//定义控制灯的端口
#define LED1   P1_0
#define LED2   P1_1
#define LED3   P0_4

/**函数声明*********************************************************************/
void initUART0(void);
void Init_LED_IO(void);        //LED初始化

/**全局变量*********************************************************************/
uchar Recdata[3]="000";
uchar RXTXflag = 1;
uchar temp;
uint  datanumber = 0;
uint  stringlen;

/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void)
{
  uchar i;
  Init_LED_IO();
  initUART0();
  while(1)
  {
    if(RXTXflag == 1)			 //接收状态
    {
      if( temp != 0)
      {
        if((temp!='#')&&(datanumber<3))
        {
          //’＃‘被定义为结束字符                   
          //最多能接收3个字符        
          Recdata[datanumber++] = temp;        
        }       
        else       
        {        
          RXTXflag = 3;                   //进入改变小灯的程序   
        }    
        if(datanumber == 3)RXTXflag = 3;    
        temp  = 0;    
      }
    }     
    if(RXTXflag == 3)   
    {  
      if(Recdata[0]=='R') 
      {
        if(Recdata[1]=='0')
          LED1 = 1;                       // R0# 关D1    
        else
          LED1 = 0;                       // R1# 开D1
      }
      if(Recdata[0]=='Y')
      {
        if(Recdata[1]=='0')
          LED3 = 1;                       // Y0# 关D3
        else
          LED3 = 0;                       // Y1# 开D3
      }
      if(Recdata[0]=='G') 
      {     
        if(Recdata[1]=='0')
          LED2 = 1;                       // G0# 关D2     
        else     
          LED2 = 0;                       // G1# 开D2   
      }   
      if(Recdata[0]=='A')      
      {     
        if(Recdata[1]=='0')
        {  
          LED1 = 1;  
          LED3 = 1;        
          LED2 = 1;                        // A0# 关所有LED
        }  
        else
        {  
          LED1 = 0;  
          LED3 = 0;         
          LED2 = 0;                       // A1# 开所有LED 
        }
      }
      RXTXflag = 1;
      for(i=0;i<3;i++)
        Recdata[i]=' ';                   //清除刚才的命令
      datanumber = 0;                     //指针归0
    }      
  }//while
}
 
/**
  * @brief     串口（UART0)初始化函数
  * @param     None
  * @retval    None
  */
void initUART0(void)
{
  CLKCONCMD &= ~0x40;                           //设置系统时钟源为32MHZ晶振
  while(CLKCONSTA & 0x40);                      //等待晶振稳定
  CLKCONCMD &= ~0x47;                           //设置系统主时钟频率为32MHZ

  PERCFG = 0x00;			        //位置1 P0口
  P0SEL = 0x0c;				        //P0用作串口
  P2DIR &= ~0XC0;                               //P0优先作为UART0    
    

  U0CSR |= 0x80;			        //串口设置为UART方式
  U0GCR |= 11;				
  U0BAUD |= 216;			        //波特率设为115200
  UTX0IF = 1;                                   //UART0 TX中断标志初始置位1    
    
  U0CSR |= 0X40;			        //允许接收
  IEN0 |= 0x84;				        //开总中断，接收中断
}

/**
  * @brief     初始化LED IO口
  * @param     None
  * @retval    None
  */
void Init_LED_IO(void)
{
  	
  P1DIR = 0x03; 	         //P10 P11 为输出 
  P0DIR = 0x10;                  //P04为输出
  LED1 = 1;
  LED3 = 1;		 
  LED2 = 1;		        //灭LED
}

/**
  * @brief     串口接收一个字符:一旦有数据从串口传至CC2530,则进入中断，将接收到的数据赋值给变量temp.	
  * @param     None
  * @retval    None
  */
#pragma vector = URX0_VECTOR
 __interrupt void UART0_ISR(void)
 {
   URX0IF = 0;				//清中断标志
   temp = U0DBUF;
 }

