#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

int sensorPin1 = A0;  //Sensor to check Pi's GPIO Output 2
int sensorPin2 = A1;  //3
int sensorPin3 = A2;  //23
int sensorPin4 = A3;  
int sensorValue1 = 0;  // variable to store the value coming from the sensor
int sensorValue2 = 0;  // variable to store the value coming from the sensor
int sensorValue3 = 0;  // variable to store the value coming from the sensor
int sensorValue4 = 0;  // variable to store the value coming from the sensor

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin1, INPUT);//Start Time GPIO 25
  pinMode(sensorPin2, INPUT);//Reset Time GPIO 24
  pinMode(sensorPin3, INPUT);//Win Game GPIO 23
  pinMode(sensorPin4, INPUT);//Force Lose Game GPIO 7
  pinMode(6, OUTPUT);//Tells raspberry Game has ended GPIO 2
  matrix.begin(0x70);
}

void loop() {
  uint16_t blinkcounter = 0;
  boolean drawDots = false;
    Serial.println(sensorPin1);  
  if(analogRead(sensorPin1) > 500){

  	CountDown();
  }
  else{
	PrintTime(60, 00);
   }
}

void WinStop(int finalminute, int finalsecond){//Flashes current finish time
  while(1){
      if(analogRead(sensorPin2) > 500){//If raspberry requests reset, then return
        return;
      }
        blinkcounter+=500;
        if (blinkcounter == 500) {
    PrintTime(finalminute, finalsecond);
    drawDots = false;
        }else {
    PrintTime(0, 0)
    drawDots = true;
    blinkcounter = 0;
        }
        matrix.writeDisplay();
        delay(1012);
      }
  }
}

void LoseStop(){//Flashes Dead, because they lost
  delay(1000);
  digitalWrite(6, LOW);
  while(1){
      if(analogRead(sensorPin2) > 500){//If raspberry requests reset, then return
        return;
      }
       blinkcounter+=500;
        if (blinkcounter == 500) {
    matrix.print(0xDEAD, HEX);
    matrix.writeDisplay();
    drawDots = false;
        }else {
    drawDots = true;
    blinkcounter = 0;
        }
        delay(1012);
  }
}

void CountDown(){
	while(1){
	    for (uint16_t minutes = 59; minutes > 0; minutes --) {
		    for(uint16_t seconds = 59; seconds > 0; seconds--){
		    	if(analogRead(sensorPin3) > 500){
		    		WinStop(minutes, seconds);
		    		return;
		    	}
		    	else if(analogRead(sensorPin4) > 500){
		    		LoseStop();
		    		return;
		    	}
			PrintTime(minutes, seconds);
			delay(1012);
		  }
		digitalWrite(6, HIGH);
		LoseStop();
		return;
	}
}


void PrintTime(int minutes, int seconds){//Function to print current time to segments
        matrix.writeDigitNum(0, (minutes / 10) % 10, drawDots);
        matrix.writeDigitNum(1, minutes % 10, drawDots);
        matrix.drawColon(drawDots);
        matrix.writeDigitNum(3, (seconds / 10) % 10, drawDots);
        matrix.writeDigitNum(4, seconds % 10, drawDots);
}

