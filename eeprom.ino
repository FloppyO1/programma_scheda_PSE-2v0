void initEEPROM() {
  int tries = 0;
  while (tries < 5) {
    if (myMem.begin() == false) {
      Serial.println("EEPROM connection FAILED");
      delay(250);
      tries++;
    } else {
      /* uncomment only if is the first time that you upload the code (comment the other lines), after uploaded reapload with only the last four lines uncommented */
      // myMem.put(GPS_ON_EEPROM_ADDRESS, true);
      // myMem.put(SOUND_ON_EEPROM_ADDRESS, true);
      // myMem.put(TEMP_UNIT_EEPROM_ADDRESS, CELSIUS);
      // myMem.put(TEMP_CAL_EEPROM_ADDRESS, 0);
      // myMem.put(UTC_EEPROM_ADDRESS, UTC);
      Serial.println("EEPROM connected");
      loadSettings();
      Serial.println("settings loaded");
      return;
    }
  }
}

void storeSettings() {
  myMem.put(GPS_ON_EEPROM_ADDRESS, gpsOn);
  myMem.put(SOUND_ON_EEPROM_ADDRESS, soundOn);
  myMem.put(TEMP_UNIT_EEPROM_ADDRESS, tempUnit);
  myMem.put(TEMP_CAL_EEPROM_ADDRESS, tempCorrection);
  myMem.put(UTC_EEPROM_ADDRESS, UTC_zone);
  Serial.println("settings stored in the eeprom");
}

void loadSettings() {
  myMem.get(GPS_ON_EEPROM_ADDRESS, gpsOn);
  myMem.get(SOUND_ON_EEPROM_ADDRESS, soundOn);
  myMem.get(TEMP_UNIT_EEPROM_ADDRESS, tempUnit);
  myMem.get(TEMP_CAL_EEPROM_ADDRESS, tempCorrection);
  myMem.get(UTC_EEPROM_ADDRESS, UTC_zone);
  Serial.println("settings loaded from the eeprom");
}