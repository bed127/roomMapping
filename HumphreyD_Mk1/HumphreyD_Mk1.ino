#include <HCSR04.h>

const int DIR1 = 2;
const int PWM1 = 3;
const int ENA1 = 4;
const int DIR2 = 5;
const int PWM2 = 6;
const int ENA2 = 7;

byte triggerPin = A5;
byte echoPin = A4;

const int LmotorHall1 = A6;
const int LmotorHall2 = A7;
const int RmotorHall1 = A2;
const int RmotorHall2 = A3;

const int trig = A5;
const int echo = A4;

float leftForward;
float rightForward;
float leftCount;
float rightCount;

long rightNow = 0;
unsigned long currentTime = 0;
int flag = 1;

char incomingData;
boolean newData = false;

void setup() {

  Serial.begin(115200);
  pinMode(ENA1, OUTPUT);
  digitalWrite(ENA1, LOW);
  pinMode(ENA2, OUTPUT);
  digitalWrite(ENA2, LOW);
  pinMode(PWM1, OUTPUT);
  analogWrite(PWM1, 0);
  pinMode(PWM2, OUTPUT);
  analogWrite(PWM2, 0);
  pinMode(DIR1, OUTPUT);
  digitalWrite(DIR1, LOW);
  pinMode(DIR2, OUTPUT);
  digitalWrite(DIR2, LOW);
}

void loop() {
  currentTime = millis();
 
  forwardMove();
}  

void forwardMove() {
  
} 
