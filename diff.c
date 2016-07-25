
int sensorPin1 = A0;    // select the input pin for the potentiometer
int sensorPin2 = A1;    // select the input pin for the potentiometer
int sensorPin3 = A2;    // select the input pin for the potentiometer
int sensorPin4 = A3;    // select the input pin for the potentiometer
int sensorValue1 = 0;  // variable to store the value coming from the sensor
int sensorValue2 = 0;  // variable to store the value coming from the sensor
int sensorValue3 = 0;  // variable to store the value coming from the sensor
int sensorValue4 = 0;  // variable to store the value coming from the sensor
const int selectPin1 = 0;
const int selectPin2 = 1;
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

int digitMultiplier = 1;
int readdelay = 250;
int combo1_curr = 0;
int combo2_curr = 0;
int combo3_curr = 0;

int combo1_soln = 4371;
int combo2_soln = 20145;
int combo3_soln = 216;

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
}

void loop() {
  //Reinitialize Variables
  combo1_curr = 0;
  combo2_curr = 0;
  combo3_curr = 0;

  //Combo 1
  digitMultiplier = 1;
  ForceLow();
  digitalWrite(selectPin1,HIGH);
  delay(readdelay);
  combo1_curr = (RetrieveValue(450) * digitMultiplier);

  digitMultiplier = 10;
  ForceLow();
  digitalWrite(selectPin2,HIGH);
  delay(readdelay);
  combo1_curr = (RetrieveValue(450) * digitMultiplier);

  digitMultiplier = 100;
  ForceLow();
  digitalWrite(selectPin3,HIGH);
  delay(readdelay);
  combo1_curr = (RetrieveValue(450) * digitMultiplier);

  digitMultiplier = 1000;
  ForceLow();
  digitalWrite(selectPin4,HIGH);
  delay(readdelay);
  combo1_curr = (RetrieveValue(450) * digitMultiplier);

  //Combo 2
  digitMultiplier = 1;
  ForceLow();
  digitalWrite(selectPin5,HIGH);
  delay(readdelay);
  combo2_curr = (RetrieveValue(450) * digitMultiplier);

  digitMultiplier = 10;
  ForceLow();
  digitalWrite(selectPin6,HIGH);
  delay(readdelay);
  combo2_curr = (RetrieveValue(450) * digitMultiplier);

  digitMultiplier = 100;
  ForceLow();
  digitalWrite(selectPin7,HIGH);
  delay(readdelay);
  combo2_curr = (RetrieveValue(450) * digitMultiplier);

  digitMultiplier = 1000;
  ForceLow();
  digitalWrite(selectPin8,HIGH);
  delay(readdelay);
  combo2_curr = (RetrieveValue(450) * digitMultiplier);

  digitMultiplier = 10000;
  ForceLow();
  digitalWrite(selectPin9,HIGH);
  delay(readdelay);
  combo2_curr = (RetrieveValue(450) * digitMultiplier);

  //Combo 3
  digitMultiplier = 1;
  ForceLow();
  digitalWrite(selectPin10,HIGH);
  delay(readdelay);
  combo3_curr = (RetrieveValue(450) * digitMultiplier);

  digitMultiplier = 10;
  ForceLow();
  digitalWrite(selectPin11,HIGH);
  delay(readdelay);
  combo3_curr = (RetrieveValue(450) * digitMultiplier);

  digitMultiplier = 100;
  ForceLow();
  digitalWrite(selectPin12,HIGH);
  delay(readdelay);
  combo3_curr = (RetrieveValue(450) * digitMultiplier);

  if(combo3_curr == cobo3_soln && combo2_curr == cobo2_soln && combo1_curr == combo1_soln){
    Serial.print("Solution is Correct!");
  }
  else{
    Serial.print("Solution is Incorrect!");
    Serial.println(combo1_curr);
    Serial.println(combo2_curr);
    Serial.println(combo3_curr);
  }
}

int ForceLow(){
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

int RetrieveValue(int sensoradjust){
  int tempdata = 0;
  sensorValue1 = analogRead(A0);
  sensorValue2 = analogRead(A1);
  sensorValue3 = analogRead(A2);
  sensorValue4 = analogRead(A3);
  if(sensorValue1 > sensoradjust){
    tempdata = tempdata + 1;
  }
  if(sensorValue2 > sensoradjust){
    tempdata = tempdata + 2;
  }
  if(sensorValue3 > sensoradjust){
    tempdata = tempdata + 4;
  }
  if(sensorValue4 > sensoradjust){
    tempdata = tempdata + 8;
  }
  return tempdata;
}
