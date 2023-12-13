// temp vs voltage -> 10mV/°C   T[°C]=(Vread-500mV)/10mV

void initTempSensor() {
  pinMode(TEMP_SENS_PIN, INPUT);
  analogReadResolution(ADC_RES);
}

int getTemp() {
  int tempRaw[100];
  for (int i = 0; i < 100; i++) {
    tempRaw[i] = analogRead(TEMP_SENS_PIN);
  }
  int tempRawFiltered = 0;
  for (int i = 0; i < 100; i++) {
    tempRawFiltered += tempRaw[i];
  }
  tempRawFiltered = tempRawFiltered / 100;
  float mVread = (REF_VOLTAGE / (1 << ADC_RES)) * tempRawFiltered;
  int celstemp = ((mVread - 0.5) / 0.01) + tempCorrection;
  if(tempUnit == CELSIUS){
    return celstemp;
  }else{
    return celstemp + 273;
  }
}