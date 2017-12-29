/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       定时器T1（中断方式）
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**宏定义***********************************************************************/
//定义数据类型
#define uint unsigned int
#define uchar unsigned char

//定义控制LED灯的端口
#define LED1 P1_0	//定义LED1为P1_0口控制

/**函数声明*********************************************************************/
void Delayms(uint xms);		//延时函数
void InitLed(void);		//LED_IO初始化函数
void InitT1(void);              //Timer1中断方式初始化函数

/**全局变量*********************************************************************/
//由于是中断函数用到，一定要定义为全局变量
uint count=0;//用于计算溢出中断的次数

/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void)
{	
    InitLed();		//调用初始化函数
    InitT1();
    while(1)
    {
    }
}

/**
  * @brief     中断服务函数
  * @param     None
  * @retval    None
  */
#pragma vector = T1_VECTOR  //Timer1中断向量
 __interrupt void T1_ISR(void) 
{ 
    IRCON = 0x00;           //清中断标志, 也可由硬件自动完成 
    if((++count)==1)        //1次中断后LED取反，闪烁一轮（0.5 秒时间） 
    {          
        count = 0;          //计数清零 
        LED1=~LED1;
    } 
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


/**
  * @brief     LED初始化函数
  * @param     None
  * @retval    None
  */
void InitLed(void)
{
    P1DIR |= 0x01;  //P1_0义为输出
    LED1 = 1;       //LED1灯熄灭
}


/**
  * @brief     Timer1中断方式初始化函数
  * @param     None
  * @retval    None
  */
void InitT1(void)
{     
    T1CTL|=0X0d;               //128分频，自由运行模式 
    T1IE = 1;                  //开Timer1中断
    EA = 1;                    //开总中断
}
