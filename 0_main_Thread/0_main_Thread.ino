#include <HCSR04.h>
#include <Wire.h>
#include <SPI.h>
#include <BMx280I2C.h>
#define I2C_ADDRESS 0x76
#include <MPU6050_light.h>

BMx280I2C bmx280(I2C_ADDRESS);

const int DIR1 = 8;
const int PWM1 = 9;
const int ENA1 = 10;
const int DIR2 = 11;
const int PWM2 = 12;
const int ENA2 = 13;

bool hall1A_flag;
bool hall2A_flag;
bool hall1B_flag;
bool hall2B_flag;

const int hall1A = 2;
const int hall2A = 3;
const int hall1B = 18;
const int hall2B = 19;

const int LmotorHall1 = 44;
const int LmotorHall2 = 45;
const int RmotorHall1 = 42;
const int RmotorHall2 = 43;

float leftForward;
float rightForward;
float leftCount;
float rightCount;

int countNowLeft;
int countNowRight;

long rightNow = 0;
unsigned long currentTime = 0;
double* distances;

int moveTime = 10;
long temperature;

long timer = 0;

uint32_t _lastHeartbeatSendTime;

void setup() {

  Serial.begin(115200);
  delay(500);
  Wire.begin();
  delay(500);
  
  setupBME280();
  
  if (!bmx280.begin())
  {
    Serial.println(" BMP280 failure ");
    while (1);
  }
  delay(500);
  
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
  
  setupMPU();
  
  setupRadio();

  setupHC_SR04();
  
  pinMode(hall1A, INPUT);
  pinMode(hall2A, INPUT);
  pinMode(hall1B, INPUT);
  pinMode(hall2B, INPUT);
  attachInterrupt(digitalPinToInterrupt(hall1A), hall1A_tripped, FALLING);
  attachInterrupt(digitalPinToInterrupt(hall2A), hall2A_tripped, FALLING);
  attachInterrupt(digitalPinToInterrupt(hall1B), hall1B_tripped, FALLING);
  attachInterrupt(digitalPinToInterrupt(hall2B), hall2B_tripped, FALLING);
  
  
  delay(1500);

}

void loop() {
  currentTime = millis();
  
  tempSensor_function();
  
  loopMPU();

  loopHC_SR04();

  loopRadio();

  if(millis() - timer > 1000){
    Serial.println();
    Serial.print(" Motor A: ");
    Serial.print(rightCount);
    Serial.print(" Motor B: ");
    Serial.print(leftCount);
    Serial.print(" Temp: ");
    Serial.print(temperature);
    Serial.print(" Distance: ");
    Serial.println(distances[0]);
    timer = millis();
  }
  
    
}  

void hall1A_tripped() {
  
  hall1A_flag = 1;
  
  if (hall2A_flag && hall1A_flag == 1) {
    rightCount--;
    hall1A_flag = 0;
    hall2A_flag = 0;
  }
}

void hall2A_tripped() {

  hall2A_flag = 1;

  if (hall1A_flag && hall2A_flag == 1) {
    rightCount++;
    hall1A_flag = 0;
    hall2A_flag = 0;
  }
    
}

void hall1B_tripped() {

  hall1B_flag = 1;

  if(hall1B_flag && hall2B_flag == 1)  {
    leftCount--;
    hall1B_flag = 0;
    hall2B_flag = 0;
  }
  
}

void hall2B_tripped() {

  hall2B_flag = 1;

  if(hall2B_flag && hall1B_flag == 1)  {
    leftCount++;
    hall1B_flag = 0;
    hall2B_flag = 0;
  }
}
