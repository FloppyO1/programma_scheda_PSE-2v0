// Horizontal dilution of position
// <1	    Ideal	      Highest possible confidence level to be used for applications demanding the highest possible precision at all times.
// 1–2	  Excellent	  At this confidence level, positional measurements are considered accurate enough to meet all but the most sensitive applications.
// 2–5	  Good	      Represents a level that marks the minimum appropriate for making accurate decisions. Positional measurements could be used to make reliable in-route navigation suggestions to the user.
// 5–10   Moderate	  Positional measurements could be used for calculations, but the fix quality could still be improved. A more open view of the sky is recommended.
// 10–20  Fair	      Represents a low confidence level. Positional measurements should be discarded or used only to indicate a very rough estimate of the current location.
// >20 	  Poor	      At this level, measurements should be discarded.

void gpsInit() {
  pinMode(GPS_PPS_PIN, INPUT);
  pinMode(GPS_EN_PIN, OUTPUT);
  digitalWrite(GPS_EN_PIN, HIGH);  // spegne il gps
  Serial1.begin(9600);
}

void enableGPS() {
  digitalWrite(GPS_EN_PIN, LOW);  // accende il gps
  gpsOn = true;
}

void disableGPS() {
  digitalWrite(GPS_EN_PIN, HIGH);  // spegne il gps
  gpsOn = false;
}

void updateGGA() {
  float utc_time, latitude, longitude, hdop, altitude;
  int state, satellites;
  char ns, ew, units;

  utc_time = 0;
  latitude = 0;
  longitude = 0;
  hdop = 0;
  altitude = 0;
  state = 0;
  satellites = 0;
  ns = 0;
  ew = 0;
  units = 0;
  char data[100];
  char temp[100];
  String rawData;
  if (Serial1.available()) {
    rawData = Serial1.readStringUntil('\n');
  } else {
    return;
  }
  rawData.toCharArray(data, 100);
  if (strncmp(data + 3, "GGA", 3) == 0) {
    if (GPSChecksumOK(data, rawData.length())) {
      Serial.println("GPS:");
      Serial.println("checksum OK!");
      Serial.println(data);

      if (rawData.length() <= 35) { // se non c'è il tempo e la posizione la lunghezza è di 31 caratteri quindi la posizione del primo dato è 13
        sscanf(data + 12, "%d,%d,%f", &state, &satellites, &hdop);
        gps.utc_time = 0;
      } else if (rawData.length() <= 45) {// se non c'è la posizione la lunghezza è di 40 caratteri quindi la posizione del primo dato è 21
        sscanf(data + 7, "%f", &utc_time);
        sscanf(data + 21, "%d,%d,%f", &state, &satellites, &hdop);
      } else {
        sscanf(data + 7, "%f,%f,%c,%f,%c,%d,%d,%f,%f,%c", &utc_time, &latitude, &ns, &longitude, &ew, &state, &satellites, &hdop, &altitude, &units);
      }
      if (state == 1) {  // vuol dire che i valori sono validi (0 valori non validi)
        gps.utc_time = utc_time;
        gps.latitude = latitude*100;
        gps.ns = ns;
        gps.longitude = longitude*100;
        gps.ew = ew;
        gps.state = state;
        gps.satellites = satellites;
        gps.hdop = hdop;
        gps.altitude = altitude;
        gps.units = units;
        printPosition();
      } else {
        gps.utc_time = utc_time;
        gps.state = state;
        gps.satellites = satellites;
        gps.hdop = hdop;
        Serial.println("no valid position");
      }
    } else {
      Serial.println("checksum ERROR! DATA DISCARDED");
    }
    calculateTime();
    Serial.println();
  }
}

void printPosition() {
  Serial.println("GLL: Geographic Position, Latitude / Longitude and time...");
  Serial.print("time: ");
  Serial.println(gps.utc_time);

  Serial.print("latitude: ");
  Serial.print(gps.latitude);
  Serial.print(" ");
  Serial.println(gps.ns);

  Serial.print("longitude: ");
  Serial.print(gps.longitude);
  Serial.print(" ");
  Serial.println(gps.ew);

  Serial.print("qulaity of position: ");
  Serial.println(gps.state);

  Serial.print("satellites in view: ");
  Serial.println(gps.satellites);

  Serial.print("hosrizontal precision: ");
  Serial.println(gps.hdop);

  Serial.print("altitude: ");
  Serial.print(gps.altitude);
  Serial.println(gps.units);
  Serial.println();
  Serial.println();
}


int GPSChecksumOK(char *Buffer, int comandLength) {
  unsigned char XOR, i, c;
  XOR = 0;
  for (i = 1; i < (comandLength - 4); i++) {
    c = Buffer[i];
    XOR ^= c;
  }
  return (Buffer[comandLength - 4] == '*') && (Buffer[comandLength - 3] == Hex(XOR >> 4)) && (Buffer[comandLength - 2] == Hex(XOR & 15));
}

char Hex(char Character) {
  char HexTable[] = "0123456789ABCDEF";
  return HexTable[Character];
}

void calculateTime(){
  Serial.println(gps.utc_time);
  orario.ore = (UTC_zone + gps.utc_time / 10000)%24;
  orario.minuti = (gps.utc_time - (gps.utc_time / 10000 * 10000))/100;
  orario.secondi = (gps.utc_time - (gps.utc_time / 100 * 100));
  // Serial.println(orario.ore);
  // Serial.println(orario.minuti);
  // Serial.println(orario.secondi);
}