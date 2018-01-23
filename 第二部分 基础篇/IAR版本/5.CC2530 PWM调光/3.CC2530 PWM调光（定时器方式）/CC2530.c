/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       PWM调节LED的亮度(定时器方式)
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
void InitLed(void);            //LED初始化
void InitT1();                 //定时器初始化
void Delay(unsigned int t);   //延时函数

/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void)
{
    uint i;
    uint rate[11]={0xF7,0xE1,0xC8,0xAF,0x96,0x7D,0x64,0x4B,0x32,0x19,0x0A};
    
    InitLed();		     //调用初始化函数
    InitT1();                //定时器初始化及pwm配置
    
    while(1)
    {
      for(i=0;i<11;i++)
      {
        T1CC2H = 0x00;
        T1CC2L = rate[i];
        Delay(50000);
        Delay(50000);
        Delay(50000);
      }
    }

}

/**
  * @brief     设置LED灯相应的IO口
  * @param     None
  * @retval    None
  */
void InitLed(void)
{
    P1DIR |= 0x01;           //P1.0定义为输出
    LED1 = 0;                //使LED1灯上电默认为熄灭     
}

/**
  * @brief     定时器初始化，TICKSPD 是16 MHz系统不配置时默认是2分频，即16MHz
  * @param     None
  * @retval    None
  */
void InitT1()
{
    CLKCONCMD &= ~0x40;      //设置系统时钟源为32MHZ晶振
    while(CLKCONSTA & 0x40); //等待晶振稳定为32M
    CLKCONCMD &= ~0x07;      //设置系统主时钟频率为32MHZ   
    CLKCONCMD |= 0x38;       //时钟速度32 MHz 定时器标记输出设置[5:3]250kHz

    //定时器通道设置
    PERCFG |= 0x40;          //定时器1 的IO位置   1:备用位置2 
    P2SEL &= ~0x10;          //定时器1优先
    P2DIR |= 0xC0;           //第1优先级：定时器1通道2-3

    P1DIR |= 0xff;           //端口1为输出    
    P1SEL |= 0x01;           //timer1 通道2映射口P1_0

    //定时器通道2比较值
    T1CC2H = 0x00;           //20%占空比为200us
    //修改T1CC2L可调整led的亮度
    //T1CC2L = 0xF7; //1%的正占空比
    //T1CC2L = 0xE1; //10%的正占空比
    //T1CC2L = 0xC8; //20%的正占空比
    //T1CC2L = 0xAF; //30%的正占空比
    //T1CC2L = 0x96; //40%的正占空比
    T1CC2L = 0x7D; //50%的正占空比
    //T1CC2L = 0x64; //60%的正占空比
    //T1CC2L = 0x4B; //70%的正占空比
    //T1CC2L = 0x32; //80%的正占空比
    //T1CC2L = 0x19; //90%的正占空比
    //T1CC2L = 0x0A; //99%的正占空比
    //T1CC2L = 0x01; //设置通道2比较寄存器初值

    //装定时器通道0初值
    T1CC0H = 0x00;           //1ms的周期时钟,频率为976.516HZ
    T1CC0L = 0xff; 
    
    T1CCTL2 = 0x1c;          // 模式选择 通道2比较模式
    
    //模式设置
    T1CTL = 0x02;            //250KHz 不分频
}

/**
  * @brief     延时函数
  * @param     xms 延时大小
  * @retval    None
  */
void Delay(unsigned int xms)
{
 while(xms--);
}