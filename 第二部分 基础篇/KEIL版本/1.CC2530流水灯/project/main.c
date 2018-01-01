/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       流水灯
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <cc2510.h>
/**宏定义***********************************************************************/
//定义数据类型
#define uint unsigned int
#define uchar unsigned char

//定义控制灯的端口
#define LED1 P1_0 //定义 LED1 为 P10 口控制
#define LED2 P1_1 //定义 LED2 为 P11 口控制
#define LED3 P0_4 //定义 LED3 为 P04 口控制

/**函数声明*********************************************************************/
void Delay(uint); //延时函数;
void InitIO(void); //初始化 LED 控制 IO 口函数

/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void)
{
	InitIO(); //初始化 LED 灯控制 IO 口
	while(1) //循环
	{
		LED1=!LED1; // LED1 灯闪一次
		Delay(30);
		
		LED2=!LED2; // LED2 灯闪一次
		Delay(30);
		
		LED3=!LED3; // LED3 灯闪一次
		Delay(30);
	}
}

/**
  * @brief     延时函数
  * @param     n     延时大小
  * @retval    None
  */
void Delay(uint n)
{
    uint i;
     for(i = 0;i<n;i++)
     {
       int j;
      for(j = 0;j<10000;j++);
     }
}

/**
  * @brief     初始化IO函数
  * @param     None
  * @retval    None
  */
void InitIO(void)
{
  P1DIR |=0x03; //P10、 P11 定义为输出
  P0DIR |= 0x10;//P04定义为输出
	LED1=1;
  LED2=1;
  LED3=1; //LED 灯初始化
}
