#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

int sensorPin1 = A0;  //Sensor to check Pi's GPIO Output 2
int sensorPin2 = A1;  //3
int sensorPin3 = A2;  //4
int sensorPin4 = A3;  //17
int sensorValue1 = 0;  // variable to store the value coming from the sensor
int sensorValue2 = 0;  // variable to store the value coming from the sensor
int sensorValue3 = 0;  // variable to store the value coming from the sensor
int sensorValue4 = 0;  // variable to store the value coming from the sensor

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
  pinMode(sensorPin4, INPUT);
  matrix.begin(0x70);
}

void loop() {
  uint16_t blinkcounter = 0;
  boolean drawDots = false;

  
  while(1){
     blinkcounter+=500;
      if (blinkcounter == 500) {
        matrix.print(0xDEAD, HEX);
        matrix.writeDisplay();
        drawDots = false;
      }else {
        drawDots = true;
        blinkcounter = 0;
      }
      delay(1000);
  }
}

void CountDown(){
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
      if(analogRead(sensorPin1) > 500){
        
      }
      matrix.writeDisplay();
      delay(1012);
    }
  }
}

