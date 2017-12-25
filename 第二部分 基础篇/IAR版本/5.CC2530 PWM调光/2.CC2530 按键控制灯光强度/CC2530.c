/***************************************************
开发者： 龙创科技

开发平台：CC2530

日期：2016.1

内容：通过按键调节LED的亮度
***************************************************/
#include <ioCC2530.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义

#define uint  unsigned int
#define uchar unsigned char 

//定义控制灯的端口
#define LED1 P1_0	//定义LED1为P10口控制
#define KEY1 P0_1      //KEY1为P0.1口控制

//函数声明
void Delay(unsigned int t); //函数声明
void InitIO(void);		//初始化LED控制IO口函数
void InitKey();

/**************************************************
//主函数
***************************************************/
void main (void)
{                  
  unsigned int CYCLE=600,PWM_LOW=0;//定义周期并赋值
  InitIO();
  InitKey();
  while (1)         //主循环
  {
    
    if(KEY1==0)
    {
      //S1按下,一直按着哦。
      PWM_LOW++;
      if(PWM_LOW>CYCLE)
      {
        PWM_LOW=CYCLE-1;
      }
    }
    else
    {
      PWM_LOW--;
      if(PWM_LOW<1)
      {
        PWM_LOW=1;
      }
    }
    
    if(PWM_LOW==1)
    {
      LED1=0;
    }
    else if(PWM_LOW==CYCLE)
    {
      LED1=1;
    }
    else if(CYCLE>PWM_LOW)
    {
      LED1=1;
      Delay(PWM_LOW);
      LED1=0;
      Delay(CYCLE-PWM_LOW);
    }
  }
  
}
/***************************************************
 //延时函数
***************************************************/
void Delay(unsigned int t)
{
 while(t)
 {
   t--;
   t++;
   t--;
 }
}

/**************************************************
//初始化IO口程序
**************************************************/
void InitIO(void)
{
    P1DIR |= 0x01;  //P10
}

/*************************************************
 //按键初始化函数
*************************************************/
void InitKey()
{
  P0SEL &= ~0x01; //设置P0.1为普通IO口
  P0DIR &= ~0X01; //按键接在P0.1口上，设P0.1为输入模式
  P0INP &= ~0x01; //打开P0.1上拉电阻
}
  

