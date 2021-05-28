
void forwardMove() {
  
  digitalWrite(ENA1, HIGH);
  digitalWrite(ENA2, HIGH);
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, LOW);
  analogWrite(PWM1, 255);
  analogWrite(PWM2, 255);
  
} 

void turnLeft() {

    digitalWrite(ENA1, HIGH);
    digitalWrite(ENA2, HIGH);
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, HIGH);
    analogWrite(PWM1, 255);
    analogWrite(PWM2, 255);
    
}

void turnRight() {

  digitalWrite(ENA1, HIGH);
    digitalWrite(ENA2, HIGH);
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, LOW);
    analogWrite(PWM1, 255);
    analogWrite(PWM2, 255);

}

void moveBackwards() {

    digitalWrite(ENA1, HIGH);
    digitalWrite(ENA2, HIGH);
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, HIGH);
    analogWrite(PWM1, 255);
    analogWrite(PWM2, 255);

}

void moveStop() {
  
    digitalWrite(ENA1, LOW);
    digitalWrite(ENA2, LOW);
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
    analogWrite(PWM1, 0);
    analogWrite(PWM2, 0);
}
