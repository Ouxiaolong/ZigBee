/***************************************************
开发者：龙创科技

开发平台：CC2530

日期：2016.1

内容：中断唤醒系统
***************************************************/
#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char


#define PM0 0
#define PM1 1
#define PM2 2
#define PM3 3

#define LED1 P1_0
#define LED2 P1_1   //LED灯控制IO口定义

void Delay(uint xms);
void Init_IO_AND_LED(void);
void SysPowerMode(uchar sel);

/***************************************************
 //延时函数,大约1毫秒	
***************************************************/
void Delay(uint xms)
{
   uint i,j;
    for(i=xms;i>0;i--)
     for(j=587;j>0;j--);   
}

/***************************************************
系统工作模式选择函数											
* para1  0 	1	2	3									
* mode 	PM0	PM1	PM2	PM3													
***************************************************/
void SysPowerMode(uchar mode)
{
  uchar i,j;
  i = mode;
  if(mode<4)
  {
    SLEEPCMD &= 0xFC;     
    SLEEPCMD |= i;       //设置系统睡眠模式
    for(j=0;j<4;j++);
    {
      PCON = 0x01;         //进入睡眠模式
    }
  }
  else
  {
    PCON = 0x00;             //系统唤醒
  }
}
void SysWorkMode(uchar mode)
{
  switch (mode) {
  case PM0:
    SLEEPCMD |= PM0; // 设置系统工作模式
    break;
  case PM1:
    SLEEPCMD |= PM1; // 设置系统工作模式
    break;
  case PM2:
    SLEEPCMD |= PM2; // 设置系统工作模式
    break;
  case PM3:
    SLEEPCMD |= PM3; // 设置系统工作模式
    break;
}
//置 1 将强制系统进入 SLEEPCMD 所指定的电源模式，所有中断信号都可以清除此置位
  PCON = 0x01;

}

/****************************************************
// LED控制IO口初始化函数	
*****************************************************/
void Init_IO_AND_LED(void)
{
    P1DIR |= 0X03;
    LED1 = 1;
    LED2 = 1;
 
    P0INP &= ~0X10;   //设置P0输入电路模式为上拉/下拉
    P0IEN |= 0X10;     //P01设置为中断方式
    PICTL |= 0X10;     //下降沿触发
    
    EA = 1;
    IEN1 |= 0X20;      // 开P0口总中断
    P0IFG |= 0x00;     //清中断标志
};
/**************************************************
//主函数	
***************************************************/
void main()
{
  uchar count = 0;
  Init_IO_AND_LED();
  LED1 = 0 ;       //开LED1，系统工作指示
  Delay(500);       //延时	
  while(1)
  {
    LED2 = !LED2;
    LED1 = 0;
    count++;
    if(count >= 6)
    {
      count = 0;     
      LED1 = 1;
      SysWorkMode(PM2);
      //SysPowerMode(3);
      //3次闪烁后进入睡眠状态PM3
    }
   
    Delay(500);
    
  };
}
/***************************************************
    中断处理函数-系统唤醒
***************************************************/
#pragma vector = P0INT_VECTOR
 __interrupt void P0_ISR(void)
 {
  if(P0IFG>0)
  {
     P0IFG = 0;
  }
  
  P0IF = 0;
  SysWorkMode(PM3);
  //SysPowerMode(4);
 }


