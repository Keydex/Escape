//Define True and False for Boolean manipulation.
#define FALSE 0
#define TRUE 1

//NeoPixel Initialize
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 9
#define NUMPIXELS 30
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Define Colors for NeoPixel
#define white 0
#define red 1
#define green 2
#define blue 3
#define yellow 4
void setup (){

  Serial.begin(9600);
  for(int i = 2; i < 9; i++){     //Initialize pin 2 to 8
      pinMode(i, INPUT_PULLUP);
  }
  pinMode(9, OUTPUT);
  strip.begin();
  strip.show();
}

int timetosolve = 50; //Amount of time given to solve puzzle in seconds


//Variables to control Timer
int puzzletimer = timetosolve * 100; //Convert time to miliseconds
int currtime = -1;
int debugdelay = 200;

//Bool sequence for actions
int buttonstart = FALSE;
int buttonend = FALSE;
int breaker = FALSE;
int powerglove = FALSE;
int usb = FALSE;
int buttonsequence1 = FALSE;
int buttonsequence2 = FALSE;
int buttonsequence3 = FALSE;
int PuzzleSolved = FALSE;

void loop(){
  //Serial.print("Access Loop!\n");
      for(int i = 0; i < NUMPIXELS; i++){
      strip.setPixelColor(i, 255, 255, 255);
      strip.show();
    }

  if(SystemResetTest() == FALSE){     //If the system is not reset, stay Red
        if(currtime == puzzletimer){
          Serial.print('\n');
          Serial.print("Too Slow!");
        }
        SystemLockOut();
  }
  
  if (digitalRead(8) == LOW){          //System is Reset, Start Sequence with Button Press
    Serial.print("\n ShutDown Sequence Initiated \n");
    currtime = 0;                           //Reset Timer
    delay(200);
    while(currtime < puzzletimer){ //5000 = 50 seconds
      SetNeoPixel(white);
        IncrementTime();                    //Increments time
          breaker = !digitalRead(2);        //Checks to make sure All switches are Off
          powerglove = !digitalRead(3);
          usb = !digitalRead(4);
          buttonsequence1 = !digitalRead(5);
          buttonsequence2 = !digitalRead(6);
          buttonsequence3 = !digitalRead(7);
        if(digitalRead(2) == LOW && powerglove == FALSE && usb == FALSE && buttonsequence1 == FALSE && buttonsequence2 == FALSE && buttonsequence3 == FALSE){
          Serial.print("\n Step 1 Solved! \n");
            while(digitalRead(2) == LOW && currtime < puzzletimer){
              if(digitalRead(3) == LOW){
                Serial.print("\n Step 2 Solved!");
                while(digitalRead(3) == LOW && currtime < puzzletimer){
                  if(digitalRead(4) == LOW){
                    Serial.print("\n Step 3 Solved!");
                    while(digitalRead(4) == LOW && currtime < puzzletimer){
                      if(digitalRead(5) == LOW){
                        SetNeoPixel(green);
                        Serial.print("ShutDown Complete \n");
                      }
                      else{
                        IncrementTime();    //Used to make sure time is still checked while in loop
                      }
                    }
                  }
                IncrementTime();
                }
              }
            IncrementTime();
            }
          }
   }
}
}
int SystemResetTest(){
  breaker = !digitalRead(2);
  powerglove = !digitalRead(3);
  usb = !digitalRead(4);
  buttonsequence1 = !digitalRead(5);
  if(breaker == FALSE && powerglove == FALSE && usb == FALSE && buttonsequence1 == FALSE){
    Serial.print("Shutdown Sequence Ready To Begin \n");
    SetNeoPixel(yellow);
/*    Serial.println(breaker);
    Serial.println(powerglove);
    Serial.println(usb);
    Serial.println(buttonsequence);
    */
    return TRUE;
  }
  else{
    Serial.print("System has not been Reset! \n");
    /*
    Serial.println(breaker);
    Serial.println(powerglove);
    Serial.println(usb);
    Serial.println(buttonsequence);
    */
    return FALSE;
  }
}

void SystemLockOut(){
    while(SystemResetTest() == FALSE){
      SetNeoPixel(red);
      Serial.print("System is Currently Locked Out \n");
      delay(1000);
    }
}

void IncrementTime(){
      if(currtime%100 == 1){  //Literally here to make timer look nicer
      Serial.print('\n');
      Serial.println(currtime/100);
      Serial.print(" seconds");
      }
      currtime++;
      delay(10);  //Delay 10 ms
      return;
}

void SetNeoPixel(int color){
  if(color == red){
    for(int i = 0; i < NUMPIXELS; i++){
      strip.setPixelColor(i, 255, 0, 0);
      strip.show();
    }
  }
  else if(color == blue){
    for(int i = 0; i < NUMPIXELS; i++){
      strip.setPixelColor(i, 0, 0, 255);
      strip.show();
    }
  }
  else if(color == green){
    for(int i = 0; i < NUMPIXELS; i++){
      strip.setPixelColor(i, 0, 255, 0);
      strip.show();
    }
  }
  else if(color == white){
    for(int i = 0; i < NUMPIXELS; i++){
      strip.setPixelColor(i, 255, 255, 255);
      strip.show();
    }
  }
  else if(color == yellow){
    for(int i = 0; i < NUMPIXELS; i++){
      strip.setPixelColor(i, 255, 255, 0);
      strip.show();
    }  
  }
  else{
    Serial.print("Invalid Color given to NeoPixels");
  }
  return;
}
