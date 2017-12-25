#include "OLED.h"
#include "code.h"
#include <string.h>

unsigned char g_LcdBuff[Y_WIDTH/8][X_WIDTH];//LCD显存的缓冲


void DelayMS(unsigned int msec)
{ 
    unsigned int i,j;
    
    for (i=0; i<msec; i++)
        for (j=0; j<600; j++);
}

/*********************LCD 延时1ms************************************/
void LCD_DLY_ms(unsigned int ms)
{                         
    unsigned int a;
    while(ms)
    {
        a=1800;
        while(a--);
        ms--;
    }
    return;
}
/*********************LCD写数据************************************/ 
void LCD_WrDat(unsigned char dat)     
{
    unsigned char i=8, temp=0;
    LCD_DC=1;  
    for(i=0;i<8;i++) //发送一个八位数据 
    {
        LCD_SCL=0;  
        
        temp = dat&0x80;
        if (temp == 0)
        {
            LCD_SDA = 0;
        }
        else
        {
            LCD_SDA = 1;
        }
        LCD_SCL=1;             
        dat<<=1;    
    }
}
/*********************LCD写命令************************************/                                        
void LCD_WrCmd(unsigned char cmd)
{
    unsigned char i=8, temp=0;
    LCD_DC=0;
    for(i=0;i<8;i++) //发送一个八位数据 
    { 
        LCD_SCL=0; 
       
        temp = cmd&0x80;
        if (temp == 0)
        {
            LCD_SDA = 0;
        }
        else
        {
            LCD_SDA = 1;
        }
        LCD_SCL=1;
        cmd<<=1;;        
    }     
}
/*********************LCD 设置坐标************************************/
void LCD_Set_Pos(unsigned char x, unsigned char y) 
{ 
    LCD_WrCmd(0xb0+y);
    LCD_WrCmd(((x&0xf0)>>4)|0x10);
    LCD_WrCmd((x&0x0f)|0x01); 
} 
/*********************LCD全屏************************************/
void LCD_Fill(unsigned char bmp_dat) 
{
    unsigned char y,x;
    for(y=0;y<8;y++)
    {
        LCD_WrCmd(0xb0+y);
        LCD_WrCmd(0x01);
        LCD_WrCmd(0x10);
        for(x=0;x<X_WIDTH;x++)
            LCD_WrDat(bmp_dat);
    }
}
/*********************LCD复位************************************/
void LCD_CLS(void)
{
    unsigned char y,x;    
    for(y=0;y<8;y++)
    {
        LCD_WrCmd(0xb0+y);
        LCD_WrCmd(0x01);
        LCD_WrCmd(0x10); 
        for(x=0;x<X_WIDTH;x++)
            LCD_WrDat(0);
    }
}
/*********************LCD初始化************************************/
void LCD_Init(void)     
{  
    P0SEL &= 0xFE; //让P0.0 为普通IO口，
    P0DIR |= 0x01; //让P0.0 为为输出

    P1SEL &= 0x73; //让 P1.2 P1.3、P1.7为普通IO口
    P1DIR |= 0x8C; //把 P1.2 P1.3、P1.7设置为输出
    
    LCD_CS=0;//
    LCD_DLY_ms( 500 );
      
    LCD_SCL=1;

    LCD_WrCmd(0xae);//--turn off oled panel
    LCD_WrCmd(0x00);//---set low column address
    LCD_WrCmd(0x10);//---set high column address
    LCD_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    LCD_WrCmd(0x81);//--set contrast control register
    LCD_WrCmd(0xcf); // Set SEG Output Current Brightness
    LCD_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
    LCD_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
    LCD_WrCmd(0xa6);//--set normal display
    LCD_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
    LCD_WrCmd(0x3f);//--1/64 duty
    LCD_WrCmd(0xd3);//-set display offset    Shift Mapping RAM Counter (0x00~0x3F)
    LCD_WrCmd(0x00);//-not offset
    LCD_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
    LCD_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
    LCD_WrCmd(0xd9);//--set pre-charge period
    LCD_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    LCD_WrCmd(0xda);//--set com pins hardware configuration
    LCD_WrCmd(0x12);
    LCD_WrCmd(0xdb);//--set vcomh
    LCD_WrCmd(0x40);//Set VCOM Deselect Level
    LCD_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
    LCD_WrCmd(0x02);//
    LCD_WrCmd(0x8d);//--set Charge Pump enable/disable
    LCD_WrCmd(0x14);//--set(0x10) disable
    LCD_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
    LCD_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
    LCD_WrCmd(0xaf);//--turn on oled panel
    LCD_Fill(0xff);  //初始清屏
    LCD_Set_Pos(0,0);     
} 
/***************功能描述：显示6*8一组标准ASCII字符串    显示的坐标（x,y），y为页范围0～7****************/
void LCD_P6x8Str(unsigned char x, unsigned char y,unsigned char ch[])
{
    unsigned char c=0,i=0,j=0;      
    while (ch[j]!='\0')
    {    
        c =ch[j]-32;
        if(x>126){x=0;y++;}
        LCD_Set_Pos(x,y);    
        for(i=0;i<6;i++)     
            LCD_WrDat(F6x8[c][i]);  
        x+=6;
        j++;
    }
}
/*******************功能描述：显示8*16一组标准ASCII字符串     显示的坐标（x,y），y为页范围0～7****************/
void LCD_P8x16Str(unsigned char x, unsigned char y,unsigned char ch[])
{
    unsigned char c=0,i=0,j=0;
    while (ch[j]!='\0')
    {    
        c =ch[j]-32;
        if(x>120){x=0;y++;}
        LCD_Set_Pos(x,y);    
        for(i=0;i<8;i++)     
            LCD_WrDat(F8X16[c*16+i]);
        LCD_Set_Pos(x,y+1);    
        for(i=0;i<8;i++)     
            LCD_WrDat(F8X16[c*16+i+8]);  
        x+=8;
        j++;
    }
}
/*****************功能描述：显示16*16点阵  显示的坐标（x,y），y为页范围0～7****************************/
/*void LCD_P16x16Ch(unsigned char x, unsigned char y, unsigned char N)
{
    unsigned char wm=0;
    unsigned int adder=32*N;  //      
    LCD_Set_Pos(x , y);
    for(wm = 0;wm < 16;wm++)  //             
    {
        LCD_WrDat(F16x16[adder]);    
        adder += 1;
    }      
    LCD_Set_Pos(x,y + 1); 
    for(wm = 0;wm < 16;wm++) //         
    {
        LCD_WrDat(F16x16[adder]);
        adder += 1;
    }           
}
*/
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void Draw_BMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{     
    unsigned int j=0;
    unsigned char x,y;
    
    if(y1%8==0) y=y1/8;      
    else y=y1/8+1;
    for(y=y0;y<y1;y++)
    {
        LCD_Set_Pos(x0,y);                
        for(x=x0;x<x1;x++)
        {      
            LCD_WrDat(BMP[j++]);            
        }
    }
} 

void LCD_FillAll(unsigned char bmp_dat) 
{
    unsigned char y,x;
    for(y=0;y<8;y++)
    {
        for(x=0;x<X_WIDTH;x++)
        {
            g_LcdBuff[y][x]=bmp_dat;
        }
    }
}

void LCD_Clear(void)
{
    memset(g_LcdBuff, 0, sizeof(g_LcdBuff));
}

void LCD_UpdataAll(void) 
{
    unsigned char y,x;
    for(y=0;y<8;y++)
    {
        LCD_WrCmd(0xb0+y);
        LCD_WrCmd(0x01);
        LCD_WrCmd(0x10);
        for(x=0;x<X_WIDTH;x++)
            LCD_WrDat(g_LcdBuff[y][x]);
    }
}

void TextOutChinese(unsigned char x, unsigned char y,unsigned char* chinese)
{
    unsigned char c_index=0;
    unsigned char x_index, y_index, y_offset;
    unsigned char c=0, data, i, j;
    unsigned char* addr=0;

    if(chinese==0) return;

    addr=getChineseCode(chinese);
    
    //一个汉字32个字节
    for(i=0;i<32;i++)
    {
        //取出数据
        data=addr[i];

        //填充lcdbuff
        for(j=0; j<8; j++)
        {
            y_index=(y+j)/8+i/16;
            y_offset=(y+j)%8;
            x_index=x+i%16;

            if(y_index>=Y_WIDTH || x_index>=X_WIDTH)
            {
                break;
            }

            if((data&0x01)==0)
            {
                g_LcdBuff[y_index][x_index] &= ~(1<<y_offset);
            }
            else
            {
                g_LcdBuff[y_index][x_index] |= (1<<y_offset);
            }

            data>>=1;   
        }
    }


}

void TextOutAsc(unsigned char x, unsigned char y,unsigned char* asc)
{
    unsigned char c_index=0;
    unsigned char x_index, y_index, y_offset;
    unsigned char c=0, data, i, j;

    y_index=y/8;
    y_offset=y%8;

    if(asc==0) return;

    c =*asc-32;

    //第一行,每个asc16个字节
    for(i=0;i<16;i++)
    {
        //取出数据
        data=F8X16[c*16+i];

        //填充lcdbuff
        for(j=0; j<8; j++)
        {
            y_index=(y+j)/8+i/8;
            y_offset=(y+j)%8;
            x_index=x+i%8;

            if(y_index>=Y_WIDTH || x_index>=X_WIDTH)
            {
                break;
            }

            if((data&0x01)==0)
            {
                g_LcdBuff[y_index][x_index] &= ~(1<<y_offset);
            }
            else
            {
                g_LcdBuff[y_index][x_index] |= (1<<y_offset);
            }

            data>>=1;   
        }
    }    
}

/*****************功能描述：显示16*16点阵  显示的坐标（x,y），y为页范围0～7****************************/
void LCD_TextOut(unsigned char x, unsigned char y, unsigned char* str)
{
    unsigned char len=0;
    unsigned char i=0,j=0,k=0;
    unsigned char* addr=0;

    if(str==0) return;
 
    len=strlen(str);
    for(i=0; i<len; )
    {
        if(IS_CHINESE(str[i]))
        {
            TextOutChinese(x, y, str+i);
            i+=2;
            x+=16;
        }
        else
        {
            TextOutAsc(x, y, str+i);
            i++;
            x+=8;
        }

        if(x>=X_WIDTH) return;
    }        
}

//图片为水平扫描方式
void LCD_DrawBmp(unsigned char x, unsigned char y)
{
  unsigned char bmp_width=128;  //对应的图片宽度
  unsigned char bmp_height=48;  //对应的图片高度
  unsigned char xx=0,yy=0,zz=0;
  unsigned char x_index=0, y_index=0, y_offset=0; //填充数据时x坐标和Y坐标的偏移
  unsigned char data=0;
  unsigned int offset=0;
  unsigned char line_byte_count=bmp_width/8;//每一行的字节数
  
  for(yy=0; yy<bmp_height; yy++)
  {
    for(xx=0; xx<line_byte_count; xx++)
    {
      offset=line_byte_count*yy+xx;
      data=gImage_t[offset];//取出当前偏移的数据
      
      for(zz=0; zz<8; zz++)
      {
        x_index=x+xx*8+zz;  //计算当前X的坐标
        y_index=(y+yy)/8;    //计算当前Y坐标
        y_offset=(y+yy)%8;//Y坐标偏移
        
        
        if(x_index>=X_WIDTH) continue;
        if(y_index>=Y_WIDTH) continue;
        
        if((data&0x80)==0)
        {
            g_LcdBuff[y_index][x_index] &= ~(1<<y_offset);
        }
        else
        {
            g_LcdBuff[y_index][x_index] |= (1<<y_offset);
        }

          data<<=1;   
      }
    }
  }  
}


