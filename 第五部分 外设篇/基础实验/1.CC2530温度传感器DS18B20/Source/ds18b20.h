#ifndef __DS18B20_H__
#define __DS18B20_H__
#include"iocc2530.h"

extern unsigned char Ds18b20Initial(void);
unsigned char ReadDs18B20(void);
float floatReadDs18B20(void);
#endif