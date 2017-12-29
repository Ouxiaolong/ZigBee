/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       定时器T3通过中断方式控制LED1周期性闪烁
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**宏定义***********************************************************************/
//定义数据类型
typedef unsigned char uchar;
typedef unsigned int  uint;

//定义控制灯的端口
#define LED1 P1_0       // P1.0口控制LED1

/**函数声明*********************************************************************/
void InitLed(void);    //初始化 LED 控制 IO 口函数
void InitT3();         //定时器初始化


/**全局变量*********************************************************************/
uint count;             //用于定时器计数

/**
  * @brief     中断处理函数
  * @param     None
  * @retval    None
  */
//定时器T3中断处理函数
#pragma vector = T3_VECTOR 
__interrupt void T3_ISR(void) 
{ 
    IRCON = 0x00;            //清中断标志, 也可由硬件自动完成 
    if(count++ > 245)        //245次中断后LED取反，闪烁一轮（约为0.5 秒时间） 
    {                        //经过示波器测量确保精确
        count = 0;           //计数清零 
        LED1 = ~LED1;        //改变LED1的状态
    } 
}

/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void)
{
  InitLed();		  //设置LED灯相应的IO口
  InitT3();            //设置T3相应的寄存器
  
  while(1)
  {};
}

/**
  * @brief     设置LED灯相应的IO口
  * @param     None
  * @retval    None
  */
void InitLed(void)
{
    P1DIR |= 0x01;           //P1.0定义为输出
    LED1 = 1;                //使LED1灯上电默认为熄灭     
}

/**
  * @brief     定时器初始化，系统不配置工作时钟时默认是2分频，即16MHz
  * @param     None
  * @retval    None
  */
void InitT3()
{     
    T3CTL |= 0x08 ;          //开溢出中断     
    T3IE = 1;                //开总中断和T3中断
    T3CTL |= 0xE0;           //128分频,128/16000000*N=0.5S,N=62500
    T3CTL &= ~0x03;          //自动重装 00－>0xff  62500/255=245(次)
    T3CTL |= 0x10;           //启动
    EA = 1;                  //开总中断
}
  

