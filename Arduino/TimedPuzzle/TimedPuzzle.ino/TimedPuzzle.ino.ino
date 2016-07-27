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

unsigned long timestamp = 0; // FOR TIMER
unsigned long timestamp2 = 0;
unsigned long elapsedTime;
int elapsedTime2;
int temp = 0;
unsigned long currtime = 0;

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
  
  if(SystemResetTest() == FALSE && currtime == 0){     //If the system is not reset, stay Red
        Serial.print('\n');
        Serial.print("Too Slow!");
        SystemLockOut();
  }
  
  if (digitalRead(8) == LOW){          //System is Reset, Start Sequence with Button Press
    Serial.print("It entered here!");
    currtime = 0;
    delay(200);
    while(currtime < 5000){ //5000 = 50 seconds
        if(digitalRead(2) == HIGH && powerglove == FALSE && usb == FALSE && buttonsequence == FALSE){
          breaker = TRUE;
          Serial.print("Step 1 is TRUE! \n");
          if(digitalRead(2) == HIGH && breaker == TRUE && usb == FALSE && buttonsequence == FALSE){
            powerglove = TRUE;
            Serial.print("Step 2 is TRUE! \n");
            if(digitalRead(3) == HIGH && breaker == TRUE && usb == FALSE && buttonsequence == FALSE && powerglove == TRUE){
              usb = TRUE;
              Serial.print("Step 3 is TRUE! \n");
                if(digitalRead(4) == HIGH && breaker == TRUE && usb == TRUE && powerglove == TRUE){
//                          digitalWrite(5, HIGH);
                          Serial.print('\n');
                          Serial.print("You Did it in ");
                          Serial.println(currtime/100);
                          Serial.print(" seconds!");
                }
                else{
                  PuzzleSolved = FALSE;
                  Serial.print("Step 4 is FALSE! \n");
                }
            }
            else{
              usb = FALSE;
              Serial.print("Step 3 is FALSE!");
            }
          }
          else{
            powerglove = FALSE;
            Serial.print("Step 2 is FALSE! \n");
          }
        }
        else{
          breaker = FALSE;
          Serial.print("Step 1 is FALSE! \n");
        }
      if(currtime%100 == 1){  //Literally here to make timer look nicer
      Serial.print('\n');
      Serial.println(currtime/100);
      Serial.print(" seconds");
      }
      currtime++;
      delay(10);  //Delay 10 ms
   }
   Serial.print('\n');
   Serial.print("We are looping");
}
}
int SystemResetTest(){
  delay(500);
  breaker = digitalRead(2);
  powerglove = digitalRead(3);
  usb = digitalRead(4);
  buttonsequence = digitalRead(5);
  if(breaker == FALSE && powerglove == FALSE && usb == FALSE && buttonsequence == FALSE){
    Serial.print("System test is True \n");
    Serial.println(breaker);
    Serial.println(powerglove);
    Serial.println(usb);
    Serial.println(buttonsequence);
    return TRUE;
  }
  else{
    Serial.print("System test is False \n");
    Serial.println(breaker);
    Serial.println(powerglove);
    Serial.println(usb);
    Serial.println(buttonsequence);
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

