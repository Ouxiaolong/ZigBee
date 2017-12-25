#include <iocc2530.h>
#include "adc.h"
#include "uart.h"
#include "led.h"
#include <stdio.h>
#include <string.h>

/****************************************************************************
* 名    称: DelayMS()
* 功    能: 以毫秒为单位延时 16M时约为535,32M时要调整,系统时钟不修改默认为16M
* 入口参数: msec 延时参数，值越大延时越久
* 出口参数: 无
****************************************************************************/
void DelayMS(uint msec)
{  
  uint i,j;
  
  for (i=0; i<msec; i++)
    for (j=0; j<1070; j++);
}

/****************************************************************************
* 功    能: 初始化时钟参数
****************************************************************************/
void ClockInit(void)
{
    CLKCONCMD = 0x28;           //时器计数时钟设定为1M Hz,  系统时钟设定为32 MHz 
    while(CLKCONSTA & 0x40);    //等晶振稳定
}

/****************************************************************************
* 名    称: InitUart()
* 功    能: 串口初始化函数
* 入口参数: 无
* 出口参数: 无
****************************************************************************/
void InitUart(void)
{ 
  PERCFG = 0x00;           //外设控制寄存器 USART 0的IO位置:0为P0口位置1 
  P0SEL = 0x0c;            //P0_2,P0_3用作串口（外设功能）
  P2DIR &= ~0XC0;          //P0优先作为UART0
  
  U0CSR |= 0x80;           //设置为UART方式
  U0GCR |= 11;				       
  U0BAUD |= 216;           //波特率设为115200
  UTX0IF = 0;              //UART0 TX中断标志初始置位0
}

/****************************************************************************
* 发送函数 note: "length" is the length of one line
****************************************************************************/
void UartTX_Send_String(char *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
  U0DBUF = 0x0A;        // 换行
  while(UTX0IF == 0);
    UTX0IF = 0;
}

/****************************************************************************
* 格式化函数 将电压值转换成数组
****************************************************************************/
void format(float vol, char buf[6])
{
    char ge = 0;           //个位
    char fen = 0;          //分位
    char shifen = 0;       //十分位
    char baifen = 0;       //百分位
    uint i = 0;
    vol = vol*1000;        //扩大1000倍
    i = (uint)vol;         //转换为整形
    ge = (i / 1000) + 0x30;//转成字符
    fen = (i / 100 % 10) + 0x30;
    shifen =(i % 100 / 10) + 0x30;
    baifen = (i % 10) + 0x30;
    buf[0] = ge;
    buf[1] = '.';
    buf[2] = fen;
    buf[3] = shifen;
    buf[4] = baifen;
    buf[5] = 'v';
}

/****************************************************************************
* 单次采样，采用端口为P0.6
* This funciton  is order to initialize ADC of CC2530
****************************************************************************/
float getVol(void)
{
  uchar i = 0;
  uint value = 0;
  long uint AdcValue = 0;     //防止溢出
  float vol = 0.0;
  SET_IO_PORT_DIR(0,6,IO_IN); //设置P0..6为输入模式
  ADC_ENABLE_CHANNEL(6);      //使能通道6作为ADC的采样通道
  for(i=0; i<4; i++)
  {
    ADC_SINGLE_CONVERSION(ADC_REF_AVDD | ADC_12_BIT | ADC_AIN6);//片上3.3V参考电压,12位，6通道
    ADC_SAMPLE_SINGLE(); 
    while(!(ADCCON1 & 0x80));              //等待AD转换完成
    /*value =  ADCL >> 2;                  //ADCL寄存器低2位无效
    value |= (((uint)ADCH) << 6); */    
    value = ADCL>>4;                      
    value |= (((uint)ADCH) << 4);         
    AdcValue += value;  
  }
  AdcValue = AdcValue >> 2;                 //累加除以4，得到平均值
  if(AdcValue > 4096)   // 输入的电压0V时，因为会满量程，检测到AdcValue的12位值为0xfff
    AdcValue = 0;
  vol = (float)(AdcValue/(float)2048)*3.3;  //换算成电压值

  return vol;
}


void  main(void)
{
  uchar i=0;
  char vol[6];
  float average;
  float temp;
  P1_0 = 0;
  ClockInit();
  InitUart();
  SET_IO_PORT_DIR(1,0,IO_OUT);         //设置LED，作为ADC采样进行的标志
  IO_FUNC_PORT_PIN(1, 0, IO_FUNC_GIO); //INIT_LED(); 
  IEN0 = IEN1 = IEN2 =0;
 
  while(1)
  { 
   for(i=0; i<16; i++)//取16次电压的平均值
   {
     temp = getVol();
     average += temp;
   }
   average = average / 16;
   format(average, vol);
   UartTX_Send_String(vol,6);  //向串口发送数据
   //UartTX_Send_String("\r",1); //发送换行
   P1_0 = ~P1_0;
   DelayMS(2000); //两秒钟发一次
   average = 0.0;
  }
}      
