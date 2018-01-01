#ifndef HAL_H
#define HAL_H

#include "ioCC2530.h"

/******************************************************************************
*******************              Commonly used types        *******************
******************************************************************************/
typedef unsigned char       BOOL;

// Data
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;

// Unsigned numbers
typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned long       UINT32;

// Signed numbers
typedef signed char         INT8;
typedef signed short        INT16;
typedef signed long         INT32;

//-----------------------------------------------------------------------------
// Common values
#ifndef FALSE
   #define FALSE 0
#endif

#ifndef TRUE
   #define TRUE 1
#endif

#ifndef NULL
   #define NULL 0
#endif

#ifndef HIGH
   #define HIGH 1
#endif

#ifndef LOW
   #define LOW 0
#endif

//-----------------------------------------------------------------------------

#define UPPER_BYTE(a) ((BYTE) (((WORD)(a)) >> 8))
#define HIBYTE(a) UPPER_BYTE(a)

#define LOWER_BYTE(a) ((BYTE) ( (WORD)(a))      )
#define LOBYTE(a) LOWER_BYTE(a)

#define SET_WORD(regH, regL, word) \
   do{                             \
      (regH) = UPPER_BYTE((word)); \
      (regL) = LOWER_BYTE((word)); \
   }while(0)

#define READ_RFR16(reg) ((((WORD) ##reg##H) << 8) + ##reg##L)
#define WRITE_RFR16(reg, value) do { ##reg##H = HIBYTE(value); ##reg##L = LOBYTE(value); } while (0)





/******************************************************************************
*******************             Port functions/macros       *******************
******************************************************************************/

// Macros for simplifying access to I/O pin setup and usage

//*****************************************************************************


// Macros for configuring IO peripheral location:
// Example usage:
//   IO_PER_LOC_TIMER1_AT_PORT0_PIN234();
//   IO_PER_LOC_TIMER4_AT_PORT2_PIN03();
//   IO_PER_LOC_USART1_AT_PORT0_PIN2345();

#define IO_PER_LOC_TIMER1_AT_PORT0_PIN234() do { PERCFG = (PERCFG&~0x40)|0x00; } while (0)
#define IO_PER_LOC_TIMER1_AT_PORT1_PIN012() do { PERCFG = (PERCFG&~0x40)|0x40; } while (0)

#define IO_PER_LOC_TIMER3_AT_PORT1_PIN34()  do { PERCFG = (PERCFG&~0x20)|0x00; } while (0)
#define IO_PER_LOC_TIMER3_AT_PORT1_PIN67()  do { PERCFG = (PERCFG&~0x20)|0x20; } while (0)

#define IO_PER_LOC_TIMER4_AT_PORT1_PIN01()  do { PERCFG = (PERCFG&~0x10)|0x00; } while (0)
#define IO_PER_LOC_TIMER4_AT_PORT2_PIN03()  do { PERCFG = (PERCFG&~0x10)|0x10; } while (0)

#define IO_PER_LOC_SPI1_AT_PORT0_PIN2345()  do { PERCFG = (PERCFG&~0x08)|0x00; } while (0)
#define IO_PER_LOC_SPI1_AT_PORT1_PIN4567()  do { PERCFG = (PERCFG&~0x08)|0x08; } while (0)

#define IO_PER_LOC_SPI0_AT_PORT0_PIN2345()  do { PERCFG = (PERCFG&~0x04)|0x00; } while (0)
#define IO_PER_LOC_SPI0_AT_PORT1_PIN2345()  do { PERCFG = (PERCFG&~0x04)|0x04; } while (0)

#define IO_PER_LOC_UART1_AT_PORT0_PIN2345() do { PERCFG = (PERCFG&~0x02)|0x00; } while (0)
#define IO_PER_LOC_UART1_AT_PORT1_PIN4567() do { PERCFG = (PERCFG&~0x02)|0x02; } while (0)

#define IO_PER_LOC_UART0_AT_PORT0_PIN2345() do { PERCFG = (PERCFG&~0x01)|0x00; } while (0)
#define IO_PER_LOC_UART0_AT_PORT1_PIN2345() do { PERCFG = (PERCFG&~0x01)|0x01; } while (0)


// Actual MCU pin configuration:
//
// Peripheral I/O signal     Alt1       Alt2
// -------------------------------------------
// Timer1 channel0           P0.2       P1.2
// Timer1 channel1           P0.3       P1.1
// Timer1 channel2           P0.4       P1.0
// Timer3 channel0           P1.3       P1.6
// Timer3 channel1           P1.4       P1.7
// Timer4 channel0           P1.0       P2.0
// Timer4 channel1           P1.1       P2.3
// USART0 TXD/MOSI           P0.3       P1.5
// USART0 RXD/MISO           P0.2       P1.4
// USART0 RTS/SCK            P0.5       P1.3
// USART0 CTS/SS_N           P0.4       P1.2
// USART1 TXD/MOSI           P0.4       P1.6
// USART1 RXD/MISO           P0.5       P1.7
// USART1 RTS/SCK            P0.3       P1.5
// USART1 CTS/SS_N           P0.2       P1.4

// Macros for configuring IO direction:
// Example usage:
//   IO_DIR_PORT_PIN(0, 3, IO_IN);    // Set P0_3 to input
//   IO_DIR_PORT_PIN(2, 1, IO_OUT);   // Set P2_1 to output

#define IO_DIR_PORT_PIN(port, pin, dir)  \
   do {                                  \
      if (dir == IO_OUT)                 \
         P##port##DIR |= (0x01<<(pin));  \
      else                               \
         P##port##DIR &= ~(0x01<<(pin)); \
   }while(0)

// Where port={0,1,2}, pin={0,..,7} and dir is one of:
#define IO_IN   0
#define IO_OUT  1

// Macros for configuring IO input mode:
// Example usage:
//   IO_IMODE_PORT_PIN(0,0,IO_IMODE_PUD);
//   IO_IMODE_PORT_PIN(2,0,IO_IMODE_TRI);
//   IO_IMODE_PORT_PIN(1,3,IO_IMODE_PUD);

#define IO_IMODE_PORT_PIN(port, pin, imode) \
   do {                                     \
      if (imode == IO_IMODE_TRI)            \
         P##port##INP |= (0x01<<(pin));     \
      else                                  \
         P##port##INP &= ~(0x01<<(pin));    \
   } while (0)

// where imode is one of:
#define IO_IMODE_PUD  0 // Pull-up/pull-down
#define IO_IMODE_TRI  1 // Tristate

// Macro for configuring IO drive mode:
// Example usage:
//   IIO_PUD_PORT(0, IO_PULLUP);
//   IIO_PUD_PORT(1, IO_PULLDOWN);
//   IIO_PUD_PORT(2, IO_PULLUP);

#define IO_PUD_PORT(port, pud)        \
   do {                               \
      if (pud == IO_PULLDOWN)         \
         P2INP |= (0x01 << (port+5)); \
      else                            \
         P2INP &= ~(0x01 << (port+5));\
   } while (0)

#define IO_PULLUP          0
#define IO_PULLDOWN        1

// Macros for function select (General purpose I/O / Peripheral function):
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

// Macros for configuring the ADC input:
// Example usage:
//   IO_ADC_PORT0_PIN(0, IO_ADC_EN);
//   IO_ADC_PORT0_PIN(4, IO_ADC_DIS);
//   IO_ADC_PORT0_PIN(6, IO_ADC_EN);

#define IO_ADC_PORT0_PIN(pin, adcEn) \
   do {                              \
      if (adcEn)                     \
         ADCCFG |= (0x01<<pin);      \
      else                           \
         ADCCFG &= ~(0x01<<pin); }   \
   while (0)

// where adcEn is one of:
#define IO_ADC_EN           1 // ADC input enabled
#define IO_ADC_DIS          0 // ADC input disab

/******************************************************************************
*******************       Interrupt functions/macros        *******************
******************************************************************************/

// Macros which simplify access to interrupt enables, interrupt flags and
// interrupt priorities. Increases code legibility.

//******************************************************************************

#define INT_ON   1
#define INT_OFF  0
#define INT_SET  1
#define INT_CLR  0

// Global interrupt enables
#define INT_GLOBAL_ENABLE(on) EA=(!!on)

#define DISABLE_ALL_INTERRUPTS() (IEN0 = IEN1 = IEN2 = 0x00)

#define INUM_RFERR 0
#define INUM_ADC   1
#define INUM_URX0  2
#define INUM_URX1  3
#define INUM_ENC   4
#define INUM_ST    5
#define INUM_P2INT 6
#define INUM_UTX0  7
#define INUM_DMA   8
#define INUM_T1    9
#define INUM_T2    10
#define INUM_T3    11
#define INUM_T4    12
#define INUM_P0INT 13
#define INUM_UTX1  14
#define INUM_P1INT 15
#define INUM_RF    16
#define INUM_WDT   17

#define NBR_OF_INTERRUPTS 18

// Macro used together with the INUM_* constants
// to enable or disable certain interrupts.
// Example usage:
//   INT_ENABLE(INUM_RFERR, INT_ON);
//   INT_ENABLE(INUM_URX0, INT_OFF);
//   INT_ENABLE(INUM_T1, INT_ON);
//   INT_ENABLE(INUM_T2, INT_OFF);
#define INT_ENABLE(inum, on)                        \
   do {                                             \
      if      (inum==INUM_RFERR) { RFERRIE = on; }  \
      else if (inum==INUM_ADC)   { ADCIE   = on; }  \
      else if (inum==INUM_URX0)  { URX0IE  = on; }  \
      else if (inum==INUM_URX1)  { URX1IE  = on; }  \
      else if (inum==INUM_ENC)   { ENCIE   = on; }  \
      else if (inum==INUM_ST)    { STIE    = on; }  \
      else if (inum==INUM_P2INT) { (on) ? (IEN2 |= 0x02) : (IEN2 &= ~0x02); } \
      else if (inum==INUM_UTX0)  { (on) ? (IEN2 |= 0x04) : (IEN2 &= ~0x04); } \
      else if (inum==INUM_DMA)   { DMAIE   = on; }  \
      else if (inum==INUM_T1)    { T1IE    = on; }  \
      else if (inum==INUM_T2)    { T2IE    = on; }  \
      else if (inum==INUM_T3)    { T3IE    = on; }  \
      else if (inum==INUM_T4)    { T4IE    = on; }  \
      else if (inum==INUM_P0INT) { P0IE    = on; }  \
      else if (inum==INUM_UTX1)  { (on) ? (IEN2 |= 0x08) : (IEN2 &= ~0x08); } \
      else if (inum==INUM_P1INT) { (on) ? (IEN2 |= 0x10) : (IEN2 &= ~0x10); } \
      else if (inum==INUM_RF)    { (on) ? (IEN2 |= 0x01) : (IEN2 &= ~0x01); } \
      else if (inum==INUM_WDT)   { (on) ? (IEN2 |= 0x20) : (IEN2 &= ~0x20); } \
   } while (0)



// Macro for setting interrupt group priority
// Example usage:
//   INT_PRIORITY(RFERR_RF_DMA, 3);
#define INT_PRIORITY(group, pri)                      \
   do {                                               \
      if (pri == 0) { IP0 &= ~group; IP1 &= ~group; } \
      if (pri == 1) { IP0 |=  group; IP1 &= ~group; } \
      if (pri == 2) { IP0 &= ~group; IP1 |=  group; } \
      if (pri == 3) { IP0 |=  group; IP1 |=  group; } \
   } while (0)
// Where pri is one of:
//   0 = Level 0 (lowest priority)
//   1 = Level 1
//   2 = Level 2
//   3 = Level 3 (highest priority)

// Where group is one of
#define RFERR_RF_DMA    0x01 // Group IP0
#define ADC_P2INT_T1    0x02 // Group IP1
#define URX0_UTX0_T2    0x04 // Group IP2
#define URX1_UTX1_T3    0x08 // Group IP3
#define ENC_P1INT_T4    0x10 // Group IP4
#define ST_WDT_P0INT    0x20 // Group IP5


// Macro used together with the INUM_* constants
// to read the interrupt flags.
// Example usage:
//   if (INT_GETFLAG(INUM_URX0))
//     ...
//   while (!INT_GETFLAG(INUM_URX0));

#define INT_GETFLAG(inum) (                       \
   (inum==INUM_RFERR)       ? RFERRIF           : \
   (inum==INUM_ADC)         ? ADCIF             : \
   (inum==INUM_URX0)        ? URX0IF            : \
   (inum==INUM_URX1)        ? URX1IF            : \
   (inum==INUM_ENC)         ? ENCIF_0           : \
   (inum==INUM_ST)          ? STIF              : \
   (inum==INUM_P2INT)       ? P2IF              : \
   (inum==INUM_UTX0)        ? UTX0IF            : \
   (inum==INUM_DMA)         ? DMAIF             : \
   (inum==INUM_T1)          ? T1IF              : \
   (inum==INUM_T2)          ? T2IF              : \
   (inum==INUM_T3)          ? T3IF              : \
   (inum==INUM_T4)          ? T4IF              : \
   (inum==INUM_P0INT)       ? P0IF              : \
   (inum==INUM_UTX1)        ? UTX1IF            : \
   (inum==INUM_P1INT)       ? P1IF              : \
   (inum==INUM_RF)          ? S1CON &= ~0x03    : \
   (inum==INUM_WDT)         ? WDTIF             : \
   0                                              \
)


// Macro used to set or clear certain interrupt flags.
// Example usage:
//   INT_SETFLAG(INUM_URX0, INT_SET;
//   INT_SETFLAG(INUM_T3, INT_CLR);
#define INT_SETFLAG(inum, f)                     \
   do {                                          \
      if      (inum==INUM_RFERR) { RFERRIF= f; } \
      else if (inum==INUM_ADC)   { ADCIF  = f; } \
      else if (inum==INUM_URX0)  { URX0IF = f; } \
      else if (inum==INUM_URX1)  { URX1IF = f; } \
      else if (inum==INUM_ENC)   { ENCIF_1 = ENCIF_0 = f; } \
      else if (inum==INUM_ST)    { STIF  = f;  } \
      else if (inum==INUM_P2INT) { P2IF  = f;  } \
      else if (inum==INUM_UTX0)  { UTX0IF= f;  } \
      else if (inum==INUM_DMA)   { DMAIF = f;  } \
      else if (inum==INUM_T1)    { T1IF  = f;  } \
      else if (inum==INUM_T2)    { T2IF  = f;  } \
      else if (inum==INUM_T3)    { T3IF  = f;  } \
      else if (inum==INUM_T4)    { T4IF  = f;  } \
      else if (inum==INUM_P0INT) { P0IF  = f;  } \
      else if (inum==INUM_UTX1)  { UTX1IF= f;  } \
      else if (inum==INUM_P1INT) { P1IF  = f;  } \
      else if (inum==INUM_RF)    { (f) ? (S1CON |= 0x03) : (S1CON &= ~0x03); } \
      else if (inum==INUM_WDT)   { WDTIF = f;  } \
   } while (0)





/******************************************************************************
**************************   DMA structures / macros  *************************
******************************************************************************/

// The macros and structs in this section simplify setup and usage of DMA.

//******************************************************************************

#define DMA_CHANNEL_0  0x01
#define DMA_CHANNEL_1  0x02
#define DMA_CHANNEL_2  0x04
#define DMA_CHANNEL_3  0x08
#define DMA_CHANNEL_4  0x10

#define VLEN_USE_LEN            0x00 // Use LEN for transfer count
#define VLEN_FIXED              0x00 // Use LEN for transfer count
#define VLEN_1_P_VALOFFIRST     0x01 // Transfer the first byte + the number of bytes indicated by the first byte
#define VLEN_VALOFFIRST         0x02 // Transfer the number of bytes indicated by the first byte (starting with the first byte)
#define VLEN_1_P_VALOFFIRST_P_1 0x03 // Transfer the first byte + the number of bytes indicated by the first byte + 1 more byte
#define VLEN_1_P_VALOFFIRST_P_2 0x04 // Transfer the first byte + the number of bytes indicated by the first byte + 2 more bytes

#define WORDSIZE_BYTE           0x00 // Transfer a byte at a time
#define WORDSIZE_WORD           0x01 // Transfer a 16-bit word at a time

#define TMODE_SINGLE            0x00 // Transfer a single byte/word after each DMA trigger
#define TMODE_BLOCK             0x01 // Transfer block of data (length len) after each DMA trigger
#define TMODE_SINGLE_REPEATED   0x02 // Transfer single byte/word (after len transfers, rearm DMA)
#define TMODE_BLOCK_REPEATED    0x03 // Transfer block of data (after len transfers, rearm DMA)

#define DMATRIG_NONE           0   // No trigger, setting DMAREQ.DMAREQx bit starts transfer
#define DMATRIG_PREV           1   // DMA channel is triggered by completion of previous channel
#define DMATRIG_T1_CH0         2   // Timer 1, compare, channel 0
#define DMATRIG_T1_CH1         3   // Timer 1, compare, channel 1
#define DMATRIG_T1_CH2         4   // Timer 1, compare, channel 2
#define DMATRIG_T2_COMP        5   // Timer 2, compare
#define DMATRIG_T2_OVFL        6   // Timer 2, overflow
#define DMATRIG_T3_CH0         7   // Timer 3, compare, channel 0
#define DMATRIG_T3_CH1         8   // Timer 3, compare, channel 1
#define DMATRIG_T4_CH0         9   // Timer 4, compare, channel 0
#define DMATRIG_T4_CH1        10   // Timer 4, compare, channel 1
#define DMATRIG_ST            11   // Sleep Timer compare
#define DMATRIG_IOC_0         12   // Port 0 I/O pin input transition
#define DMATRIG_IOC_1         13   // Port 1 I/O pin input transition
#define DMATRIG_URX0          14   // USART0 RX complete
#define DMATRIG_UTX0          15   // USART0 TX complete
#define DMATRIG_URX1          16   // USART1 RX complete
#define DMATRIG_UTX1          17   // USART1 TX complete
#define DMATRIG_FLASH         18   // Flash data write complete
#define DMATRIG_RADIO         19   // RF packet byte received/transmit
#define DMATRIG_ADC_CHALL     20   // ADC end of a conversion in a sequence, sample ready
#define DMATRIG_ADC_CH0       21   // ADC end of conversion channel 0 in sequence, sample ready
#define DMATRIG_ADC_CH1       22   // ADC end of conversion channel 1 in sequence, sample ready
#define DMATRIG_ADC_CH2       23   // ADC end of conversion channel 2 in sequence, sample ready
#define DMATRIG_ADC_CH3       24   // ADC end of conversion channel 3 in sequence, sample ready
#define DMATRIG_ADC_CH4       25   // ADC end of conversion channel 4 in sequence, sample ready
#define DMATRIG_ADC_CH5       26   // ADC end of conversion channel 5 in sequence, sample ready
#define DMATRIG_ADC_CH6       27   // ADC end of conversion channel 6 in sequence, sample ready
#define DMATRIG_ADC_CH7       28   // ADC end of conversion channel 7 in sequence, sample ready
#define DMATRIG_ENC_DW        29   // AES encryption processor requests download input data
#define DMATRIG_ENC_UP        30   // AES encryption processor requests upload output data

#define SRCINC_0         0x00 // Increment source pointer by 0 bytes/words after each transfer
#define SRCINC_1         0x01 // Increment source pointer by 1 bytes/words after each transfer
#define SRCINC_2         0x02 // Increment source pointer by 2 bytes/words after each transfer
#define SRCINC_M1        0x03 // Decrement source pointer by 1 bytes/words after each transfer

#define DESTINC_0        0x00 // Increment destination pointer by 0 bytes/words after each transfer
#define DESTINC_1        0x01 // Increment destination pointer by 1 bytes/words after each transfer
#define DESTINC_2        0x02 // Increment destination pointer by 2 bytes/words after each transfer
#define DESTINC_M1       0x03 // Decrement destination pointer by 1 bytes/words after each transfer

#define IRQMASK_DISABLE  0x00 // Disable interrupt generation
#define IRQMASK_ENABLE   0x01 // Enable interrupt generation upon DMA channel done

#define M8_USE_8_BITS    0x00 // Use all 8 bits for transfer count
#define M8_USE_7_BITS    0x01 // Use 7 LSB for transfer count

#define PRI_LOW          0x00 // Low, CPU has priority
#define PRI_GUARANTEED   0x01 // Guaranteed, DMA at least every second try
#define PRI_HIGH         0x02 // High, DMA has priority
#define PRI_ABSOLUTE     0x03 // Highest, DMA has priority. Reserved for DMA port access.


#pragma bitfields=reversed
typedef struct {
   BYTE SRCADDRH;
   BYTE SRCADDRL;
   BYTE DESTADDRH;
   BYTE DESTADDRL;
   BYTE VLEN      : 3;
   BYTE LENH      : 5;
   BYTE LENL      : 8;
   BYTE WORDSIZE  : 1;
   BYTE TMODE     : 2;
   BYTE TRIG      : 5;
   BYTE SRCINC    : 2;
   BYTE DESTINC   : 2;
   BYTE IRQMASK   : 1;
   BYTE M8        : 1;
   BYTE PRIORITY  : 2;
} DMA_DESC;
#pragma bitfields=default


#define DMA_SET_ADDR_DESC0(a)           \
   do{                                  \
      DMA0CFGH = (BYTE)( (WORD)a >> 8 );\
      DMA0CFGL = (BYTE)( (WORD)a );     \
   } while(0)

#define DMA_SET_ADDR_DESC1234(a)        \
   do{                                  \
      DMA1CFGH = (BYTE)( (WORD)a >> 8 );\
      DMA1CFGL = (BYTE)( (WORD)a );     \
   } while(0)

#define DMA_ARM_CHANNEL(ch)           \
   do{                                \
      DMAARM = ((0x01 << ch) & 0x1F); \
   } while(0)

#define DMA_ABORT_CHANNEL(ch)    DMAARM = (0x80 | ((0x01 << ch) & 0x1F))
#define DMA_MAN_TRIGGER(ch)      DMAREQ = (0x01 << ch)
#define DMA_START_CHANNEL(ch)    DMA_MAN_TRIGGER(ch)

// Macro for quickly setting the destination address of a DMA structure
#define SET_DMA_DEST(pDmaDesc, dest)                 \
   do{                                               \
      pDmaDesc->DESTADDRH = (BYTE) ((WORD)dest >> 8);\
      pDmaDesc->DESTADDRL = (BYTE)  (WORD)dest;      \
   } while (0);

// Macro for quickly setting the source address of a DMA structure
#define SET_DMA_SOURCE(pDmaDesc, source)              \
   do{                                                \
      pDmaDesc->SRCADDRH = (BYTE) ((WORD)source >> 8);\
      pDmaDesc->SRCADDRL = (BYTE)  (WORD)source;      \
   } while (0)

// Macro for quickly setting the number of bytes to be transferred by the DMA.
// max lenght is 0x1FFF
#define SET_DMA_LENGTH(pDmaDesc, length)          \
   do{                                            \
      pDmaDesc->LENH = (BYTE) ((WORD)length >> 8);\
      pDmaDesc->LENL = (BYTE)  (WORD)length;      \
   } while (0)

// Macro for getting the destination address of a DMA channel
#define GET_DMA_DEST(pDmaDesc)   \
   ( (WORD)pDmaDesc->DESTADDRL | ( (WORD)pDmaDesc->DESTADDRH << 8 ))

// Macro for getting the source address of a DMA channel
#define GET_DMA_SOURCE(pDmaDesc) \
   ( (WORD)pDmaDesc->SRCADDRL  | ( (WORD)pDmaDesc->SRCADDRH << 8 ))






/******************************************************************************
*******************         Common USART functions/macros   *******************
******************************************************************************/

// The macros in this section are available for both SPI and UART operation.

//*****************************************************************************

// Example usage:
//   USART0_FLUSH();
#define USART_FLUSH(num)              (U##num##UCR |= 0x80)
#define USART0_FLUSH()                USART_FLUSH(0)
#define USART1_FLUSH()                USART_FLUSH(1)

// Example usage:
//   if (USART0_BUSY())
//     ...
#define USART_BUSY(num)               (U##num##CSR & 0x01 == 0x01)
#define USART0_BUSY()                 USART_BUSY(0)
#define USART1_BUSY()                 USART_BUSY(1)

// Example usage:
//   while(!USART1_BYTE_RECEIVED())
//     ...
#define USART_BYTE_RECEIVED(num)      ((U##num##CSR & 0x04) == 0x04)
#define USART0_BYTE_RECEIVED()        USART_BYTE_RECEIVED(0)
#define USART1_BYTE_RECEIVED()        USART_BYTE_RECEIVED(1)

// Example usage:
//   if(USART1_BYTE_TRANSMITTED())
//     ...
#define USART_BYTE_TRANSMITTED(num)   ((U##num##CSR & 0x02) == 0x02)
#define USART0_BYTE_TRANSMITTED()     USART_BYTE_TRANSMITTED(0)
#define USART1_BYTE_TRANSMITTED()     USART_BYTE_TRANSMITTED(1)


/******************************************************************************
*******************  USART-UART specific functions/macros   *******************
******************************************************************************/
// The macros in this section simplify UART operation.
#define BAUD_E(baud, clkDivPow) (     \
    (baud==2400)   ?  6  +clkDivPow : \
    (baud==4800)   ?  7  +clkDivPow : \
    (baud==9600)   ?  8  +clkDivPow : \
    (baud==14400)  ?  8  +clkDivPow : \
    (baud==19200)  ?  9  +clkDivPow : \
    (baud==28800)  ?  9  +clkDivPow : \
    (baud==38400)  ?  10 +clkDivPow : \
    (baud==57600)  ?  10 +clkDivPow : \
    (baud==76800)  ?  11 +clkDivPow : \
    (baud==115200) ?  11 +clkDivPow : \
    (baud==153600) ?  12 +clkDivPow : \
    (baud==230400) ?  12 +clkDivPow : \
    (baud==307200) ?  13 +clkDivPow : \
    0  )


#define BAUD_M(baud) (      \
    (baud==2400)   ?  59  : \
    (baud==4800)   ?  59  : \
    (baud==9600)   ?  59  : \
    (baud==14400)  ?  216 : \
    (baud==19200)  ?  59  : \
    (baud==28800)  ?  216 : \
    (baud==38400)  ?  59  : \
    (baud==57600)  ?  216 : \
    (baud==76800)  ?  59  : \
    (baud==115200) ?  216 : \
    (baud==153600) ?  59  : \
    (baud==230400) ?  216 : \
    (baud==307200) ?  59  : \
  0)



//*****************************************************************************

// Macro for setting up a UART transfer channel. The macro sets the appropriate
// pins for peripheral operation, sets the baudrate, and the desired options of
// the selected uart. _uart_ indicates which uart to configure and must be
// either 0 or 1. _baudRate_ must be one of 2400, 4800, 9600, 14400, 19200,
// 28800, 38400, 57600, 76800, 115200, 153600, 230400 or 307200. Possible
// options are defined below.
//
// Example usage:
//
//      UART_SETUP(0,115200,HIGH_STOP);
//
// This configures uart 0 for contact with "hyperTerminal", setting:
//      Baudrate:           115200
//      Data bits:          8
//      Parity:             None
//      Stop bits:          1
//      Flow control:       None
//

#define UART_SETUP(uart, baudRate, options)      \
   do {                                          \
      if((uart) == 0){                           \
         if(PERCFG & 0x01){                      \
            P1SEL |= 0x30;                       \
         } else {                                \
            P0SEL |= 0x0C;                       \
         }                                       \
      }                                          \
      else {                                     \
         if(PERCFG & 0x02){                      \
            P1SEL |= 0xC0;                       \
         } else {                                \
            P0SEL |= 0x30;                       \
         }                                       \
      }                                          \
                                                 \
      U##uart##GCR = BAUD_E((baudRate),CLKSPD);  \
      U##uart##BAUD = BAUD_M(baudRate);          \
                                                 \
      U##uart##CSR |= 0x80;                      \
                                                 \
                                                 \
      U##uart##UCR |= ((options) | 0x80);        \
                                                 \
      if((options) & TRANSFER_MSB_FIRST){        \
         U##uart##GCR |= 0x20;                   \
      }                                          \
   } while(0)




// Options for UART_SETUP macro
#define FLOW_CONTROL_ENABLE         0x40
#define FLOW_CONTROL_DISABLE        0x00
#define EVEN_PARITY                 0x20
#define ODD_PARITY                  0x00
#define NINE_BIT_TRANSFER           0x10
#define EIGHT_BIT_TRANSFER          0x00
#define PARITY_ENABLE               0x08
#define PARITY_DISABLE              0x00
#define TWO_STOP_BITS               0x04
#define ONE_STOP_BITS               0x00
#define HIGH_STOP                   0x02
#define LOW_STOP                    0x00
#define HIGH_START                  0x01
#define TRANSFER_MSB_FIRST          0x80
#define TRANSFER_MSB_LAST           0x00
#define UART_ENABLE_RECEIVE         0x40


// Example usage:
//   if(UART0_PARERR())
//     ...
#define UART_PARERR(num)      ((U##num##CSR & 0x08) == 0x08)
#define UART0_PARERR()        UART_PARERR(0)
#define UART1_PARERR()        UART_PARERR(1)

// Example usage:
//   if(UART1_FRAMEERR())
//     ...
#define UART_FRAMEERR(num)    ((U ##num## CSR & 0x10) == 0x10)
#define UART0_FRAMEERR()      UART_FRAMEERR(0)
#define UART1_FRAMEERR()      UART_FRAMEERR(1)


// Example usage:
//   char ch = 'A';
//   UART1_SEND(ch);
//   ...
//   UART1_RECEIVE(ch);
#define UART_SEND(num, x)   U##num##DBUF = x
#define UART0_SEND(x)       UART_SEND(0, x)
#define UART1_SEND(x)       UART_SEND(1, x)

#define UART_RECEIVE(num, x)  x = U##num##DBUF
#define UART0_RECEIVE(x)      UART_RECEIVE(0, x)
#define UART1_RECEIVE(x)      UART_RECEIVE(1, x)



/******************************************************************************
*******************    USART-SPI specific functions/macros  *******************
******************************************************************************/
// The macros in this section simplify SPI operation.

//*****************************************************************************
// Macro for setting up an SPI connection. The macro configures the appropriate
// pins for peripheral operation, sets the baudrate if the chip is configured
// to be SPI master, and sets the desired clock polarity and phase. Whether to
// transfer MSB or LSB first is also determined. _spi_ indicates whether
// to use spi 0 or 1. _baudRate_ must be one of 2400, 4800, 9600, 14400, 19200,
// 28800, 38400, 57600, 76800, 115200, 153600, 230400 or 307200.
// Possible options are defined below.

#define SPI_SETUP(spi, baudRate, options)           \
   do {                                             \
      U##spi##UCR = 0x80;                           \
      U##spi##CSR = 0x00;                           \
                                                    \
      if(spi == 0){                                 \
         if(PERCFG & 0x01){                         \
            P1SEL |= 0x3C;                          \
         } else {                                   \
            P0SEL |= 0x3C;                          \
         }                                          \
      }                                             \
      else {                                        \
         if(PERCFG & 0x02){                         \
            P1SEL |= 0xF0;                          \
         } else {                                   \
            P0SEL |= 0x3C;                          \
         }                                          \
      }                                             \
                                                    \
      if(options & SPI_SLAVE){                      \
         U##spi##CSR = 0x20;                        \
      }                                             \
      else {                                        \
         U##spi##GCR = BAUD_E(baudRate, CLKSPD);    \
         U##spi##BAUD = BAUD_M(baudRate);           \
      }                                             \
      U##spi##GCR |= (options & 0xE0);              \
   } while(0)


// Options for the SPI_SETUP macro.
#define SPI_SLAVE              0x01
#define SPI_MASTER             0x00
#define SPI_CLOCK_POL_LO       0x00
#define SPI_CLOCK_POL_HI       0x80
#define SPI_CLOCK_PHA_0        0x00
#define SPI_CLOCK_PHA_1        0x40
#define SPI_TRANSFER_MSB_FIRST 0x20
#define SPI_TRANSFER_MSB_LAST  0x00



/******************************************************************************
*******************       FLASH programming functions       *******************
*******************************************************************************
 _halFlashWritePage(...)_ writes a whole flash page. Because code memory cannot
be read during flash write, the writing routines are copied to XDATA RAM. The
function is implemented in assembly code with file extensions .s51 rather than .c

The Direct Memory Access (DMA) may also be used for flash write.
******************************************************************************/

//Macro for erasing a given flash page
#define FLASH_ERASE_PAGE(page) \
   do{                         \
      FADDRH = (page) << 1;    \
      FADDRL = 0x00;           \
      FLASH_CONFIG(ERASE);     \
   }while (0)


// Macro for configuring flash access and setting flash access mode.
#define FLASH_CONFIG(options)     \
   do {                           \
      FWT  = ( 0x2A >> CLKSPD );  \
      FCTL = options;             \
   } while (0)

// _options_ may be the following:
#define READ_WHEN_NEED  0x00
#define CONTINOUS_READ  0x10
#define WRITE           0x02
#define ERASE           0x01
#define FLASH_BUSY      0x80

/******************************************************************************
* @fn  halFlashWritePage
*
* @brief
*       This function writes a byte field in XDATA RAM to a given flash
*       page. Normal program execution is run from flash. However during flash
*       write, flash memory is not available for reading. To circumvent this
*       problem the core operation of this procedure, namely the actual flash
*       write procedure, is copied to XDATA RAM and run from there. The flash
*       write procedure is copied to a 35 byte XDATA RAM buffer.
*       Prior to a write the page is erased.
*
*       This function disables interrupts when running, and re-enables interrupt
*       if interrupts were enabled at function entry.
*
* Parameters:
*
* @param  BYTE*	 pSrcAddr
*         Pointer to first byte in xdata space which is to be written to
*         flash. The number of bytes a flash page consists of starting from
*         this address will be written to the page _page_.
* @param  BYTE*	 pBuffer
*         Pointer to a buffer of 35 bytes in XDATA RAM to which the flash
*         write procedure
*         can be copied.
* @param  BYTE	    page
*         Indicates which of the flash pages the data is to be written to.
*
* @return void
*
******************************************************************************/
void halFlashWritePage(BYTE *pSrcAddr, BYTE *pBuffer, BYTE page);


/******************************************************************************
* @fn  halFlashErasePage
*
* @brief
*       This function erases a given flash page.
*
*       This function disables interrupts when running, and re-enables interrupt
*       if interrupts were enabled at function entry.
*
* Parameters:
*
* @param  BYTE*	 pBuffer
*         Pointer to a buffer of 10 bytes in XDATA RAM to which the flash
*         erase procedure can be copied.
* @param  BYTE	    page
*         Indicates which of the flash pages is to be erased.
*
* @return void
*
******************************************************************************/
void halFlashErasePage(BYTE* buffer, BYTE page);



/******************************************************************************
*******************      Power and clock management        ********************
*******************************************************************************

These macros are used to set power-mode, clock source and clock speed.

******************************************************************************/

// Macro for getting the clock division factor
#define CLKSPD  (CLKCONSTA & 0x07)

// Macro for getting the timer tick division factor.
#define TICKSPD ((CLKCONSTA & 0x38) >> 3)

// Macro for checking status of the crystal oscillator
#define XOSC_STABLE (SLEEPSTA & 0x40)

// Macro for checking status of the high frequency RC oscillator.
#define HIGH_FREQUENCY_RC_OSC_STABLE    (SLEEPSTA & 0x20)


// Macro for setting power mode
#define SET_POWER_MODE(mode)                   \
   do {                                        \
      if(mode == 0)        { SLEEPSTA &= ~0x03; } \
      else if (mode == 3)  { SLEEPSTA |= 0x03;  } \
      else { SLEEPSTA &= ~0x03; SLEEPSTA |= mode;  } \
      PCON |= 0x01;                            \
      asm("NOP");                              \
   }while (0)


// Where _mode_ is one of
#define POWER_MODE_0  0x00  // Clock oscillators on, voltage regulator on
#define POWER_MODE_1  0x01  // 32.768 KHz oscillator on, voltage regulator on
#define POWER_MODE_2  0x02  // 32.768 KHz oscillator on, voltage regulator off
#define POWER_MODE_3  0x03  // All clock oscillators off, voltage regulator off

// Macro for setting the 32 KHz clock source
#define SET_32KHZ_CLOCK_SOURCE(source) \
   do {                                \
      if( source ) {                   \
         CLKCONSTA |= 0x80;               \
      } else {                         \
         CLKCONSTA &= ~0x80;              \
      }                                \
   } while (0)

// Where _source_ is one of
#define CRYSTAL 0x00
#define RC      0x01

// Macro for setting the main clock oscillator source,
//turns off the clock source not used
//changing to XOSC will take approx 150 us
#define SET_MAIN_CLOCK_SOURCE(source) \
   do {                               \
      if(source) {                    \
        CLKCONCMD |= 0x40;               \
        while(!HIGH_FREQUENCY_RC_OSC_STABLE); \
        SLEEPCMD |= 0x04;                \
      }                               \
      else {                          \
        SLEEPCMD &= ~0x04;               \
        while(!XOSC_STABLE);          \
        asm("NOP");                   \
        CLKCONCMD &= ~0x47;              \
        SLEEPCMD |= 0x04;                \
      }                               \
   }while (0)


/******************************************************************************
*******************           Timer macros/functions        *******************
*******************************************************************************
General:
The timers/counters can be configured in a number of ways. The following
functions allow basic configuration of the timers as interrupt timers,
pulse width modulators (PWM) and capture timers. Other uses require manual
configuration of the timers/counters.

Generally 3 steps are nescessary to start a timer:

   TIMERx_INIT();
   BOOL halSetTimerxPeriod(period);
   TIMERx_RUN(TRUE);

where x is the timer number. Please see the function / macro in question for
details.

All timers can generate interrupts. The configuration of interrupts is not
included in the HAL.

******************************************************************************/


/******************************************************************************
* @fn  halSetTimer1Period
*
* @brief
*      This function sets up timer 1 to run with a given period. If _period_ is
*      set to 0, maximum period length will be used. The first time the timer
*      is used the macro TIMER1_INIT() should be run to clear all settings. The
*      timer is started and stopped with the macro TIMER1_RUN(TRUE / FALSE).
*
* Parameters:
*
* @param  DWORD	 period
*         The desired timer period in u-seconds.
*
* @return WORD
*         The timer value written to the register if the configuration was
*         successful and 0 if the period could not be achieved. This return
*         value can be used for determining pulse widths when the timer is
*         used in PWM mode.
*
******************************************************************************/
WORD halSetTimer1Period(DWORD period);


// Macro for initialising timer 1. Resets all involved registers and disables
// all interrupt masks.
#define TIMER1_INIT()   \
   do {                 \
      T1CTL  = 0x00;    \
      T1CCTL0 = 0x00;   \
      T1CCTL1 = 0x00;   \
      T1CCTL2 = 0x00;   \
      TIMIF &= ~0x40;   \
   } while (0)

// Macro for configuring a channel of timer 1 for PWM. Channel may be
// either 1 or 2.
#define TIMER1_PWM_CONFIG(channel)               \
   do {                                          \
      T1CCTL##channel## = 0x24;                  \
      if(PERCFG&0x40) {                          \
         if(channel == 0x01){                    \
            IO_FUNC_PORT_PIN(1,1,IO_FUNC_PERIPH);\
         }                                       \
         else {                                  \
            IO_FUNC_PORT_PIN(1,0,IO_FUNC_PERIPH);\
         }                                       \
      }                                          \
      else {                                     \
         if(channel == 0x01){                    \
            IO_FUNC_PORT_PIN(0,3,IO_FUNC_PERIPH);\
         }                                       \
         else {                                  \
            IO_FUNC_PORT_PIN(0,4,IO_FUNC_PERIPH);\
         }                                       \
      }                                          \
   } while(0)

// Macro for changing the pulse length of a timer in PWM mode. The value is
// not scaled and the user must verify that it is correct. _channel_ is the
// channel (1 or 2) configured for PWM operation, whereas _value_ is the
// 16 bit word giving the pulse length. This argument should be shorter than
// or equal to the value returned from the function halSetTimer1Period(...).
#define TIMER1_SET_PWM_PULSE_LENGTH(channel, value) \
   do {                                             \
      T1CC##channel##L = (BYTE)value;               \
      T1CC##channel##H = (BYTE)(value >> 8);        \
   } while(0)


// Macro for configuring a channel of timer 1 for capture.
#define TIMER1_CAPTURE_CHANNEL(channel, edge)      \
   do {                                            \
      T1CCTL ##channel = edge;                     \
      if(PERCFG&0x40) {                            \
         if(channel == 0x01){                      \
            IO_FUNC_PORT_PIN(1,1,IO_FUNC_PERIPH);  \
         }                                         \
         else {                                    \
            IO_FUNC_PORT_PIN(1,0,IO_FUNC_PERIPH);  \
         }                                         \
      }                                            \
      else {                                       \
         if(channel == 0x01){                      \
            IO_FUNC_PORT_PIN(0,3,IO_FUNC_PERIPH);  \
         }                                         \
         else {                                    \
            IO_FUNC_PORT_PIN(0,4,IO_FUNC_PERIPH);  \
         }                                         \
      }                                            \
   } while(0)

// Where _edge_ is either
#define POS_EDGE 0x01  // Capture when a positive edge on the channel input is detected
#define NEG_EDGE 0x02  // Capture when a negative edge on the channel input is detected
#define ANY_EDGE 0x03  // Capture when either a positive or a negative edge on the
                       // channel input is detected.

// Macro for enabling or disabling overflow interrupts of timer 1.
#define TIMER1_ENABLE_OVERFLOW_INT(val) \
   (TIMIF =  (val) ? TIMIF | 0x40 : TIMIF & ~0x40)


/******************************************************************************
* @fn  halSetTimer2Period
*
* @brief
*      This function sets the period and overflow counter value of the MAC timer
*      (timer 2). The timer can be set up with 320 u-second periods according to
*      IEEE 802.15.4 or as a normal counter with 1 m-second period by using the
*      option TIMER2_MAC_TIMER or TIMER2_NORMAL_TIMER respectively. The value of
*      _period_ gives the number of periods (320 u-seconds or 1 m-seconds) to
*      generate a compare event. The timer is set up to compensate for any clock
*      division. The timer is also set up to be synchronised with the 32.768 KHz
*      clock when entering or leaving power mode 0. When starting synchronously
*      from power mode 1 or 2, the timer value is updated by adding the time
*      passed since PM 0 was left. This time is kept by the 32.768 KHz clock.
*      This way the time is kept as if the chip had been in power mode 0 the
*      whole time. The timer must be started with the macro
*      TIMER2_RUN(TRUE) or MAC_TIMER_RUN(TRUE). The macro TIMER2_INIT() should be
*      run in advance to reset all register values.
*
* Parameters:
*
* @param  BYTE	 mode
*         Determines which time period Timer 2 is to use. The period of Timer 2
*         is either 320 u-seconds (TIMER2_MAC_TIMER) or 1 m-second
*         (TIMER2_NORMAL_TIMER).
* @param  DWORD	 period
*         This value indicates how many periods (320 u-second or 1 m-second) to
*         pass before an overflow compare event is generated.
*
* @return BOOL
          Returns 0 if period is too large, 1 otherwise.
*
******************************************************************************/
BOOL halSetTimer2Period(BYTE mode, DWORD period);

// _options_ may be of the following:
#define TIMER2_MAC_TIMER    0x01  // Counts 320 u-second periods
#define TIMER2_NORMAL_TIMER 0x02  // Uses the timer as a normal timer with 1 m-second period.

// Macro for initialising timer 2
#define TIMER2_INIT()  \
   do {                \
      T2THD = 0x00;    \
      T2TLD = 0x00;    \
      T2CMP = 0x00;    \
      T2OF0 = 0x00;    \
      T2OF1 = 0x00;    \
      T2OF2 = 0x00;    \
      T2CAPHPH = 0x00; \
      T2CAPLPL = 0x00; \
      T2PEROF0 = 0x00; \
      T2PEROF1 = 0x00; \
      T2PEROF2 = 0x00; \
      T2CNF = 0x06;    \
   } while (0)

#define TIMER2_ENABLE_OVERFLOW_COMP_INT(val) (T2PEROF2 =  (val) ? T2PEROF2 | 0x20 : T2PEROF2 & ~0x20)


/******************************************************************************
* @fn  halSetTimer34Period
*
* @brief
*      This function sets the period of timer 3 or 4 according to the value of
*      _timer_. The two timers are identical. Clock division is used to fit the
*      desired period within the timer range. If the period is too short or too
*      long the function returns 0. If the period is successfully set, the
*      function returns the BYTE value written to the timer register. This
*      value can be used to set the pulse length if the timer is used for PWM.
*      If _period_ is set to 0, maximum timeout value will be used.
*
* Parameters:
*
* @param  BYTE	 timer
*         Indicates which timer to configure. Must be either 3 or 4
*         (0x03 or 0x04).
* @param  DWORD	 period - Describe value.
*         The desired period in microseconds.
*
* @return BYTE
*         The value written to the TxCC0 register. The timer is incremented up
*         to this value before the timer is reset. This value may be used to
*         set the pulse length in PWM mode.
*
******************************************************************************/
BYTE halSetTimer34Period(BYTE timer, DWORD period);
// Where _timer_ must be either 3 or 4

// Macro for initialising timer 3 or 4
#define TIMER34_INIT(timer)   \
   do {                       \
      T##timer##CTL   = 0x06; \
      T##timer##CCTL0 = 0x00; \
      T##timer##CC0   = 0x00; \
      T##timer##CCTL1 = 0x00; \
      T##timer##CC1   = 0x00; \
   } while (0)

//Macro for enabling overflow interrupt
#define TIMER34_ENABLE_OVERFLOW_INT(timer,val) \
   (T##timer##CTL =  (val) ? T##timer##CTL | 0x08 : T##timer##CTL & ~0x08)



// Macro for configuring channel 1 of timer 3 or 4 for PWM mode.
#define TIMER34_PWM_CONFIG(timer)                 \
   do{                                            \
      T##timer##CCTL1 = 0x24;                     \
      if(timer == 3){                             \
         if(PERCFG & 0x20) {                      \
            IO_FUNC_PORT_PIN(1,7,IO_FUNC_PERIPH); \
         }                                        \
         else {                                   \
            IO_FUNC_PORT_PIN(1,4,IO_FUNC_PERIPH); \
         }                                        \
      }                                           \
      else {                                      \
         if(PERCFG & 0x10) {                      \
             IO_FUNC_PORT_PIN(2,3,IO_FUNC_PERIPH);\
         }                                        \
         else {                                   \
            IO_FUNC_PORT_PIN(1,1,IO_FUNC_PERIPH); \
         }                                        \
      }                                           \
   } while(0)

// Macro for setting pulse length of the timer in PWM mode
#define TIMER34_SET_PWM_PULSE_LENGTH(timer, value) \
   do {                                            \
      T##timer##CC1 = (BYTE)value;                 \
   } while (0)


// Macro for setting timer 3 or 4 as a capture timer
#define TIMER34_CAPTURE_TIMER(timer,edge)          \
   do{                                             \
      T##timer##CCTL1 = edge;                      \
      if(timer == 3){                              \
         if(PERCFG & 0x20) {                       \
            IO_FUNC_PORT_PIN(1,7,IO_FUNC_PERIPH);  \
         }                                         \
         else {                                    \
             IO_FUNC_PORT_PIN(1,4,IO_FUNC_PERIPH); \
         }                                         \
      }                                            \
      else {                                       \
         if(PERCFG & 0x10) {                       \
            IO_FUNC_PORT_PIN(2,3,IO_FUNC_PERIPH);  \
         }                                         \
        else {                                     \
           IO_FUNC_PORT_PIN(1,1,IO_FUNC_PERIPH);   \
        }                                          \
     }                                             \
  }while(0)


// Macros for turning timers on or off
#define TIMER1_RUN(value)      (T1CTL = (value) ? T1CTL|0x02 : T1CTL&~0x03)
#define TIMER2_RUN(value)      (T2CNF  = (value) ? T2CNF|0x01  : T2CNF&~0x01)
#define MAC_TIMER_RUN(value)   do{ TIMER2_RUN(value); }while(0)  //MAC-timer == timer 2
#define TIMER3_RUN(value)      (T3CTL = (value) ? T3CTL|0x10 : T3CTL&~0x10)
#define TIMER4_RUN(value)      (T4CTL = (value) ? T4CTL|0x10 : T4CTL&~0x10)

// Macro for enabling/ disabling interrupts from the channels of timer 1, 3 or 4.
#define TIMER_CHANNEL_INTERRUPT_ENABLE(timer, channel, value) \
   do{                                                        \
      if(value){                                              \
         T##timer##CCTL##channel## |= 0x40;                   \
      } else {                                                \
         T##timer##CCTL##channel## &= ~0x40;                  \
      }                                                       \
   } while(0)



/******************************************************************************
*******************          Watch Dog Timer (WDT)          *******************
*******************************************************************************

The WDT may be used to prevent the unit from being trapped in a system
stalemate, i.e. an endless waiting state. The WDT must be reset before it times
out. If a timeout occurs, the system is reset.

The WDT can also be configured as a normal timer which generates interrupt at
each timeout. This must be configured manually.
******************************************************************************/

// Macro for setting the WDT timeout interval.
#define WDT_SET_TIMEOUT_PERIOD(timeout) \
   do {  WDCTL &= ~0x03; WDCTL |= timeout; } while (0)

// Where _timeout_ is one of
#define SEC_1          0x00     // after 1 second
#define M_SEC_250      0x01     // after 250 ms
#define M_SEC_15       0x02     // after 15 ms
#define M_SEC_2        0x03     // after 2 ms

// Macro for resetting the WDT. If this is not done before the WDT times out,
// the system is reset.
#define WDT_RESET() do {           \
   WDCTL = (WDCTL & ~0xF0) | 0xA0; \
   WDCTL = (WDCTL & ~0xF0) | 0x50; \
} while (0)

// Macro for turning on the WDT
#define WDT_ENABLE()   WDCTL |= 0x08
#define WDT_DISABLE()  WDCTL &= ~0x08




/******************************************************************************
*******************             ADC macros/functions        *******************
*******************************************************************************

These functions/macros simplifies usage of the ADC.

******************************************************************************/
// Macro for setting up a single conversion. If ADCCON1.STSEL = 11, using this
// macro will also start the conversion.
#define ADC_SINGLE_CONVERSION(settings) \
   do{ ADCCON3 = settings; }while(0)

// Macro for setting up a single conversion
#define ADC_SEQUENCE_SETUP(settings) \
   do{ ADCCON2 = settings; }while(0)

// Where _settings_ are the following:
// Reference voltage:
#define ADC_REF_1_25_V      0x00     // Internal 1.25V reference
#define ADC_REF_P0_7        0x40     // External reference on AIN7 pin
#define ADC_REF_AVDD        0x80     // AVDD_SOC pin
#define ADC_REF_P0_6_P0_7   0xC0     // External reference on AIN6-AIN7 differential input

// Resolution (decimation rate):
#define ADC_8_BIT           0x00     //  64 decimation rate
#define ADC_10_BIT          0x10     // 128 decimation rate
#define ADC_12_BIT          0x20     // 256 decimation rate
#define ADC_14_BIT          0x30     // 512 decimation rate
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


//-----------------------------------------------------------------------------
// Macro for starting the ADC in continuous conversion mode
#define ADC_SAMPLE_CONTINUOUS() \
   do { ADCCON1 &= ~0x30; ADCCON1 |= 0x10; } while (0)

// Macro for stopping the ADC in continuous mode (and setting the ADC to be
// started manually by ADC_SAMPLE_SINGLE() )
#define ADC_STOP() \
  do { ADCCON1 |= 0x30; } while (0)

// Macro for initiating a single sample in single-conversion mode (ADCCON1.STSEL = 11).
#define ADC_SAMPLE_SINGLE() \
  do { ADC_STOP(); ADCCON1 |= 0x40;  } while (0)

// Macro for configuring the ADC to be started from T1 channel 0. (T1 ch 0 must be in compare mode!!)
#define ADC_TRIGGER_FROM_TIMER1()  do { ADC_STOP(); ADCCON1 &= ~0x10;  } while (0)

// Expression indicating whether a conversion is finished or not.
#define ADC_SAMPLE_READY()  (ADCCON1 & 0x80)

// Macro for setting/clearing a channel as input of the ADC
#define ADC_ENABLE_CHANNEL(ch)   ADCCFG |=  (0x01<<ch)
#define ADC_DISABLE_CHANNEL(ch)  ADCCFG &= ~(0x01<<ch)



/******************************************************************************
* @fn  halAdcSampleSingle
*
* @brief
*      This function makes the adc sample the given channel at the given
*      resolution with the given reference.
*
* Parameters:
*
* @param BYTE reference
*          The reference to compare the channel to be sampled.
*        BYTE resolution
*          The resolution to use during the sample (8, 10, 12 or 14 bit)
*        BYTE input
*          The channel to be sampled.
*
* @return INT16
*          The conversion result
*
******************************************************************************/
INT16 halAdcSampleSingle(BYTE reference, BYTE resolution, UINT8 input);



/******************************************************************************
* @fn  halGetAdcValue
*
* @brief
*      Returns the result of the last ADC conversion.
*
* Parameters:
*
* @param  void
*
* @return INT16
*         The ADC value
*
******************************************************************************/
INT16 halGetAdcValue(void);




/******************************************************************************
*******************    RF communication functions/macros    *******************
*******************************************************************************
// The functions in this section are designed to simplify usage of the radio.
// A function for setup, transmitting and receiption are included. In addition,
// macros for writing instructions to the Command Stobe Processor are included.

******************************************************************************/

/******************************************************************************
* @fn  halRfSend
*
* @brief
*      This function sends the given number of bytes using the radio. The radio
*      frequency must be set before sending. Can send a maximum of 125 bytes.
*      The function waits until the transfer is complete.
*
* Parameters:
*
* @param  BYTE*	 pData
*         Pointer to the start of the data to be transferred.
* @param  BYTE	 length
*         The number of bytes to be transferred.
*
* @return BYTE
*         Returns the number of transferred bytes.
*
******************************************************************************/
BYTE halRfSendPacket(BYTE* pData, BYTE length);



/******************************************************************************
* @fn  halRfReceivePacket
*
* @brief
*      This function receives a maximum of 128 bytes sent by another radio
*      transmitter. The function will wait for _timeOut_ ms before returning
*      without receiving any data.
*
* Parameters:
*
* @param  BYTE*	 pData
*         Pointer to the received packet is to be stored.
* @param  BYTE pRssi
*         Pointer to where to store the received signal strength indicator calculation.
* @param  BYTE pLqi
*         Pointer to where to store the link quality indicator.
* @param  BYTE	 timeOut
*         The number of ms the chip will wait for a packet to be received.
*
* @return BYTE
*         Returns the number of received bytes.
*
******************************************************************************/
BYTE halRfReceivePacket(BYTE* pData, BYTE*pRssi, BYTE* pLqi, BYTE timeOut);

/******************************************************************************
* @fn  halRfConfig
*
* @brief
*      This function configures the radio for simple send and receive operation.
*      Advanced IEEE 802.15.4 functionality such as Address Decoding, AutoAck
*      etc is not employed. CRC value is automatically calculated to enable
*      detection of packet corruption. The desired frequency is set. The
*      function returns TRUE if the configuration is successful.
*
* Parameters:
*
* @param  UINT32 frequency
*         The desired Radio Frequency in kHz.
*
* @return BOOL
*         Returns TRUE if the configuration is successful and FALSE otherwise.
*
******************************************************************************/
BOOL halRfConfig(UINT32 frequency);

/******************************************************************************
* @fn  halRfSetRadioFrequency
*
* @brief
*      This function sets the radio frequency of the radio. The requency must
*      be within the range of the radio.
*
* Parameters:
*
* @param  WORD	 frequency
*         The desired Radio Frequency in kHz.
*
* @return void
*
******************************************************************************/
void halRfSetRadioFrequency(UINT32 frequency);

#define STOP_RADIO()        ISRFOFF;

// RF interrupt flags
#define IRQ_RREG_ON         0x80
#define IRQ_TXDONE          0x40
#define IRQ_FIFOP           0x20
#define IRQ_SFD             0x10
#define IRQ_CCA             0x08
#define IRQ_CSP_WT          0x04
#define IRQ_CSP_STOP        0x02
#define IRQ_CSP_INT         0x01

// RF status flags
#define TX_ACTIVE_FLAG      0x10
#define FIFO_FLAG           0x08
#define FIFOP_FLAG          0x04
#define SFD_FLAG            0x02
#define CCA_FLAG            0x01

// Radio status states
#define TX_ACTIVE   (RFSTATUS & TX_ACTIVE_FLAG)
#define FIFO        (RFSTATUS & FIFO_FLAG)
#define FIFOP       (RFSTATUS & FIFOP_FLAG)
#define SFD         (RFSTATUS & SFD_FLAG)
#define CCA         (RFSTATUS & CCA_FLAG)

// Various radio settings
#define ADR_DECODE          0x08
#define AUTO_CRC            0x20
#define AUTO_TX2RX_OFF      0x08
#define RX2RX_TIME_OFF      0x04
#define ACCEPT_ACKPKT       0x01






//-----------------------------------------------------------------------------
// Command Strobe Processor (CSP) instructions
//-----------------------------------------------------------------------------
#define DECZ        do{RFST = 0xBF;                       }while(0)
#define DECY        do{RFST = 0xBE;                       }while(0)
#define INCY        do{RFST = 0xBD;                       }while(0)
#define INCMAXY(m)  do{RFST = (0xB8 | m);                 }while(0) // m < 8 !!
#define RANDXY      do{RFST = 0xBC;                       }while(0)
#define INT         do{RFST = 0xB9;                       }while(0)
#define WAITX       do{RFST = 0xBB;                       }while(0)
#define WAIT(w)     do{RFST = (0x80 | w);                 }while(0) // w < 64 !!
#define WEVENT      do{RFST = 0xB8;                       }while(0)
#define LABEL       do{RFST = 0xBA;                       }while(0)
#define RPT(n,c)    do{RFST = (0xA0 | (n << 3) | c);      }while(0) // n = TRUE/FALSE && (c < 8)
#define SKIP(s,n,c) do{RFST = ((s << 4) | (n << 3) | c);  }while(0) // && (s < 8)
#define STOP        do{RFST = 0xDF;                       }while(0)
#define SNOP        do{RFST = 0xC0;                       }while(0)
#define STXCALN     do{RFST = 0xC1;                       }while(0)
#define SRXON       do{RFST = 0xC2;                       }while(0)
#define STXON       do{RFST = 0xC3;                       }while(0)
#define STXONCCA    do{RFST = 0xC4;                       }while(0)
#define SRFOFF      do{RFST = 0xC5;                       }while(0)
#define SFLUSHRX    do{RFST = 0xC6;                       }while(0)
#define SFLUSHTX    do{RFST = 0xC7;                       }while(0)
#define SACK        do{RFST = 0xC8;                       }while(0)
#define SACKPEND    do{RFST = 0xC9;                       }while(0)
#define ISSTOP      do{RFST = 0xFF;                       }while(0)
#define ISSTART     do{RFST = 0xFE;                       }while(0)
#define ISTXCALN    do{RFST = 0xE1;                       }while(0)
#define ISRXON      do{RFST = 0xE2;                       }while(0)
#define ISTXON      do{RFST = 0xE3;                       }while(0)
#define ISTXONCCA   do{RFST = 0xE4;                       }while(0)
#define ISRFOFF     do{RFST = 0xE5;                       }while(0)
#define ISFLUSHRX   do{RFST = 0xE6;                       }while(0)
#define ISFLUSHTX   do{RFST = 0xE7;                       }while(0)
#define ISACK       do{RFST = 0xE8;                       }while(0)
#define ISACKPEND   do{RFST = 0xE9;                       }while(0)


// Conditions _c_ for the RPT and SKIP instructions of the CSP
#define CCA_TRUE            0x00;
#define RECEIVING           0x01;
#define MCU_BIT_IS_1        0x02;
#define COMMAND_BUF_EMPT    0x03;
#define REGX_IS_0           0x04;
#define REGY_IS_0           0x05;
#define REGZ_IS_0           0x06;
#define NO_OP               0x07;




/******************************************************************************
******************* Memory space mapping macros/functions  ********************
*******************************************************************************/

// Macros for enabling or disabling unified code space.
// Unified code space is generally used when executing programs from RAM.
#define ENABLE_UINIFIED_CODE_SPACE()  do { MEMCTR |= 0x40;  } while (0)
#define DISABLE_UINIFIED_CODE_SPACE()  do { MEMCTR &= ~0x40;  } while (0)


/******************************************************************************
*******************   AES encryption / decryption functions *******************
*******************************************************************************

Functions for performing a encryption or decryption using the Advanced
Encryption Standard. A unique 16 byte key must be loaded prior to the
encryption or decryption process.

This function performs a manual transfer of data to and from the AES module.

The Direct Memory Access (DMA) may also be used for data transfer to and from
the AES module.
******************************************************************************/


/******************************************************************************
* @fn  halAesLoadKeyOrInitVector
*
* @brief
*      This function Loads an AES key or an initialisation vector. The data
*      (key or vector) must be 16 bytes long (128 bit).
*
* Parameters:
*
* @param  BYTE*	 pData
*         Pointer to the start of the 16 bit key or the 16 bit initialisation
*         vector to be loaded.
* @param  BOOL key
*         Boolean value. Set to TRUE if a key is to be loaded and FALSE if an
*         initialisation vector is to be loaded.
*
* @return void
*
******************************************************************************/
void halAesLoadKeyOrInitVector(BYTE* pData, BOOL key);


/******************************************************************************
* @fn  halAesEncrDecr
*
* @brief
*      Encrypts or decrypts a given number of bytes and stores the result at a
*      given location.
*
* Parameters:
*
* @param  BYTE*	 pDataIn
*         Pointer to the start of the data to be decrypted or encrypted
* @param  UINT16	 length
*         The number of bytes to be encrypted/decrypted. Should be a multiplum
*         of 16 bytes.
* @param  BYTE*	 pDataOut.
*         Pointer to the location at which the converted data is to be stored.
* @param  BYTE*	 pInitVector
*         Initialisation vector to fill the AES module at startup. Must be
*         identical for encryption
*         and decryption.
* @param  BOOL	 decr
*         Indicates whether an encryption or decryption is to be performed.
*         0 indicates encryption whereas 1 indicates decryption.
*
* @return void
*
******************************************************************************/
void halAesEncrDecr(BYTE* pDataIn, UINT16 length, BYTE* pDataOut, BYTE* pInitVector, BOOL decr);


#define AES_BUSY    0x08
#define ENCRYPT     0x00
#define DECRYPT     0x01

// Macro for setting the mode of the AES operation
#define AES_SETMODE(mode) do { ENCCS &= ~0x70; ENCCS |= mode; } while (0)

// _mode_ is one of
#define CBC         0x00
#define CFB         0x10
#define OFB         0x20
#define CTR         0x30
#define ECB         0x40
#define CBC_MAC     0x50

// Macro for starting or stopping encryption or decryption
#define AES_SET_ENCR_DECR_KEY_IV(mode) \
   do {                                \
    ENCCS = (ENCCS & ~0x07) | mode     \
   } while(0)

// Where _mode_ is one of
#define AES_ENCRYPT     0x00;
#define AES_DECRYPT     0x02;
#define AES_LOAD_KEY    0x04;
#define AES_LOAD_IV     0x06;


// Macro for starting the AES module for either encryption, decryption,
// key or initialisation vector loading.
#define AES_START()     ENCCS |= 0x01


/******************************************************************************
*************         Random Generator macros / functions          ************
******************************************************************************/
//
// Example usage:
//
//    BYTE rnd;
//
//    //first initialise the random generator:
//    halInitRandomGenerator();
//
//
//    // Each time the random generator is read, the following sequence should
//    // be used (clock the random generator for each read):
//       CLOCK_RANDOM_GENERATOR();
//       rnd = GET_RANDOM_VALUE();
//
//

// Macro for enabling the random generator
#define ENABLE_RANDOM_GENERATOR()   do{ ADCCON1 &= ~0x0C; } while(0)

// Macro for clocking the random generator
#define CLOCK_RANDOM_GENERATOR()   do{ ADCCON1 |= 0x04; } while(0)

// Macro for getting a random byte
#define GET_RANDOM_BYTE(a)      \
   do{                           \
      CLOCK_RANDOM_GENERATOR();  \
      a = RNDH;                  \
   }while(0)


// Macro for getting a random word
#define GET_RANDOM_WORD(a)      \
   do{                           \
      CLOCK_RANDOM_GENERATOR();  \
      a = (((WORD)RNDH << 8) | RNDL);                  \
   }while(0)


/******************************************************************************
* @fn  halInitRandomGenerator
*
* @brief
*      This function generates a random sequence using the radio. The radio is
*      turned on and data is sampled from the receiver. This data is used to
*      seed the random generator. This seeding forms the basis for generating
*      new random bytes by clocking the random generator.
*
* Parameters:
*
* @param  void
*
* @return void
*
******************************************************************************/
void halInitRandomGenerator(void);


/******************************************************************************
*******************              Utility functions          *******************
******************************************************************************/

/******************************************************************************
* @fn  halWait
*
* @brief
*      This function waits approximately a given number of m-seconds
*      regardless of main clock speed.
*
* Parameters:
*
* @param  BYTE	 wait
*         The number of m-seconds to wait.
*
* @return void
*
******************************************************************************/
void halWait(BYTE wait);



/******************************************************************************
* @fn  getkey
*
* @brief
*       This function gets a char from UART0. It waits for URX0IF to be set before
*       reading the value and return. If URX0IF is not set, the function will
*       never return.
*
* Parameters:
*
* @param  void
*
* @return char
*         The received byte.
******************************************************************************/
char getkey(void);

/******************************************************************************
* @fn  putchar
*
* @brief
*      This writes a byte to the UART.
*
*      NOTE: This function is adapted to the printf() function of IAR (in
*            accordance with ANSI C). This is the reason for the apparently
*            contradictory castings/type conversions (int <-> char).
*
*            NOTE: A condition for using this function is that the
*                  UART0 TX flag is set before usage. If this requirement is
*                  not met, the function will never return.
*
* Parameters:
*
* @param  int	 i
*         The value to be written to the UART
* @return int
*
******************************************************************************/
int putchar(int i);
#endif //HAL_H

/*********************************************END OF FILE**********************/
