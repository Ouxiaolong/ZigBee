/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       按键控制LED（查询方式）
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**宏定义***********************************************************************/
//定义数据类型
#define uint unsigned int
#define uchar unsigned char

//定义控制LED灯的端口
#define LED1 P1_0	//LED1为P1.0口控制
#define KEY1 P0_1       //KEY1为P0.1口控制

/**函数声明*********************************************************************/
void Delayms(uint);		//延时函数
void InitLed(void);		//初始化LED1
void InitKey();                 //按键初始化
uchar KeyScan();                //按键扫描程序


/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void)
{
  InitLed();		//调用初始化函数
  InitKey();
  while(1)
  {
   if(KeyScan())       //按键改变LED状态
     LED1=~LED1;       
  }
}

/**
  * @brief     普通延时函数
  * @param     xms 延时长度
  * @retval    None
  */
void Delayms(uint xms)   //i=xms 即延时i毫秒
{
 uint i,j;
 for(i=xms;i>0;i--)
   for(j=587;j>0;j--);
}

/**
  * @brief     LED初始化
  * @param     None
  * @retval    None
  */
void InitLed(void)
{
    P1DIR |= 0x01;  //P1_0定义为输出
    LED1 = 1;       //LED1灯熄灭     
}

/**
  * @brief     按键初始化
  * @param     None
  * @retval    None
  */
void InitKey()
{
  P0SEL &= ~0X02;    //设置P01为普通IO口  
  P0DIR &= ~0X02;   //按键在P01 口，设置为输入模式 
  P0INP &= ~0x02;   //打开P01上拉电阻,不影响
}

/**
  * @brief     按键检测函数
  * @param     None
  * @retval    uchar
  */
uchar KeyScan(void)
{
  if(KEY1==0)
  {
    Delayms(10);
    if(KEY1==0)
    {
      while(!KEY1);  //松手检测
      return 1;      //有按键按下
    }
  }
  return 0;          //无按键按下
}
