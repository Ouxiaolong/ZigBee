/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2018-01
  * @brief       温湿度传感器应用
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>
#include <string.h>
#include "UART.H" 
#include "DHT11.H" 
#include "LCD.h"

/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void)
{  
  uchar temp[3]; 
  uchar humidity[3];   
  uchar strTemp[13]="Temperature:";
  uchar strHumidity[10]="Humidity:";
    
   
  Delay_ms(1000);          //让设备稳定
  InitUart();              //串口初始化
  LCD_Init();                 //oled 初始化  
  LCD_CLS();                  //屏全亮   
  LCD_welcome();
    
  while(1)  
  {             
    memset(temp, 0, 3);    
    memset(humidity, 0, 3);
            
    DHT11();             //获取温湿度

        
    /*
    将温湿度的转换成字符串      
    将十进制数转换成 ASCII 码，0x30 就是 ASCII 码里的 0 ，      
    然后通过串口将最终温湿度值发送给电脑显示出来。    
    */
        
    temp[0]=wendu_shi+0x30;    
    temp[1]=wendu_ge+0x30;
    humidity[0]=shidu_shi+0x30;
    humidity[1]=shidu_ge+0x30;
            
    //获得的温湿度通过串口输出到电脑显示
    UartSendString(strTemp, 12);    
    UartSendString(temp, 2);
    UartSendString("   ", 3);
    UartSendString(strHumidity, 9);
    UartSendString(humidity, 2);
    UartSendString("\n", 1);
            
    Delay_ms(500);    
    LCD_P8x16Str(16, 2, "Humidity:");    
    LCD_P8x16Str(86, 2, (unsigned char*)humidity);
           
    Delay_ms(500);       
    LCD_P8x16Str(16, 4, "Temp:");
    LCD_P8x16Str(64, 4, (unsigned char*)temp);
               
    Delay_ms(1000);                   //延时函数使用定时器方式  
  }
}
