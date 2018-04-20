/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       LED1闪烁5次后进入睡眠状态，通过按下按键K1
产生外部中断进行唤醒
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**宏定义***********************************************************************/
//定义数据类型
typedef unsigned char uchar;
typedef unsigned int  uint;

//定义IO口
#define LED1 P1_0            //P1.0口控制LED1
#define KEY1 P0_1            //P0.1口控制KEY1

#define  PM0  0
#define  PM1  1
#define  PM2  2
#define  PM3  3

/**函数声明*********************************************************************/
void InitKey(void);
void SysWorkMode(uchar mode);
void Delayms(uint xms);
void InitLed(void);

/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void)
{
    uchar count=0;  

    InitKey();  //按键中断初始化，用于中断唤醒
    InitLed();
    while(1)
    {
        LED1=~LED1;  //仅作指示作用
        if(++count>=10)
        {
            count=0;
            SysWorkMode(PM3); //5次闪烁后进入睡眠状态PM3,等待按键S1中断唤醒
        }
        Delayms(500);
    }
}

/**
  * @brief     中断处理函数-系统唤醒
  * @param     None
  * @retval    None
  */
#pragma vector = P0INT_VECTOR         //格式：#pragma vector = 中断向量
    __interrupt void P0_ISR(void)     //接着是中断处理程序(函数名可以任意取)
{
    P0IFG = 0;       //清中断标志
    P0IF = 0;
    PCON = 0x00;  //清0，让系统进入正常工作模式
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
void InitKey(void)
{
    P0IEN |= 0x02;  //设置P0_1为中断方式
    PICTL |= 0x01;  //下降沿触发 
    IEN1 |= 0x20;   //允许P0口中断
    P0IFG = 0x00;   //清中断标志位
    EA = 1;         //开总中断
}

/**
  * @brief     系统工作模式选择函数
  * @param     None
  * @retval    None
  * @attention
  *            para1  0 	1	2	3									
  *            mode 	PM0	PM1	PM2	PM3													
  */
void SysWorkMode(uchar mode) 
{ 
    switch(mode)
    {  
    case PM0:
        SLEEPCMD |= PM0;     // 设置系统工作模式 
        break;      
    case PM1:
        SLEEPCMD |= PM1;     // 设置系统工作模式 
        break;
    case PM2:
        SLEEPCMD |= PM2;     // 设置系统工作模式 
        break;
    case PM3:
        SLEEPCMD |= PM3;     // 设置系统工作模式 
        break;        
    }
    //置1将强制系统进入SLEEPCMD所指定的电源模式，所有中断信号都可以清除此置位
    PCON = 0x01; 
}

/**
  * @brief     延时函数,大约1毫秒
  * @param     msec 延时大小
  * @retval    None
  */
void Delayms(uint xms)  
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=587;j>0;j--);
}
