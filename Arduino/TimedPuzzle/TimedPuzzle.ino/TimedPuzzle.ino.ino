//Define True and False for Boolean manipulation.
#define FALSE 0
#define TRUE 1

//NeoPixel Initialize
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 13
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
  pinMode(PIN, OUTPUT);
  pinMode(10, OUTPUT);//Used to tell raspberry that the game is won
  digitalWrite(10, LOW);
  strip.begin();
  strip.show();
}

int timetosolve = 30; //Amount of time given to solve puzzle in seconds

//Variables to control Timer
int puzzletimer = timetosolve * 100; //Convert time to miliseconds
int currtime = -1;
int debugdelay = 200;

//Bool sequence for actions
int buttonstart = FALSE;      //Digital 2
int breaker = FALSE;          //Digital 3
int powerglove = FALSE;       //Digital 4
int usb = FALSE;              //Digital 5
int buttonseq1 = FALSE;  //Digital 6
int buttonseq2 = FALSE;  //Digital 7
int buttonseq3 = FALSE;  //Digital 8
int buttonend = FALSE;        //Digital 9
int PuzzleSolved = FALSE;     //Use if boolean needed for win
int sequenceBroken = FALSE;

//Varialbes to test button sequence
const int startTrigger = 2 + 1;   //Insert Button that Starts Sequence + 1

void loop(){

  if(SystemResetTest() == FALSE){     //If the system is not reset, stay Red
        if(currtime == puzzletimer){
          Serial.print('\n');
          Serial.print("Too Slow!");
        }
        SystemLockOut();
  }
  
  if (digitalRead(2) == LOW){          //System is Reset, Start Sequence with Button Press
    SetNeoPixel(blue);
    Serial.print("\n ShutDown Sequence Initiated \n");
    currtime = 0;                           //Reset Timer
    delay(200);
     while(currtime < puzzletimer){         //Checks to see if time runs out
        IncrementTime();                    //Increments time
        breaker = !digitalRead(3);          //Checks to make sure All switches are Off
        powerglove = !digitalRead(4);
        usb = !digitalRead(5);
        buttonseq1 = !digitalRead(6);
        buttonseq2 = !digitalRead(7);
        buttonseq3 = FALSE;
        sequenceBroken = FALSE;             //Resets sequence
        if(breaker == TRUE && powerglove == FALSE && usb == FALSE && buttonseq1 == FALSE && buttonseq2 == FALSE && buttonseq3 == FALSE){
        PuzzleNextStep(3,4);
        }
    }
  }
}
int SystemResetTest(){              //Function to test if system has been reset
  breaker = !digitalRead(3);
  powerglove = !digitalRead(4);
  usb = !digitalRead(5);
  buttonseq1 = !digitalRead(6);
  buttonseq2 = !digitalRead(7);
  buttonseq3 = FALSE;
  Serial.println(breaker);
  Serial.println(powerglove);
  Serial.println(usb);
  Serial.println(buttonseq1);
  Serial.println(buttonseq2);
  Serial.println(buttonseq3);
  if(breaker == FALSE && powerglove == FALSE && usb == FALSE && buttonseq1 == FALSE && buttonseq2 == FALSE && buttonseq3 == FALSE){
    Serial.print("Shutdown Sequence Ready To Begin \n");
    SetNeoPixel(yellow);
    return TRUE;      //If all true system has been reset successfully
  }
  else{
    return FALSE;     //System has not been reset
  }
}

void PuzzleNextStep(int previousTrigger, int currentTrigger){   //Creates a loop for the next Trigger
  if(currentTrigger > 3){
    Serial.print("\n Step ");
    Serial.println(currentTrigger - 3);
    Serial.print(" Solved! \n");
  }
  if(currentTrigger == 9){
    YouWin();
  }
  while(digitalRead(previousTrigger) == LOW && currtime < puzzletimer && sequenceBroken == FALSE){  //If previousTrigger is start, ignore previous check
    if(digitalRead(currentTrigger) == LOW){
      PuzzleNextStep(currentTrigger, currentTrigger + 1);
    }
    IncrementTime();
    if(CheckSwitchOrder(previousTrigger) == FALSE){
      return;
    }
  }
  return;
}

int CheckSwitchOrder(int checkStep){    //Checks if user broke puzzle up to the current step
  for(int i = startTrigger; i < checkStep; i++){
    if(!digitalRead(i) == FALSE){
      Serial.print("The sequence is broken \n");
      Serial.println(i);
      sequenceBroken = TRUE;
      return FALSE;               //The puzzle sequence is broken, force exit loop
    }
    else{
      Serial.print("The sequence is okay \n");
      Serial.println(checkStep);
      return TRUE;                //Puzzle sequence is good
    }
  }
}

void YouWin(){      //Well They Won
  digitalWrite(10, HIGH);
  SetNeoPixel(green);
  delay(1000);
  digitalWrite(10,LOW);
  while(TRUE){              //Stay in Loop until Arduino is force reset
      Serial.print("ShutDown Complete \n");
  }
}

void SystemLockOut(){                   //Function for when system is locked out
    while(SystemResetTest() == FALSE){
      SetNeoPixel(red);
      Serial.print("System is Currently Locked Out \n");
      delay(1000);
    }
}

void IncrementTime(){                   //Function to check time
      if(currtime%100 == 1){  //Literally here to make timer look nicer
      Serial.print('\n');
      Serial.println(currtime/100);
      Serial.print(" seconds");
      }
      currtime++;
      delay(10);  //Delay 10 ms
      return;
}

void SetNeoPixel(int color){          //Function to set NeoPixel Color
  delay(500);                         //Prevent Pixels from Constantly Updated
  if(color == red){
    for(int i = 0; i < NUMPIXELS; i++){
      strip.setPixelColor(i, strip.Color(255, 0, 0));
      strip.show();
    }
  }
  else if(color == blue){
    for(int i = 0; i < NUMPIXELS; i++){
      strip.setPixelColor(i, strip.Color(0, 0, 255));
      strip.show();
    }
  }
  else if(color == green){
    for(int i = 0; i < NUMPIXELS; i++){
      strip.setPixelColor(i, strip.Color(0, 255, 0));
      strip.show();
    }
  }
  else if(color == white){
    for(int i = 0; i < NUMPIXELS; i++){
      strip.setPixelColor(i, strip.Color(255,255,255));
      strip.show();
    }
  }
  else if(color == yellow){
    for(int i = 0; i < NUMPIXELS; i++){
      strip.setPixelColor(i, strip.Color(255, 150, 0));
      strip.show();
    }  
  }
  else{
    Serial.print("Invalid Color given to NeoPixels");
  }
  return;
}
