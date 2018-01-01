/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       AD采集内部温度串口显示
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>
#include "initUART_Timer.h"
#include "stdio.h"
#include "string.h"
#include "LCD.h"

/**函数声明*********************************************************************/
void initTempSensor(void);
INT8 getTemperature(void);

/**全局变量*********************************************************************/
INT16 AvgTemp; 

/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void)
{		
  char i;      
  char TempValue[30]={0}; 

  InitUART0();        //初始化串口
  initTempSensor();  //初始化ADC
  
  LCD_Init();//初始化LCD           
  LCD_CLS();   
  LCD_welcome();    
       
  while(1)      
  {    
    AvgTemp = 0;    
    for(i = 0 ; i < 64 ; i++) 
    {
      AvgTemp += getTemperature();              
      AvgTemp >>= 1;      //每次累加后除2.
    }
       
    memset(TempValue, 0, 30);
    sprintf(TempValue, "ADTestRead = %dC", (INT8)AvgTemp);
    UartTX_Send_String(TempValue,strlen(TempValue));
    UartTX_Send_String("\n",1);
    LCD_P8x16Str(0, 4, (unsigned char*)TempValue);

    Delay(2000); 
  }
}


/**
  * @brief     温度传感器初始化函数	
  * @param     None
  * @retval    None
  */
void initTempSensor(void)
{
   DISABLE_ALL_INTERRUPTS();            //关闭所有中断
   InitClock();                         //设置系统主时钟为32M
   *((BYTE __xdata*) 0x624B) = 0x01;  //或者TR0=0X01;  //开启温度传感器,TR0的地址为0x624B
   *((BYTE __xdata*) 0x61BD) = 0x01;  //或者ATEST = 0x01; //将温度传感器与ADC连接起来,ATEST的地址为0x61BD
}

/**
  * @brief     读取温度传感器AD值函数	
  * @param     None
  * @retval    INT8
  */
INT8 getTemperature(void)
//float getTemperature(void)
{
/*
  //方法一
 uint value;
  
  ADCCON3 = (0x3E); //选择 1.25V 为参考电压； 12 位分辨率；对片内温度传感器采样
  ADCCON1 |= 0x30; //选择 ADC 的启动模式为手动
  ADCCON1 |= 0x40; //启动 AD 转化
  
  while(!(ADCCON1 & 0x80)); //等待 AD 转换完成
  value = ADCL >> 4; //ADCL 寄存器低 4 位无效
  value |= (((UINT16)ADCH) << 4);
  
  return (INT8)((value-1367.5)/4.5-4); 
  //根据 AD 值，计算出实际的温度,芯片、
  //手册有错，温度系数应该是 4.5 /℃
  //进行温度校正，这里减去 4℃（不同芯片根据具体情况校正）
*/  
  //方法二
  UINT8   i;
  UINT16  AdcValue;
  UINT16  value;

  AdcValue = 0;
  for( i = 0; i < 4; i++ )
  {
    ADC_SINGLE_CONVERSION(ADC_REF_1_25_V | ADC_14_BIT | ADC_TEMP_SENS);    // 使用1.25V内部电压，12位分辨率，AD源为：温度传感器
    ADC_SAMPLE_SINGLE();  //开启单通道ADC
   
    while(!ADC_SAMPLE_READY());      //等待AD转换完成
    value =  ADCL >> 2;              //ADCL寄存器低2位无效
    value |= (((UINT16)ADCH) << 6);    
    AdcValue += value;               //AdcValue被赋值为4次AD值之和
  }  
  value = AdcValue >> 4;           //累加除以4，得到平均值
    
  return ADC14_TO_CELSIUS(value);   //根据AD值，计算出实际的温度

}



