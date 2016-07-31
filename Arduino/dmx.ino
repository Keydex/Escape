#include <DmxMaster.h>

void setup() {
  Serial.begin(9600);
  DmxMaster.usePin(3);
  DmxMaster.maxChannel(4);
  pinMode(A0, INPUT);
  pinMode(A3 INPUT);
}

void loop() {
  int brightness;
  Serial.print("Hello");
  Serial.println(analogRead(A0));
  Serial.println(analogRead(A1));
  if(analogRead(A0) > 500){
    while(analogRead(A3) < 500){
        Serial.println(analogRead(A3));
        for (brightness = 0; brightness <= 255; brightness++) {
        DmxMaster.write(1, brightness);
        DmxMaster.write(2, 255);
        DmxMaster.write(4, 0);
        DmxMaster.write(3, 255);
        delay(5);
      }
    }  
  }
  else{
        DmxMaster.write(1, 0);
        DmxMaster.write(2, 0);
        DmxMaster.write(4, 0);
        DmxMaster.write(3, 0);
  }
}
