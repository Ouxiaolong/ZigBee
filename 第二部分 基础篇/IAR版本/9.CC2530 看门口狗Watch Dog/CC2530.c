/***************************************************
开发者：龙创科技

开发平台：CC2530

日期：2016.1

内容：看门狗
***************************************************/
# include <ioCC2530.h>

#define uint unsigned int 

#define LED1  P1_0 
#define LED2  P1_1

void InitLEDIO(void)
{
    P1DIR |= 0x03;  //P10、P11定义为输出
    LED1 = 1;
    LED2 = 1;
       //LED灯初始化为关   
}
 
void Init_Watchdog(void)
{
	WDCTL = 0x00;
	//时间间隔一秒，看门狗模式
	//WDCTL |= 0x08;
	
        //定时器模式
        WDCTL |= 0x0d;
}

void  SET_MAIN_CLOCK(int source) 
   {                                  
      if(source) {                            
        CLKCONCMD |= 0x40;          /*RC*/               
        while(!(CLKCONSTA &0X40));  /*待稳*/       
             }                                       
      else {                       
        CLKCONCMD &= ~0x47;        /*晶振*/             
        while((CLKCONSTA &0X40));  /*待稳*/  
      }                                       
   }
void FeetDog(void)
{
	WDCTL = 0xa0;
	WDCTL = 0x50;
}
void Delay(uint xms)
{
   uint i,j;
    for(i=xms;i>0;i--)
     for(j=587;j>0;j--);   
}

void main(void)
{
	SET_MAIN_CLOCK(0) ;
	InitLEDIO();
	Init_Watchdog();
        
        Delay(500);
        
	LED1=0;	       
	LED2=0;       
	while(1)
	{
	  //FeetDog();	
	}	//喂狗指令（加入后系统不复位，LED1和LED2不再闪烁）
}


