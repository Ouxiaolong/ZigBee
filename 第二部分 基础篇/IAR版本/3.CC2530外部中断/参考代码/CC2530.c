/***************************************************
开发者： 龙创科技

开发平台：CC2530

日期：2016.1

修改：2016.2

内容：外部中断控制流水灯
***************************************************/
#include <ioCC2530.h>
#define uint  unsigned int
#define uchar unsigned char

//定义控制灯的端口
#define LED1   P1_0	  //定义LED1为P10口控制
#define LED2   P1_1	  //定义LED2为P11口控制
#define LED3   P0_4	  //定义LED3为P04口控制
#define KEY1   P0_1       //定义按键S1为P01口控制

//函数声明
void Delay(uint);		//延时函数声明
void Initial(void);		//初始化函数声明
void InitKey(void);             //初始化按键函数声明

uchar KeyScan(void);            //按键扫描函数声明
uchar Keyvalue = 0 ;            //定义变量记录按键动作
uint  KeyTouchtimes = 0 ;       //定义变量记录按键次数

/***************************************************
//延时
***************************************************/
void Delayms(uint xms)//即i=xms延时i毫秒
{
    uint i,j;
    for(i=xms;i>0;i--)
     for(j=587;j>0;j--);   
}

/****************************************************
//初始化按键为中断输入方式
****************************************************/
void InitKeyINT(void)
{
  P0INP |= 0x02;   //上拉    
  P0IEN |= 0X02;   //P01设置为中断方式
  PICTL |= 0X01;   //下降沿触发
  EA = 1;
  IEN1 |= 0X20;   // P0设置为中断方式;
  P0IFG |= 0x00;   //初始化中断标志位（可以不设）
  
}

/****************************************************
//初始化程序,将P10、P11、P04定义为输出口，并将LED灯初始化为灭
****************************************************/
void InitIO(void)
{
    P1DIR |= 0x03; //P10、P11定义为输出
    P0DIR |= 0x10; //P04定义为输出
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;	//LED灯初始化为灭
}

/************************************************
//中断处理函数
************************************************/
#pragma vector = P0INT_VECTOR
 __interrupt void P0_ISR(void)
 {
  if(P0IFG>0)            //按键中断
  {
    P0IFG = 0;
    Delayms(6);       //延时去抖
    if(P0IFG==0)         //按键中断
    {
      Delayms(6);  
      KeyTouchtimes = KeyTouchtimes+1;  //每次中断发生时记录按键次数加1
    }  
  }       
  P0IF = 0;             //清中断标志
 }
 
/************************************************
//主函数
************************************************/
void main(void)
{
  InitIO();	
  InitKeyINT();               //调用初始化函数
   
  while(1)
  {
    if(KeyTouchtimes == 1)       //按键设置为LED3,LED2,LED1倒序流水闪烁 
    {
      LED3 = !LED3;                
      Delayms(1000);           
      LED2 = !LED2;           
      Delayms(1000);            
      LED1 = !LED1;           
      Delayms(1000);
      KeyTouchtimes = 0;        
    }
  }
 }


