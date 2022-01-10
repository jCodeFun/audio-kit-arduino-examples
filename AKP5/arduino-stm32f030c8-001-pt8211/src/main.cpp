/*
 * Sine wave generator.
 */

#include <Arduino.h>
#include "pt8211.h"
#include "math.h"

// PCM buffers
#define PCM_BUF_SIZE 128

volatile int pLeft[PCM_BUF_SIZE], pRight[PCM_BUF_SIZE];

void setup() {
  InitDac();
}

void loop() {
  int i, j;
  int wSize = PCM_BUF_SIZE;
  
  for(i=0; i<wSize; i++){
    pLeft[i] = sin(i*2*PI/wSize)*65535/2;
    pRight[i] = 65535*i/wSize;
  }
  
  while(1) {
    for(j=0; j<65535; j++){
      for(i=0; i<wSize; i++){
        //DacStereoOut(pLeft[i], pRight[i]); // 8 per sample
        DacMonoOut(pLeft[i]); // 5us per sample
      }
    }
  }
}