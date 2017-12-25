/***************************************************
开发者：龙创科技

开发平台：CC2530

日期：2016.1

内容：随机数发生器
***************************************************/
#include "ioCC2530.h"
#include "Uart.h"
#include "hal.h"

#define KEY1 P0_4  
#define LED1 P1_0

//函数说明
void Init_RandomGenerator(void);

uint Random=0;// Random Sequence
char TX_data[4];

/**************************************************
 函 数 名  : main
 功能描述  : 随机数发生器(由串口将随机数发给电脑显示)
 输入参数  : NONE  
 输出参数  : NONE
 返 回 值  : NONE
***************************************************/
void main(void)
{    
    uint Data_H,Data_L;
  
    SetSysClock();  //设置系统时钟为32MHz
    InitUART();  //初始化串口
   
    Init_RandomGenerator(); //初始化随机数发生器
   
    while(1)
    {       
        //更新LFSR
        ADCCON1 |= 0x04;
        
        // Read Randomom register          
        Data_H=RNDH;  //读相关寄存器
        Data_L=RNDL;
  
        Random = (((uint)Data_H << 8) | Data_L);//获取随机数
        memset(TX_data, 0, sizeof(TX_data));
        
        TX_data[0]=(char)(Random/4096);   //数据处理
        TX_data[1]=(char)((Random%4096)/256);
        TX_data[2]=(char)(((Random%4096)%256)/16);
        TX_data[3]=(char)(((Random%4096)%256)%16);
       
        UartSend_String(TX_data,4);  //串口发给电脑显示
        
        Delayms(1000);
    }
}
/**************************************************
 函 数 名  : Init_RandomGenerator
 功能描述  : 初始化随机数发生器
 输入参数  : NONE  
 输出参数  : NONE
 返 回 值  : NONE
***************************************************/
void Init_RandomGenerator(void)
{  
   /*当需要一个真正的随机值，LFSR 应通过写入RNDL 产生种子，
     随机值来自在RF 接收路径的IF_ADC。要
     使用这种产生种子的方法，无线电必须首先上电*/
    RFRND = 0x04;

   // 等待上电完毕
    while( RFRND & 0x10 );

   //无线电应处于无限TX 状态，以避免RX 状态可能的同步检测
    RFST = 0xE2;
    Delayms(1);
    
    /*RCTRL[1:0]---控制16 位随机数发生器
      [00：] 正常运行。(13X 型展开)*/
    ADCCON1 &= ~0x0C;   

    RNDH = ADCTEST2;
      
    /*更新LFSR 的一种方式是设置ADCCON1.RCTRL 为01。
      [01：] LFSR 的时钟一次(没有展开).*/
    ADCCON1 |= 0x04;
}

/*********************************************END OF FILE**********************/