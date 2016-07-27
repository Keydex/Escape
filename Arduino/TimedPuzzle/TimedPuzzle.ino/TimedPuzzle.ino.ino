//typedef uint8_t boolean; // Super inefficient but it works
#define FALSE 0
#define TRUE 1
void setup (){

  Serial.begin(9600);
  pinMode(13, OUTPUT);
//    pinMode(3, OUTPUT)
  pinMode(8, INPUT_PULLUP);
//  pinMode(1, INPUT_PULLUP);
//  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
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
int buttonsequence = FALSE;
int PuzzleSolved = FALSE;

void loop(){
  //Serial.print("Access Loop!\n");

  if(SystemResetTest() == FALSE){     //If the system is not reset, stay Red
        if(currtime == puzzletimer){
          Serial.print('\n');
          Serial.print("Too Slow!");
        }
        SystemLockOut();
  }
  
  if (digitalRead(8) == LOW){          //System is Reset, Start Sequence with Button Press
    Serial.print("\n ShutDown Sequence Initiated \n");
    currtime = 0;
    delay(200);
    while(currtime < puzzletimer){ //5000 = 50 seconds
        IncrementTime();
          breaker = !digitalRead(2);
          powerglove = !digitalRead(3);
          usb = !digitalRead(4);
          buttonsequence = !digitalRead(5);
        if(digitalRead(2) == LOW && powerglove == FALSE && usb == FALSE && buttonsequence == FALSE){
          Serial.print("\n Step 1 Solved! \n");
            while(digitalRead(2) == LOW && currtime < puzzletimer){
              if(digitalRead(3) == LOW){
                Serial.print("\n Step 2 Solved!");
                while(digitalRead(3) == LOW && currtime < puzzletimer){
                  if(digitalRead(4) == LOW){
                    Serial.print("\n Step 3 Solved!");
                    while(digitalRead(4) == LOW && currtime < puzzletimer){
                      if(digitalRead(5) == LOW){
                        Serial.print("ShutDown Complete \n");
                      }
                      else{
                        IncrementTime();
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
  delay(500);
  breaker = !digitalRead(2);
  powerglove = !digitalRead(3);
  usb = !digitalRead(4);
  buttonsequence = !digitalRead(5);
  if(breaker == FALSE && powerglove == FALSE && usb == FALSE && buttonsequence == FALSE){
    Serial.print("Shutdown Sequence Ready To Begin \n");
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
      //LED RED, STAY IN LOOP
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
