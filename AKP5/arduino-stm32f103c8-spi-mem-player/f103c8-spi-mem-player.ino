/*
 * STM32F103 PROGMEM DAC player (SPI-DAC)
 */
#include <SPI.h>
#include "sample.h"

// stm32f103c8 SPI pins
// MISO PA6 -> no use
// MOSI PA7 -> DIN(DAC)
// SCK  PA5 -> BCK(DAC)
// WS   PA4 -> WS(DAC)
#define WS PA4

#define TIMER_PCM_11025 3264 // 36MHz/11025

HardwareTimer timer(TIM1);
uint32_t pcmGo, pcmOut;

void i2sInit(uint8_t pinWS){
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2); // 72MHz/2
  pinMode(pinWS, OUTPUT);
}

void i2sOut(uint16_t l, uint16_t r){
  digitalWrite(WS, LOW); // Right channel
  //SPI.transfer16(i);
  SPI.transfer(r>>8);
  SPI.transfer(r&0xff);
  digitalWrite(WS, HIGH); // Left channel
  //SPI.transfer16(j);
  SPI.transfer(l>>8);
  SPI.transfer(l&0xff);
}

void hwTimer() {
    if(pcmGo) {
      i2sOut(data[pcmOut], 0);
      pcmOut++;
      if (pcmOut >= NUM_ELEMENTS) {
        pcmGo = 0; // auto stop
      }
    }
}

void initTimer (uint16_t ticks) {
  // Timer 11KHz/22KHz/44KHz
  timer.setPrescaleFactor(2); // 72MHz/2
  timer.setOverflow(ticks);
  timer.attachInterrupt(hwTimer);
  timer.refresh(); // Update timer data
  timer.resume(); // Enable timer
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pcmGo = 0;
  i2sInit(WS);
  initTimer(TIMER_PCM_11025);
}

void loop() {
  pcmOut = 0; // Point to start position.
  pcmGo = 1; // Set flag to start playing
  while(pcmGo){
    // Do something
    if (pcmOut >= NUM_ELEMENTS) {
      break;
    }
    digitalWrite(LED_BUILTIN, LOW);
  }
  digitalWrite(LED_BUILTIN, HIGH);
  delay(3000);
}
