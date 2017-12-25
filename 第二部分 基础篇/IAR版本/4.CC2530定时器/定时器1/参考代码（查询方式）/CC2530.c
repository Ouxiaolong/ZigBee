/***************************************************
开发者： 龙创科技

开发平台：CC2530

日期：2016.1

内容：定时器T1的应用
***************************************************/
#include <ioCC2530.h>

#define uint   unsigned  int
#define uchar  unsigned  char

#define LED1   P1_0	        //定义LED1为P10口控制
#define LED2   P1_1	        //定义LED2为P11口控制
#define LED3   P0_4	        //定义LED3为P04口控制

uint counter=0;				//统计溢出次数
uint LEDFlag;				//标志是否要闪烁

void InitialT1test(void);               //初始化函数声明

/*****************************************************
//T1初始化程序
*****************************************************/
void InitialT1test(void)
{
	//初始化LED控制端口P1
	P1DIR = 0x03; 	         //P10 P11 为输出
        P0DIR = 0x10;            //P04为输出
        //灯默认为灭
	LED1 = 1;
	LED2 = 1;		
        LED3 = 1;
	//初始化计数器1
	T1CTL = 0x05;	
        T1STAT= 0x21;          //通道0,中断有效,8分频;自动重装模式(0x0000->0xffff)        
}

/******************************************************
//主函数
******************************************************/
void main()
{
  InitialT1test(); 	 //调用初始化函数
  while(1)   	         //查询溢出
  {
    if( T1IF> 0)
    {
      T1IF = 0;                //清溢出标志     
      counter++;     
      if(counter==15)            //中断计数，约0.25s
      {
        counter =0;
        LEDFlag = !LEDFlag;
      }
    }    
    if(LEDFlag)
    {
      LED2 =  LED1;
      LED3 = !LED2;
      LED1 = !LED1;	   // 每 1s LED灯闪烁一下 
      LEDFlag = !LEDFlag;   // 闪烁标志变量置0
    }                
  }
}
