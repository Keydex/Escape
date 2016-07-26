
void setup (){

  Serial.begin(9600);
    pinMode(13, OUTPUT);
    pinMode(3, OUTPUT)
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

}

unsigned long timestamp = 0; // FOR TIMER
unsigned long timestamp2 = 0;
unsigned long elapsedTime;
int elapsedTime2;
int temp = 0;
unsigned long currtime = 0;

//Bool sequence for actions
bool buttonstart = false;
bool buttonend = false;
bool breaker = false;
bool powerglove = false;
bool usb = false;
bool buttonsequence = false;
bool PuzzleSolved = false;


void loop(){
  if(SystemResetTest() == False && currtime > 5000){     //If the system is not reset, stay Red
        Serial.print('\n');
        Serial.print("Too Slow!");
        SystemLockOut();
  }
  if (digitalRead(0) == LOW){          //System is Reset, Start Sequence with Button Press
    currtime = 0;
    delay(200);
    while(currtime < 5000){ //5000 = 50 seconds
        if(digitalRead(1) == LOW && powerglove == False && usb == False && buttonsequence == False){
          breaker = True;
          if(digitalRead(2) == LOW && breaker == True && usb == False && buttonsequence == False){
            powerglove = True;
            if(digitalRead(3) == LOW && breaker == True && usb == False && buttonsequence == False && powerglove == True){
              usb = True;
                if(digitalRead(4) == LOW && breaker == True && usb == True && powerglove == True){
                          digitalWrite(3, HIGH);
                          Serial.print('\n');
                          Serial.print("You Did it in ");
                          Serial.println(currtime/100);
                          Serial.print(" seconds!");
                }
                else{
                  PuzzleSolved = False;
                }
            }
            else{
              usb = False;
            }
          }
          else{
            powerglove = False;
          }
        }
        else{
          breaker = False;
        }
      if(currtime%100 == 1){  //Literally here to make timer look nicer
      Serial.print('\n');
      Serial.println(currtime/100);
      Serial.print(" seconds");
      }
      currtime++;
      delay(10);  //Delay 10 ms
   }
}
}
void SystemResetTest(){
  if(breaker == False && powerglove == False && usb == False && buttonsequence == False){
    return True;
  }
  else{
    return False;
  }
}

void SystemLockOut(){
    while(SystemResetTest() == False){
      //LED RED, STAY IN LOOP
      Serial.print("System is Currently Locked Out");
      delay(1000);
    }
}

