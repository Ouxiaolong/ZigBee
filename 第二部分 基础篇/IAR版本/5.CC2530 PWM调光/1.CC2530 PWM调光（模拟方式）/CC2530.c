/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       通过PWM（脉宽调制）调节LED的亮度
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义

/**宏定义***********************************************************************/
//定义数据类型
#define uint  unsigned int
#define uchar unsigned char 

//定义控制灯的端口
#define LED0 P1_0	//定义LED1为P10口控制

/**函数声明*********************************************************************/
void Delay(unsigned int t);   //延时函数
void InitIO(void);		//初始化LED控制IO口函数

/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main (void)
{
  uint CYCLE=600,PWM_LOW=0;//定义周期并赋值
  InitIO();
  while (1)         //主循环
  {
    LED0=1;
    Delay(60000);        //特意加延时，可以看到熄灭的过程
    for(PWM_LOW=1;PWM_LOW<CYCLE;PWM_LOW++)
    {
      //PWM_LOW表示低
      //电平时间，这个循环中低电平时长从1累加到CYCLE（周期）的值，即600次
      LED0=0;        //点亮LED  
      Delay(PWM_LOW);//延时长度，600次循环中从1加至599
      LED0=1;        //熄灭LED
      Delay(CYCLE-PWM_LOW);//延时长度，600次循环中从599减至1
    }

    LED0=0;
    for(PWM_LOW=CYCLE-1;PWM_LOW>0;PWM_LOW--)
    {
      //与逐渐变亮相反的过程    
      LED0=0;
      Delay(PWM_LOW);
      LED0=1;
      Delay(CYCLE-PWM_LOW);    
    }
    //主循环中添加其他需要一直工作的程序
  }
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

/**
  * @brief     初始化IO
  * @param     None
  * @retval    None
  */
void InitIO(void)
{
  P1DIR |= 0x1;  //P10定义为输出
}



