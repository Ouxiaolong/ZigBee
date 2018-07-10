/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2018-01
  * @brief       人进入其感应范围模块输出高电平,点亮LED1，人离开感应范围LED1熄灭，
                 P0.6口为HC-SR501传感器的输入端
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**宏定义***********************************************************************/
//定义数据类型
typedef unsigned char uchar;
typedef unsigned int  uint;

//定义端口
#define LED1     P1_0        //定义P1.0口为LED1控制端
#define DATA_PIN P0_6        //定义P0.6口为传感器的输入端

/**函数声明*********************************************************************/
void DelayMS(uint msec);
void InitLed(void);

/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void)
{       
  InitLed();               //设置LED灯和P0.6相应的IO口
    
  while(1)                 //无限循环  
  {    
    if(DATA_PIN == 1)   
    {      
      DelayMS(10);     
      if(DATA_PIN == 1)      
      {              
        LED1 = 0;      //有人时LED1亮      
      }    
    }    	    
    else      
      LED1=1;          //无人时LED1熄灭  
  }    
}

/**
  * @brief     以毫秒为单位延时 16M时约为535,系统时钟不修改默认为16M
  * @param     msec 延时参数，值越大，延时越久
  * @retval    None
  */
void DelayMS(uint msec)
{   
  uint i,j;
    
  for (i=0; i<msec; i++)
    for (j=0; j<535; j++);
}

/**
  * @brief     设置LED灯和P0.4相应的IO口
  * @param     None
  * @retval    None
  */
void InitLed(void)
{
  P1DIR |= 0x01;           //P1.0定义为输出口
  P0SEL = 0x00;
  P0DIR &= ~0x40;          //P0.6定义为输入口    
  P2INP |= 0x20;
}

