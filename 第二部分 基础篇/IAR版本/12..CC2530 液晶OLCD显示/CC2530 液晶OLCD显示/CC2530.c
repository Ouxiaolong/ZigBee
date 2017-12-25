/***************************************************
开发者： 龙创科技

开发平台：CC2530

日期：2016.1

内容：液晶OLCD显示
***************************************************/
#include <ioCC2530.h>
#include "OLED.h"

void main()
{
    LCD_Init();
  
    while(1)
    {
      //显示"欢迎使用龙创科技产品!”
      LCD_Clear();
      LCD_TextOut(32, 16, "欢迎使用");
      LCD_TextOut(13, 33, "龙创科技产品!");
      LCD_UpdataAll();
      DelayMS(3000);
 /*
      //显示中英文混合字符串
      LCD_Clear();
      LCD_TextOut(0, 16, "欢迎使用");
      LCD_TextOut(32, 32, "OLED显示屏");
      LCD_UpdataAll();
      DelayMS(3000);
  */  
      //显示QQ信息
      LCD_Clear();
      LCD_TextOut(0, 16, "QQ:");
      LCD_TextOut(0, 32, "270139773");
      LCD_UpdataAll();
      DelayMS(3000);
/*
      //显示Bmp单色图片
      LCD_Clear();
      LCD_DrawBmp(0, 8);
      LCD_UpdataAll();
      DelayMS(3000);
*/
    }  
}   








































































/*
uchar data_bus;
void check_busy(void)
{
  uchar read_data = 0xff;
  data_bus = 0xff;
  //复位LCD
  LCD_RS = 0;
  //读命令
  LCD_RW = 1;
  //片使能
  LCD_CS1 = 0;
  
  while(read_data & 0x80)
  {
    LCD_E = 1;
    _nop_();
    _nop_();
    read_data = data_bus;
    LCD_E = 0;
  }
  
  LCD_E = 0;
  //片禁能
  LCD_CS1 = 1;
  
}

//写命令道寄存器
void send_cmd(uchar cmd)
{
  check_busy();
  //复位
  LCD_RS = 0;
  //写命令
  LCD_RW = 0;
  //片使能
  LCD_CS1 = 0;
  data_bus = cmd;
  
  LCD_E = 1;
  
  _nop_();
  _nop_();
  
  LCD_E = 0;
  
  _nop_();
  _nop_();
  //片禁能
  LCD_CS1 = 1;
}

//写数据到DDRAM
void send_dat(uchar dat)
{
  check_busy();
  LCD_RS = 1;
  LCD_RW = 0;
  //片使能
  LCD_CS1 = 0;
  data_bus = dat;
  LCD_E = 1;
  _nop_();
  _nop_();
  LCD_E = 0;
  _nop_();
  _nop_();
  //片禁能
  LCD_CS1 = 1;
}

void lcd_initial(void)
{
  P1DIR |= 0xFC;
        P2DIR |= 0x01;
        P0DIR |= 0x02;
        P1_2 = 0;
  
  LCD_RS = 1;
  delay_nms(50);
  send_cmd(0xE2);
  send_cmd(0xA3);
  send_cmd(0xA0);
  send_cmd(0xC8);
  send_cmd(0x24);
  send_cmd(0x81);
  send_cmd(0x14);
  send_cmd(0x2C);
  send_cmd(0x2E);
  send_cmd(0x2F);
  send_cmd(0x40);
  send_cmd(0xB0);
  send_cmd(0x10);
  send_cmd(0x00);
  send_cmd(0xAF);
}
*/






















