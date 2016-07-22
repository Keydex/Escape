/*
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13.
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead().

 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground

 * Note: because most Arduinos have a built-in LED attached
 to pin 13 on the board, the LED is optional.


 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/AnalogInput

 */

int sensorPin1 = A0;    // select the input pin for the potentiometer
int sensorPin2 = A1;    // select the input pin for the potentiometer
int sensorPin3 = A2;    // select the input pin for the potentiometer
int sensorPin4 = A3;    // select the input pin for the potentiometer
int sensorValue1 = 0;  // variable to store the value coming from the sensor
int sensorValue2 = 0;  // variable to store the value coming from the sensor
int sensorValue3 = 0;  // variable to store the value coming from the sensor
int sensorValue4 = 0;  // variable to store the value coming from the sensor
const int selectPin1 = 7;
const int selectPin2 = 6;
const int selectPin3 = 5;
const int selectPin4 = 4;
int tempval = 0;
int digitMultiplier = 1;
int finalval = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
  pinMode(selectPin1, OUTPUT);
  pinMode(selectPin2, OUTPUT);
  pinMode(selectPin3, OUTPUT);
  pinMode(selectPin4, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}

void loop() {
  // read the value from the sensor:
  tempval = 0;
  finalval = 0;
  digitMultiplier = 1;
  digitalWrite(selectPin1, HIGH);
  digitalWrite(selectPin2, LOW);
  digitalWrite(selectPin3, LOW);
  digitalWrite(selectPin4, LOW);
  delay(500);
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);
  sensorValue4 = analogRead(sensorPin4);
      if(sensorValue1 > 700){
        tempval = tempval + 1;
      }
      if(sensorValue2 > 700){
        tempval = tempval + 2;
      }
      if(sensorValue3 > 700){
        tempval = tempval + 4;
      }
      if(sensorValue4 > 700){
        tempval = tempval + 8;
      }
        finalval = (tempval * digitMultiplier);

  tempval = 0;
  digitMultiplier = 10;
  digitalWrite(selectPin1, LOW);
  digitalWrite(selectPin2, HIGH);
  digitalWrite(selectPin3, LOW);
  digitalWrite(selectPin4, LOW);
  delay(500);
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);
  sensorValue4 = analogRead(sensorPin4);
      if(sensorValue1 > 700){
        tempval = tempval + 1;
      }
      if(sensorValue2 > 700){
        tempval = tempval + 2;
      }
      if(sensorValue3 > 700){
        tempval = tempval + 4;
      }
      if(sensorValue4 > 700){
        tempval = tempval + 8;
      }
        finalval = finalval + (tempval * digitMultiplier);


  tempval = 0;
  digitMultiplier = 100;
  digitalWrite(selectPin1, LOW);
  digitalWrite(selectPin2, LOW);
  digitalWrite(selectPin3, HIGH);
  digitalWrite(selectPin4, LOW);
  delay(500);
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);
  sensorValue4 = analogRead(sensorPin4);
      if(sensorValue1 > 700){
        tempval = tempval + 1;
      }
      if(sensorValue2 > 700){
        tempval = tempval + 2;
      }
      if(sensorValue3 > 700){
        tempval = tempval + 4;
      }
      if(sensorValue4 > 700){
        tempval = tempval + 8;
      }
        finalval = finalval + (tempval * digitMultiplier);

  tempval = 0;
  digitMultiplier = 1000;
  digitalWrite(selectPin1, LOW);
  digitalWrite(selectPin2, LOW);
  digitalWrite(selectPin3, LOW);
  digitalWrite(selectPin4, HIGH);
  delay(500);
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);
  sensorValue4 = analogRead(sensorPin4);
      if(sensorValue1 > 700){
        tempval = tempval + 1;
      }
      if(sensorValue2 > 700){
        tempval = tempval + 2;
      }
      if(sensorValue3 > 700){
        tempval = tempval + 4;
      }
      if(sensorValue4 > 700){
        tempval = tempval + 8;
      }
        finalval = finalval + (tempval * digitMultiplier);
  Serial.print("The Number is: ");
  Serial.println(finalval);
  delay(1000);
}
