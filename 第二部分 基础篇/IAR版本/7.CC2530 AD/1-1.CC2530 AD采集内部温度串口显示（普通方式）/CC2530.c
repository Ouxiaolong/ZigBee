/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       AD采集内部温度串口显示（普通方式）
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <iocc2530.h>
#include <stdio.h>
#include <string.h>

/**宏定义***********************************************************************/
#define uchar unsigned char
#define uint unsigned int
#define int16 short 
#define uint16 unsigned short 
      
/**函数声明*********************************************************************/
void initclock(void);
void inituart0(void);
void uarttx_send_string(char *data,int len);
void Delay(uint xms);
uint gettemperature(void);

/**全局变量*********************************************************************/
int16 avgtemp;


/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void)
{
  char i;
  char tempvalue[30];
  
  initclock();//初始化时钟  
  inituart0();//初始化串口
  IEN0=IEN1=IEN2=0X00;//关闭所有中断
  ATEST=0X01;//开启温度传感器
  TR0=0X01;//将温度传感器与ADC连接起来
  
  while(1)
  {
    avgtemp=0;
    for(i=0;i<64;i++)
    {
      avgtemp +=gettemperature();//取得温度数，加上原平均值
      if(i>0) avgtemp>>=1;//除以2，取得平均值
    }
    
    memset(tempvalue, 0, 30);
    sprintf(tempvalue, "AD Data= %dC", (int)avgtemp);
    uarttx_send_string(tempvalue,strlen(tempvalue));
    //uarttx_send_string("\n",1);
    Delay(3000);
  }
}

/**
  * @brief     初始化时钟
  * @param     None
  * @retval    None
  */
void initclock(void)
{
  CLKCONCMD &=0XBF;//系统时钟源选择32MHZ XOSC
  CLKCONCMD &=0XF8;//系统时钟频率为32MHZ
  
  CLKCONCMD |=0X28;
  CLKCONCMD &=0XEF;//定时时钟频率为1MHZ
  while(CLKCONSTA & 0X40);//等待时钟稳定
}

/**
  * @brief     初始化串口0函数
  * @param     None
  * @retval    None
  */
void inituart0(void)
{
  PERCFG = 0x00;		         //位置1 P0口
  P0SEL = 0x3c;				 //P0用作串口
	
  P2DIR &= ~0XC0;                       //P0优先作为UART0    
  U0CSR |= 0x80;   	                //串口设置为UART方式
  U0GCR |= 11;				
  U0BAUD |= 216;		       //波特率设为115200

  UTX0IF = 1;                          //UART0 TX中断标志初始置位1  
  U0CSR |= 0X40;		       //允许接收
  IEN0 |= 0x84;			       //开总中断，接收中断
}


/**
  * @brief     串口发送字符串函数
  * @param     date  数据‘
               len   长度
  * @retval    None
  */
void uarttx_send_string(char *data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF=*data++;
    while(UTX0IF==0);
    UTX0IF=0;
  }
  U0DBUF=0X0A;//换行
  while(UTX0IF==0);
  UTX0IF=0;  
}

/**
  * @brief     延时函数
  * @param     xms   延时大小
  * @retval    None
  */
void Delay(uint xms)
{
   uint i,j;
    for(i=xms;i>0;i--)
     for(j=587;j>0;j--);   
}

/**
  * @brief     读取温度传感器AD值函数
  * @param     None
  * @retval    None
  */
uint gettemperature(void)
{
  uint i;
  uint16 adcvalue;
  uint16 value;
  
  adcvalue=0;
  for(i=0;i<4;i++)
  {
    ADCCON3 |=0X0E;//单通道AD转换源为温度传感器
    ADCCON3 &=0X3F;//单通道AD转换参考电压为1.25内部电压
    ADCCON3 |=0X30;//单通道AD转换分辨率为512DEC，12有效
    ADCCON1 |=0X30;//ADC启动方式选择为ADCCON1.ST=1事件
    ADCCON1 |=0X40;//ADC启动转换
        
    while(!ADCCON1&0X80);//等待AD转换完成
    value =  ADCL >> 2; //ADCL寄存器低2位无效
    value |=(((uint16)ADCH)<<6);//连接ADCH和ADCL，并赋值给value
    adcvalue +=value;//adcvalue被赋值为4次AD值之和
  }
  value=adcvalue>>2;//累加除以4，得到平均值
  //return (((value) >> 4) - 315)/10;     //根据AD值，计算出实际的温度
  return (uint)(((value>>2)-1367.5)/4.5-5);
  
}   