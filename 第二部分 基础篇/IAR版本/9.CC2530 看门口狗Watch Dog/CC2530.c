/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       看门狗
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**宏定义***********************************************************************/
//定义数据类型
#define uint unsigned int 
//定义IO口
#define LED1  P1_0 
#define LED2  P1_1

/**函数声明*********************************************************************/
void InitLEDIO(void);
void Init_Watchdog(void);
void SET_MAIN_CLOCK(int source) ;
void FeetDog(void);
void Delay(uint xms);

/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void)
{	
  SET_MAIN_CLOCK(0) ;
  InitLEDIO();
  Init_Watchdog();
        
  Delay(1000);
        	
  LED1= 0;	       
  LED2= 0;       

  while(1)
  {
    FeetDog();	
  }	
  //喂狗指令（加入后系统不复位，LED1和LED2不再闪烁）
}

/**
  * @brief     LED初始化
  * @param     None
  * @retval    None
  */
void InitLEDIO(void)
{
    P1DIR |= 0x03;  //P10、P11定义为输出
    LED1 = 1;
    LED2 = 1;
    //LED灯初始化为关   
}
 
/**
  * @brief     初始化看门狗
  * @param     None
  * @retval    None
  */
void Init_Watchdog(void)
{
  WDCTL = 0x00;
	
  //时间间隔一秒，看门狗模式
  WDCTL |= 0x08;
}

/**
  * @brief     设置时钟模式
  * @param     None
  * @retval    None
  */
void  SET_MAIN_CLOCK(int source) 
{                                  
      
  if(source) 
  {                             
    CLKCONCMD |= 0x40;          /*RC*/               
    while(!(CLKCONSTA &0X40));  /*待稳*/           
  }                                       
      
  else 
  {  
    CLKCONCMD &= ~0x47;        /*晶振*/             
       
    while((CLKCONSTA &0X40));  /*待稳*/  
  }                                       
}

/**
  * @brief     喂狗
  * @param     None
  * @retval    None
  */
void FeetDog(void)
{	
  WDCTL = 0xa0;
  WDCTL = 0x50;
}

/**
  * @brief     延时函数
  * @param     xms 延时大小
  * @retval    None
  */
void Delay(uint xms)
{
   uint i,j;
    for(i=xms;i>0;i--)
     for(j=587;j>0;j--);   
}



