#ifndef _LED_H_
#define _LED_H_

#include<iocc2530.h>
#include"uart.h"


extern void delay(uint n);
extern void LED(void);
/***
*Example:
*SET_IO_PORT_DIR(0,7,IO_OUT)----P0.7 as output
*
*
**/
#define SET_IO_PORT_DIR(port,pin,dir) \
  do                              \
{                                 \
  if(dir==IO_OUT)                 \
    P##port##DIR |=(0X01<<pin);   \
  else                           \
    P##port##DIR &= ~(0X01<<pin);\
}while(0)
//  port={0,1,2}, pin={0,..,7} and dir is one of them:
#define IO_IN   0
#define IO_OUT  1
/***
*Example:
*SET_IO_PORT_INPUT_MODE(0,7,TRI)----P0.7 the mode of input is tristate;
****/
#define SET_IO_PORT_INPUT_MODE(port,pin,mode) \
  do                              \
{                                 \
  if(mode==TRI)                   \
    P##port##INP |=(0X01<<pin);   \
  else                            \
    P##port##INP &= ~(0X01<<pin); \
}while(0)
// where imode is one of them:
#define IO_IMODE_PUD  0 // Pull-up/pull-down
#define IO_IMODE_TRI  1 // Tristate


//该宏定义了IO的端口模式，是作为普通IO还是最为外设IO 
// Example usage:
//   IO_FUNC_PORT0_PIN0(0, 0, IO_FUNC_PERIPH);
//   IO_FUNC_PORT0_PIN1(0, 1, IO_FUNC_GIO);
//   IO_FUNC_PORT2_PIN3(2, 3, IO_FUNC_PERIPH);

#define IO_FUNC_PORT_PIN(port, pin, func)  \
   do {                                    \
      if((port == 2) && (pin == 3)){       \
         if (func) {                       \
            P2SEL |= 0x02;                 \
         } else {                          \
            P2SEL &= ~0x02;                \
         }                                 \
      }                                    \
      else if((port == 2) && (pin == 4)){  \
         if (func) {                       \
            P2SEL |= 0x04;                 \
         } else {                          \
            P2SEL &= ~0x04;                \
         }                                 \
      }                                    \
      else{                                \
         if (func) {                       \
            P##port##SEL |= (0x01<<(pin)); \
         } else {                          \
            P##port##SEL &= ~(0x01<<(pin));\
        }                                  \
      }                                    \
   } while (0)

// where func is one of:
#define IO_FUNC_GIO     0 // General purpose I/O
#define IO_FUNC_PERIPH  1 // Peripheral function

/**
*example:
*SET_ADC_CHANNEL(7)
*/
#define SET_ADC_CHANNEL(ch)\
  do{                       \
      ADCCON2 |= (0x01<<ch);\
}while(0)

#endif