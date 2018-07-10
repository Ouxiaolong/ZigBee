/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2018-01
  * @brief       设置串口调试助手波特率：115200bps 8N1  DS18B20采集的温度通过串口传给电脑显示
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <iocc2530.h>
#include <stdio.h>
#include <string.h>
#include "ds18b20.h"  
#include "LCD.h"

/**宏定义***********************************************************************/
//定义数据类型
typedef unsigned char uchar;
typedef unsigned int  uint;
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr)[0])
#define FLOAT_TEMP      1          //输出更高精度时打开此注释

/**函数声明*********************************************************************/
void InitCLK();
void InitUart();
void UartSendString(char *Data, int len);

/**全局变量*********************************************************************/
extern void Delay_ms(unsigned int k);//外部函数ms的声明


/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main()
{  
  char str[9]="DS18B20:"; 
  char strTemp[30];
  float fTemp;
  
  InitCLK();                      //设置系统时钟源
  InitUart();                     //串口初始化
  P0SEL &= 0x7f;                  //DS18B20的io口初始化
    
  LCD_Init();                 //oled 初始化  
  LCD_CLS();                  //屏全亮 
  LCD_welcome();
    
  while(1)
  {        
    memset(strTemp, 0, ARRAY_SIZE(strTemp)); 

    //厂家提供的程序温度值不带小数，Ds18B20本身是支持1位小数位的，修改后使其支持，精度更高        
#if defined(FLOAT_TEMP)                 
    fTemp = floatReadDs18B20();       //温度读取函数 带1位小数位
    sprintf(strTemp, "%s%.01f", str, fTemp); //将浮点数转成字符串  
        
    UartSendString(strTemp, strlen(strTemp));       //通过串口发送温度值到电脑显示
#else       
    ucTemp = ReadDs18B20();           //温度读取函数
    //strTemp[0] = ucTemp/10+48;        //取出十位数
    //strTemp[1] = ucTemp%10+48;        //取出个位数

    sprintf(strTemp, "%s%d%d", str, ucTemp/10, ucTemp%10);   
    UartSendString(strTemp, strlen(strTemp));       //通过串口发送温度值到电脑显示
#endif 
        
    LCD_P8x16Str(0, 5, (unsigned char*)strTemp);
    UartSendString("\r\n", 2);          // 回车换行     
    Delay_ms(1000);                   //延时函数使用定时器方式  
  }
}

/**
  * @brief     设置系统时钟源
  * @param     None
  * @retval    None
  */
void InitCLK()
{
  CLKCONCMD &= ~0x40;             //设置系统时钟源为32MHZ晶振 
  while(CLKCONSTA & 0x40);        //等待晶振稳定为32M
  CLKCONCMD &= ~0x47;             //设置系统主时钟频率为32MHZ   
}

/**
  * @brief     串口初始化函数
  * @param     None
  * @retval    None
  */
void InitUart()
{
  PERCFG = 0x00;                  //位置1 P0口
  P0SEL = 0x0c;                   //P0用作串口
  P2DIR &= ~0xc0;                 //P0优先作为UART0 
  U0CSR |= 0x80;                  //串口设置为UART方式
  U0GCR |= 11;
  U0BAUD |= 216;                  //波特率设为115200
  U0CSR |= 0x40;                  //UART接收器使能
  UTX0IF = 0;                     //UART0 TX中断标志初始置位0
}

/**
  * @brief     串口发送函数
  * @param     Data:发送缓冲区   
               len:发送长度
  * @retval    None
  */
void UartSendString(char *Data, int len)
{
  uint i;
    
  for(i=0; i<len; i++)
  {    
    U0DBUF = *Data++;
   
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
}

