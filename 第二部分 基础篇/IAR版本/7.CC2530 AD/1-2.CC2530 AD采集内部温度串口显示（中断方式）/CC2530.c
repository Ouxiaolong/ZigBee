/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       AD采集内部温度串口显示（中断方式）
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>
#include "InitUART_Timer.h" 
#include "stdio.h"
#include "string.h"

/**函数声明*********************************************************************/
void initTempSensor(void);
float getTemperature(void);

/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void) 
{   
  char i; 
  char TempValue[30]={0}; 
  INT16 AvgTemp;    
  //char TempValue[6];   
  //float AvgTemp;         
       
  InitUART0();              //初始化串口   
  initTempSensor();         //初始化 ADC 
      
  while(1) 
  { 
    AvgTemp = 0;          
    for(i = 0 ; i < 64 ; i++) 
    {    
      AvgTemp += getTemperature();  
      AvgTemp=AvgTemp/2;                  //每次累加后除 2 
    }
    memset(TempValue, 0, 30);
    sprintf(TempValue, "ADTestRead = %dC", (INT8)AvgTemp);
    UartTX_Send_String(TempValue,strlen(TempValue));
 
 /*   
    //温度转换成ascii码发送     
    TempValue[0] = (unsigned char)(AvgTemp)/10 + 48;          //十位   
    TempValue[1] = (unsigned char)(AvgTemp)%10 + 48;          //个位
    TempValue[2] = '.';                                       //小数点         
    TempValue[3] = (unsigned char)(AvgTemp*10)%10+48;         //十分位
    TempValue[4] = (unsigned char)(AvgTemp*100)%10+48;        //百分位      
    TempValue[5] = '\0';                                   //字符串结束符   
    UartTX_Send_String( TempValue,6); 
 */  
   Delayms(2000); //使用32M晶振，故这里2000约等于1S
       
  } 
}


/**
  * @brief     温度传感器初始化函数    
  * @param     None
  * @retval    None
  */
void initTempSensor(void)
{ 
   DISABLE_ALL_INTERRUPTS();  //关闭所有中断 
   InitClock();               //设置系统主时钟为 32M 
   TR0=0X01;         //set '1' to connectthe temperature sensorto the SOC_ADC.
   ATEST=0X01;       // Enablesthe temperature sensor
}   

/**
  * @brief     读取温度传感器 AD 值函数  
  * @param     None
  * @retval    float
  */
float getTemperature(void)
{    
   uint  value; 
   ADCCON3  = (0x3E);    //选择1.25V为参考电压；14位分辨率；对片内温度传感器采样
   ADCCON1 |= 0x30;      //选择ADC的启动模式为手动
   ADCCON1 |= 0x40;      //启动AD转化  
   while(!(ADCCON1 & 0x80));        //等待 AD 转换完成 
   value =  ADCL >> 4;              //ADCL 寄存器低 2 位无效 
   value |= (((UINT16)ADCH) << 4);
   return (value-1367.5)/4.5-5;    //根据 AD 值，计算出实际的温度,芯片手册有错，温度系数应该是4.5 /℃
                                   //进行温度校正，这里减去5℃（不同芯片根据具体情况校正）
}

