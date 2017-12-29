/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       定时器T3（查询方式）
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**宏定义***********************************************************************/
//定义数据类型
#define uint unsigned int
#define uchar unsigned char

//定义控制LED1灯的端口
#define LED1 P1_0      //LED1为P1_0端口控制

/**函数声明*********************************************************************/

void InitLed(void);    //初始化LED端口
void InitT3(void);     //初始化定时器T3

/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void)
{
    uchar count=0;
    
    InitLed();		//LED_IO初始化
    InitT3();           //Timer3初始化
    
    while(1)
    {
        if(T3IF>0)    //查询溢出标志
        { 
            T3IF=0;
            if((++count)==254)      //溢出一次约为0.5s
            {
                count=0;
                LED1 = ~LED1;        //LED1取反   

            }
        } 
    }
}

/**
  * @brief     LED_IO初始化函数
  * @param     None
  * @retval    None
  */
void InitLed(void)
{
    P1DIR |= 0x01;  //P1端口定义为输出
    LED1 = 1;       //LED灯初始化熄灭

}

/**
  * @brief     Timer3初始化函数
  * @param     None
  * @retval    None
  */
void InitT3(void)        
{
    T3CTL = 0xF8;   //128分频；自由运行，从0x00到0xFF反复计数 
}

