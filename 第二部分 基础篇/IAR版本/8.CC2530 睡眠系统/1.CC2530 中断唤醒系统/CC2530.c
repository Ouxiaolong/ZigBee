/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       LED1闪烁3次后进入睡眠状态，通过按下按键K2产生外部中断进行唤醒
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**宏定义***********************************************************************/
//定义数据类型
typedef unsigned char uchar;
typedef unsigned int  uint;

//定义IO口
#define LED1 P1_0            //P1.0口控制LED
#define KEY2 P2_0            //P2.0口控制KEY2

/**函数声明*********************************************************************/
void DelayMS(uint msec);
void InitLed(void);
void InitKey();
void SysPowerMode(uchar mode) ;

/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void)
{   
    uchar i=0;  
      
    InitLed();		     //设置LED灯相应的IO口     
    InitKey();               //设置KEY相应的IO口
    
    while(1)
    {
        for (i=0; i<6; i++)  //LED闪烁3次提醒用户将进入睡眠模式
        {
            LED1 = ~LED1;
            DelayMS(500);
        }

        SysPowerMode(3);     //进入睡眠模式PM3,按下按键K1中断唤醒系统 
    }
}

/**
  * @brief     延时函数,大约1毫秒
  * @param     msec 延时大小
  * @retval    None
  */
void DelayMS(uint msec)
{ 
    uint i,j;
    
    for (i=0; i<msec; i++)
        for (j=0; j<535; j++);
}

/**
  * @brief     LED控制IO口初始化函数
  * @param     None
  * @retval    None
  */
void InitLed(void)
{
    P1DIR |= 0x01;           //P1.0定义为输出口
    LED1 = 1;                //LED灯上电默认为熄灭 
}

/**
  * @brief     按键控制IO口初始化函数
  * @param     None
  * @retval    None
  */
void InitKey()
{
    P2IEN |= 0x1;    // P2.0 设置为中断方式 1：中断使能
    PICTL |= 0x8;    //下降沿触发   
    IEN2 |= 0x2;     //允许P2口中断; 
    P2IFG = 0x00;    //初始化中断标志位
    EA = 1;          //打开总中断
}

/**
  * @brief     系统工作模式选择函数
  * @param     None
  * @retval    None
  * @attention
  *            para1  0 	1	2	3									
  *            mode 	PM0	PM1	PM2	PM3													
  */
void SysPowerMode(uchar mode) 
{ 
    if(mode > 0 && mode < 4) 
    {  
        SLEEPCMD |= mode;    //设置系统睡眠模式 
        PCON = 0x01;         //进入睡眠模式 ,通过中断唤醒
    } 
    else 
        PCON = 0x00;         //主动/空闲模   通过中断唤醒系统 
}

/**
  * @brief     中断处理函数-系统唤醒
  * @param     None
  * @retval    None
  */
#pragma vector = P2INT_VECTOR    
__interrupt void P2_ISR(void) 
{ 
    if(P2IFG > 0) 
    { 
        P2IFG = 0;           //清标志位
    } 
    
    P2IF = 0; 
    SysPowerMode(4);         //正常工作模式
} 

