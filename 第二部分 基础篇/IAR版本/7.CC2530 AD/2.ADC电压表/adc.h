/******************************************************************************
    Filename: adc.h

    These functions/macros simplifies usage of the ADC.

    Copyright 2007 Texas Instruments, Inc.
******************************************************************************/

#ifndef _ADC_H
#define _ADC_H

/*******************************************************************************
 * INCLUDES
 */

#include "hal_types.h"
#include "hal_defs.h"
#include "uart.h"


extern float  ADCValue;
extern void ADInit(void);

// Include chip specific IO definition file
#if (chip == 2530 || chip == 2531)
#include <ioCC2530.h>
#elif (chip == 2430)
#include <ioCC2430.h>
#elif (chip == 2431)
#include <ioCC2431.h>
#elif (chip == 2510)
#include <ioCC2510.h>
#elif (chip == 2511)
#include <ioCC2511.h>
#elif (chip == 1110)
#include <ioCC1110.h>
#elif (chip == 1111)
#include <ioCC1111.h>
#endif



/*******************************************************************************
 * CONSTANTS AND MACROS
 */

// Macro for setting up a single conversion. If ADCCON1.STSEL = 11, using this
// macro will also start the conversion.
#define ADC_SINGLE_CONVERSION(settings) st( ADCCON3 = (settings); )

// Macro for setting up a single conversion
#define ADC_SEQUENCE_SETUP(settings)    st( ADCCON2 = (settings); )

// Where _settings_ are the following:
// Reference voltage:
#define ADC_REF_1_25_V      0x00     // Internal 1.25V reference
#define ADC_REF_P0_7        0x40     // External reference on AIN7 pin
#define ADC_REF_AVDD        0x80     // AVDD_SOC pin
#define ADC_REF_P0_6_P0_7   0xC0     // External reference on AIN6-AIN7 differential input

// Resolution (decimation rate):
#define ADC_7_BIT           0x00     //  64 decimation rate
#define ADC_9_BIT           0x10     // 128 decimation rate
#define ADC_10_BIT          0x20     // 256 decimation rate
#define ADC_12_BIT          0x30     // 512 decimation rate

// Input channel:
#define ADC_AIN0            0x00     // single ended P0_0
#define ADC_AIN1            0x01     // single ended P0_1
#define ADC_AIN2            0x02     // single ended P0_2
#define ADC_AIN3            0x03     // single ended P0_3
#define ADC_AIN4            0x04     // single ended P0_4
#define ADC_AIN5            0x05     // single ended P0_5
#define ADC_AIN6            0x06     // single ended P0_6
#define ADC_AIN7            0x07     // single ended P0_7
#define ADC_GND             0x0C     // Ground
#define ADC_TEMP_SENS       0x0E     // on-chip temperature sensor
#define ADC_VDD_3           0x0F     // (vdd/3)

// Macro for starting the ADC in continuous conversion mode
#define ADC_SAMPLE_CONTINUOUS()   \
  st( ADCCON1 &= ~0x30;           \
      ADCCON1 |= 0x10; )

// Macro for stopping the ADC in continuous mode
#define ADC_STOP()  st( ADCCON1 |= 0x30; )

// Macro for initiating a single sample in single-conversion mode (ADCCON1.STSEL = 11).
#define ADC_SAMPLE_SINGLE()       \
  st( ADC_STOP();                 \
      ADCCON1 |= 0x40; )

// Macro for configuring the ADC to be started from T1 channel 0. (T1 ch 0 must be in compare mode!!)
#define ADC_TRIGGER_FROM_TIMER1() \
  st( ADC_STOP();                 \
      ADCCON1 &= ~0x10; )

// Expression indicating whether a conversion is finished or not.
#define ADC_SAMPLE_READY()      st( ADCCON1 & 0x80 ;)

// Macro for setting/clearing a channel as input of the ADC
#define ADC_ENABLE_CHANNEL(ch)   ADCCFG |=  (0x01 << ch)
#define ADC_DISABLE_CHANNEL(ch)  ADCCFG &= ~(0x01 << ch)


// Macros for configuring the ADC input:
// Example usage:
//   IO_ADC_PORT0_PIN(0, IO_ADC_EN);
//   IO_ADC_PORT0_PIN(4, IO_ADC_DIS);
//   IO_ADC_PORT0_PIN(6, IO_ADC_EN);

#define IO_ADC_PORT0_PIN(pin, adcEn)    \
  st( if (adcEn)                        \
        ADCCFG |= BM( pin );            \
      else                              \
        ADCCFG &= ~BM( pin ) )

// where adcEn is one of:
#define IO_ADC_EN           1 // ADC input enabled
#define IO_ADC_DIS          0 // ADC input disab


/*******************************************************************************
 * PUBLIC FUNCTIONS
 */

int16 adcSampleSingle(uint8 reference, uint8 resolution, uint8 channel);


/*****************************************************************************/
#endif
