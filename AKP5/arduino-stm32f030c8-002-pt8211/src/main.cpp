/*
 * Sine wave generator.
 */

#include <Arduino.h>
#include "pt8211.h" // 16bit DAC pt8211
#include "sound.h" // sample 0.19 seconds

#define SAMPLING_44KHZ 1087 // 48MHz/44100
#define SAMPLING_22KHZ 2175 // 48MHz/22050
#define SAMPLING_11KHZ 4352 // 48MHz/11025

HardwareTimer timer(TIM1);
uint32_t pcmGo, pcmOut;
void hwTimer() {
    if(pcmGo) {
      pt8211MonoOut(data[pcmOut]);
      pcmOut++;
      if (pcmOut >= NUM_ELEMENTS) {
        pcmGo = 0; // auto stop
      }
    }
}

void initTimer (uint16_t ticks) {
    // Timer 11KHz/22KHz/44KHz
    timer.setPrescaleFactor(1); // 48MHz
    timer.setOverflow(ticks);
    timer.attachInterrupt(hwTimer);
    timer.refresh(); // Update timer data
    timer.resume(); // Enable timer
}

void setup() {
    pcmGo = 0;
    pt8211Init ();
    initTimer(SAMPLING_11KHZ);
}

void loop() {
    pcmOut = 0; // Point to start position.
    pcmGo = 1; // Set flag to start playing
    while(pcmGo){
      // Do something
      if (pcmOut >= NUM_ELEMENTS) {
        break;
      }
    }

    delay(3000);
}