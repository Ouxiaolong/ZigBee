#ifndef __OLED_H
#define	__OLED_H


#include <ioCC2530.h>


#define LCD_SCL P1_2       //SCLK  时钟 D0（SCLK）
#define LCD_SDA P1_3       //SDA   D1（MOSI） 数据
#define LCD_CS  P1_7       //CS   片选  
#define LCD_DC  P0_0       //A0  H/L 命令数据选通端，H：数据，L:命令

#define XLevelL        0x00
#define XLevelH        0x10
#define XLevel         ((XLevelH&0x0F)*16+XLevelL)
#define Max_Column     128
#define Max_Row        64
#define Brightness     0xCF 
#define X_WIDTH        128
#define Y_WIDTH        64


//英文编码为0~127，所以大于127的中文
#define IS_CHINESE(x)       (((BYTE)(x))>(BYTE)0x7f )


typedef int            INT;
typedef const char*    LPCSTR;
typedef unsigned char BYTE;
typedef int	           LENGTH;


void DelayMS(unsigned int msec);
void LCD_DLY_ms(unsigned int ms);
void LCD_WrDat(unsigned char dat);                                      
void LCD_WrCmd(unsigned char cmd);
void LCD_Set_Pos(unsigned char x, unsigned char y);
void LCD_Fill(unsigned char bmp_dat);
void LCD_CLS(void);
void LCD_Init(void);
void LCD_P6x8Str(unsigned char x, unsigned char y,unsigned char ch[]);
void LCD_P8x16Str(unsigned char x, unsigned char y,unsigned char ch[]);
void Draw_BMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void LCD_FillAll(unsigned char bmp_dat);
void LCD_Clear(void);
void LCD_UpdataAll(void);
void TextOutChinese(unsigned char x, unsigned char y,unsigned char* chinese);
void TextOutAsc(unsigned char x, unsigned char y,unsigned char* asc);
void LCD_TextOut(unsigned char x, unsigned char y, unsigned char* str);
void LCD_DrawBmp(unsigned char x, unsigned char y);



#endif
