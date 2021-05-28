

void setupBME280()  {
  bmx280.resetToDefaults();
  bmx280.writeOversamplingPressure(BMx280MI::OSRS_P_x16);
  bmx280.writeOversamplingTemperature(BMx280MI::OSRS_T_x16); 
  bmx280.writeOversamplingHumidity(BMx280MI::OSRS_H_x16);
}

void loopBME280() {
  
}

void tempSensor_function()  {
  if (!bmx280.measure())  {
    return;
  }
  do  {
    delay(100);
  } while(!bmx280.hasValue());
  temperature = bmx280.getTemperature();
}
