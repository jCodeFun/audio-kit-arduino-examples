/*
 pt8211.h
*/

#include <Arduino.h>

#ifndef PT8211_H
#define PT8211_H

#define BIT15 0x8000
#define BIT14 0x4000
#define BIT13 0x2000
#define BIT12 0x1000
#define BIT11 0x800
#define BIT10 0x400
#define BIT9  0x200
#define BIT8  0x100
#define BIT7  0x80
#define BIT6  0x40
#define BIT5  0x20
#define BIT4  0x10
#define BIT3  8
#define BIT2  4
#define BIT1  2
#define BIT0  1

//
// DAC pins
#define DAC_SCK  PA0
#define DAC_WS   PA1
#define DAC_DIN  PA2

// don't change it
#define POUT0  GPIOA->BRR
#define POUT1  GPIOA->BSRR
#define P_SCK  BIT0
#define P_WS   BIT1
#define P_DIN  BIT2

void DacStereoOut (uint16_t left, uint16_t right);
void DacMonoOut (uint16_t left);
void InitDac (void);

#endif // PT8211_H
