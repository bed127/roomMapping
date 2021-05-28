byte triggerPin = 5;
byte echoPin = 4;

void setupHC_SR04() {
  HCSR04.begin(triggerPin, echoPin);
}

void loopHC_SR04()  {
  distances = HCSR04.measureDistanceCm(temperature);
}
