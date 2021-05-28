
MPU6050 mpu(Wire);

long timer2 = 0;
int16_t temp_raw;
float temp;


void setupMPU() {
  
  byte status = mpu.begin();
  
  Serial.print(F(" MPU6050 status: "));
  Serial.println(status);
  
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F(" Calculating offsets, do not move MPU6050"));
  delay(1000);
  
  mpu.calcOffsets(true,true); // gyro and accelero
  Serial.println(" Done!");
  
}

void loopMPU() {
  
  mpu.update();
  temp_raw = mpu.getTemp();
  temp = float(temp_raw + 521)/340 + temperature;

  if(millis() - timer2 > 1000){ // print data every second
    Serial.println();
    Serial.print(F(" Accel     X: "));Serial.print(mpu.getAccX());
    Serial.print("\tY: ");Serial.print(mpu.getAccY());
    Serial.print("\tZ: ");Serial.println(mpu.getAccZ());
  
    Serial.print(F(" Gyro      X: "));Serial.print(mpu.getGyroX());
    Serial.print("\tY: ");Serial.print(mpu.getGyroY());
    Serial.print("\tZ: ");Serial.println(mpu.getGyroZ());
    
    Serial.print(F(" Angle     X: "));Serial.print(mpu.getAngleX());
    Serial.print("\tY: ");Serial.print(mpu.getAngleY());
    Serial.print("\tZ: ");Serial.println(mpu.getAngleZ());
    Serial.print(F(" Accel Angle X: "));Serial.print(mpu.getAccAngleX());
    Serial.print("\tY: ");Serial.println(mpu.getAccAngleY());
    
    Serial.println();
    Serial.print(" Temperature: ");
    Serial.println(temp);

    timer2 = millis();
  }

}
