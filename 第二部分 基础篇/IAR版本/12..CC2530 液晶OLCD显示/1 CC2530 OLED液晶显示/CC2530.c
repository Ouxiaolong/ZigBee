/***************************************************
开发者： 龙创科技

开发平台：CC2530

日期：2016.1

内容：液晶LCD显示
***************************************************/
#include <ioCC2530.h>
#include "LCD.h"

void main()
{       
    int i;
    LCD_Init();                      //oled 初始化  
    LCD_CLS();                      //屏全亮 
    
    while(1)
    {
      for(i=0; i<4; i++)
      {
        DelayMS(500);
        LCD_P16x16Ch(16*(i+2), 0, i);
        if(i==100)
        {
          i=0;
        }
      }
      for(i=0; i<7; i++)
      {
        LCD_P16x16Ch(8+16*i, 2, 4+i);
      }
    
      DelayMS(500);
      LCD_P8x16Str(16, 5, "QQ:270139773");
      //LCD_P8x16Str(32, 6, "2016-05-01");
      LCD_Clear();
      
    }
}   


