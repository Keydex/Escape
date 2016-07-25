
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
//#include <TinyWireM.h> // Enable this line if using Adafruit Trinket, Gemma, etc.

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);
}

void loop() {
/*
  // print with print/println
  for (uint16_t counter = 0; counter < 9999; counter++) {
    matrix.println(counter);
    matrix.writeDisplay();
    delay(10);
  }
*/
  // method #2 - draw each digit
  uint16_t blinkcounter = 0;
  boolean drawDots = false;
  for (uint16_t hour = 59; hour > 0; hour --) {
    for(uint16_t minutes = 59; minutes > 0; minutes--){
      matrix.writeDigitNum(0, (hour / 10) % 10, drawDots);
      matrix.writeDigitNum(1, hour % 10, drawDots);
      matrix.drawColon(drawDots);
      matrix.writeDigitNum(3, (minutes / 10) % 10, drawDots);
      matrix.writeDigitNum(4, minutes % 10, drawDots);

      blinkcounter+=500;
      if (blinkcounter == 500) {
        drawDots = false;
      }else {
        drawDots = true;
        blinkcounter = 0;
      }
      matrix.writeDisplay();
      delay(1000);
    }
  }
}
