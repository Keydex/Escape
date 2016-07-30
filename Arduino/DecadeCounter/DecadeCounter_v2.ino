//Checks individual digits to calculate Threshold versus the first version
int sensorPin1 = A0;    // select the input pin for the potentiometer
int sensorPin2 = A1;    // select the input pin for the potentiometer
int sensorPin3 = A2;    // select the input pin for the potentiometer
int sensorPin4 = A3;    // select the input pin for the potentiometer
int sensorValue1 = 0;  // variable to store the value coming from the sensor
int sensorValue2 = 0;  // variable to store the value coming from the sensor
int sensorValue3 = 0;  // variable to store the value coming from the sensor
int sensorValue4 = 0;  // variable to store the value coming from the sensor
const int selectPin1 = 13;
const int selectPin2 = 12;
const int selectPin3 = 2;
const int selectPin4 = 3;
const int selectPin5 = 4;
const int selectPin6 = 5;
const int selectPin7 = 6;
const int selectPin8 = 7;
const int selectPin9 = 8;
const int selectPin10 = 9;
const int selectPin11 = 10;
const int selectPin12 = 11;

int readdelay = 50;  //Adjust Delay before Reading Analog Pins, (delay * 12) ms so 50 delay is .6 seconds
int retrieveAdjust = 450; //Adjusts the Analog Read Threshold
const int correctThreshold = 12;  //Change this to change difficulty/Threshold
const int NumberofDigits = 12;  //The number of digits in this combination 

int correct_counter = 0; //Checks how many digits are correct

const int digit_1 = 4;
const int digit_2 = 3;
const int digit_3 = 7;
const int digit_4 = 1;

const int digit_5 = 2;
const int digit_6 = 0;
const int digit_7 = 1;
const int digit_8 = 4;
const int digit_9 = 5;

const int digit_10 = 2;
const int digit_11 = 1;
const int digit_12 = 6;

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
  pinMode(selectPin1, OUTPUT);
  pinMode(selectPin2, OUTPUT);
  pinMode(selectPin3, OUTPUT);
  pinMode(selectPin4, OUTPUT);
  pinMode(selectPin5, OUTPUT);
  pinMode(selectPin6, OUTPUT);
  pinMode(selectPin7, OUTPUT);
  pinMode(selectPin8, OUTPUT);
  pinMode(selectPin9, OUTPUT);
  pinMode(selectPin10, OUTPUT);
  pinMode(selectPin11, OUTPUT);
  pinMode(selectPin12, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A5, OUTPUT);
  digitalWrite(A5, LOW);
}

void loop() {
  //Reinitialize Variables
  correct_counter = 0;
  //Digit 1
  ForceLow();
  digitalWrite(selectPin1,HIGH);
  delay(readdelay);
  if(RetrieveValue() == digit_4){
  	correct_counter++;
  }

  ForceLow();
  digitalWrite(selectPin2,HIGH);
  delay(readdelay);
  if(RetrieveValue() == digit_3){
  	correct_counter++;
  }

  ForceLow();
  digitalWrite(selectPin3,HIGH);
  delay(readdelay);
  if(RetrieveValue() == digit_2){
  	correct_counter++;
  }

  ForceLow();
  digitalWrite(selectPin4,HIGH);
  delay(readdelay);
  if(RetrieveValue() == digit_1){
  	correct_counter++;
  }

  //Combo 2
  ForceLow();
  digitalWrite(selectPin5,HIGH);
  delay(readdelay);
  if(RetrieveValue() == digit_9){
  	correct_counter++;
  }

  ForceLow();
  digitalWrite(selectPin6,HIGH);
  delay(readdelay);
  if(RetrieveValue() == digit_8){
  	correct_counter++;
  }

  ForceLow();
  digitalWrite(selectPin7,HIGH);
  delay(readdelay);
  if(RetrieveValue() == digit_7){
  	correct_counter++;
  }

  ForceLow();
  digitalWrite(selectPin8,HIGH);
  delay(readdelay);
  if(RetrieveValue() == digit_6){
  	correct_counter++;
  }

  ForceLow();
  digitalWrite(selectPin9,HIGH);
  delay(readdelay);
  if(RetrieveValue() == digit_5){
  	correct_counter++;
  }

  //Combo 3
  ForceLow();
  digitalWrite(selectPin10,HIGH);
  delay(readdelay);
  if(RetrieveValue() == digit_12){
  	correct_counter++;
  }

  ForceLow();
  digitalWrite(selectPin11,HIGH);
  delay(readdelay);
  if(RetrieveValue() == digit_11){
  	correct_counter++;
  }

  ForceLow();
  digitalWrite(selectPin12,HIGH);
  delay(readdelay);
  if(RetrieveValue() == digit_10){
  	correct_counter++;
  }

  if(correct_counter >= correctThreshold){//CorrectThreshold can be changed above, # of digits needed to be right
    if(correct_counter == NumberofDigits){
      Serial.print("Exact Number of Digits!\n");
    }
    else{
      Serial.print("Treshold Bypass!\n");
    }
    Serial.print("Solution is Correct!\n");
    digitalWrite(A5, HIGH);
  }
  else{
    Serial.print("Solution is Incorrect!\n");
  }
}

int ForceLow(){
  digitalWrite(selectPin1, LOW);
  digitalWrite(selectPin2, LOW);
  digitalWrite(selectPin3, LOW);
  digitalWrite(selectPin4, LOW);
  digitalWrite(selectPin5, LOW);
  digitalWrite(selectPin6, LOW);
  digitalWrite(selectPin7, LOW);
  digitalWrite(selectPin8, LOW);
  digitalWrite(selectPin9, LOW);
  digitalWrite(selectPin10, LOW);
  digitalWrite(selectPin11, LOW);
  digitalWrite(selectPin12, LOW);
 // Serial.print("Forced low!");
}

int RetrieveValue(){
  int tempdata = 0;
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);
  sensorValue4 = analogRead(sensorPin4);
  if(sensorValue1 > retrieveAdjust){
    tempdata = tempdata + 1;
  }
  if(sensorValue2 > retrieveAdjust){
    tempdata = tempdata + 2;
  }
  if(sensorValue3 > retrieveAdjust){
    tempdata = tempdata + 4;
  }
  if(sensorValue4 > retrieveAdjust){
    tempdata = tempdata + 8;
  }
//  Serial.println(tempdata);
  return tempdata;
}
