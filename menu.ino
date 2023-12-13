// ================================================================================================= //
//                                          MAIN SCREEN                                              //
// ================================================================================================= //
void mainScreen() {
  switch (menu_line) {
    case MS_SCREEN1:
      drawMainScreen1();
      break;
    case MS_SCREEN2:
      drawMainScreen2();
      break;
  }
}

void mainScreenEvents(int event) {
  switch (event) {  // in base al pulsante premuto
    case EVENT_CLICK + B_UP_PIN:
      if (menu_line == 1) {
        menu_line = 0;
        playBeep();
      } else {
        playErrorBeep();
      }
      break;
    case EVENT_CLICK + B_DWN_PIN:
      if (menu_line == 0) {
        menu_line = 1;
        playBeep();
      } else {
        playErrorBeep();
      }
      break;
    case EVENT_CLICK + B_R_PIN:
      menu = MAIN_MENU;
      menu_line = 0;
      playBeep();
      Serial.println("main menu");
      break;
    default:
      playErrorBeep();
      break;
  }
  calculatePrevNext(LINES_MAIN_MENU);
}

void drawMainScreen1() {
  clearDisplay();
  /* temperature */
  display.drawBitmap(0, 0, mainScreenIconsArr[4], 7, 16, WHITE);  // temperature
  char temperature[10];
  if (tempUnit == CELSIUS) {
    sprintf(temperature, "%d C", getTemp());
    display.drawRect(24, 4, 2, 2, WHITE);
  } else {
    sprintf(temperature, "%dK", getTemp());
  }
  drawText(temperature, 1, WHITE, 9, 4);
  /* gps */
  if (gpsOn == true) {                                                 // stampa a schermo il simbolo del gps on/off
    display.drawBitmap(0, 53, mainScreenIconsArr[0], 7, 11, WHITE);    // altitude
    display.drawBitmap(108, 0, mainScreenIconsArr[2], 18, 15, WHITE);  // gps on
    char satNumb[5];
    sprintf(satNumb, "%2d", gps.satellites);
    drawText(satNumb, 1, WHITE, 93, 4);  //scrive il numero di satelliti in vista
    if (gps.utc_time != 0) {
      char ora[10];
      sprintf(ora, "%02d:%02d:%02d", orario.ore, orario.minuti, orario.secondi);
      drawTextCentered(ora, 8, 2, WHITE, 25);
    } else {
      drawTextCentered("no time", 7, 2, WHITE, 25);
    }
    if (gps.state == 0 && halfSecToggle) {
      display.drawBitmap(123, 5, mainScreenIconsArr[3], 5, 5, WHITE);  // gps no position
      drawText("N/A", 1, WHITE, 10, 55);
    }
    if (gps.state == 1 || gps.state == 2) {
      char alt[10];
      sprintf(alt, "%dm", (int)gps.altitude);  // scrive l'altitudine
      drawText(alt, 1, WHITE, 10, 55);
    }
  } else {
    display.drawBitmap(108, 0, mainScreenIconsArr[1], 18, 15, WHITE);  // gps off
    if (halfSecToggle) {
      drawTextCentered("to get more", 11, 1, WHITE, 23);
      drawTextCentered("information", 11, 1, WHITE, 32);
      drawTextCentered("activate GPS", 12, 1, WHITE, 41);
    }
  }
  drawText("menu", 1, WHITE, 96, 56);
  display.drawBitmap(124, 57, settingsMenuIconsArr[5], 4, 7, WHITE);  // right arrow
}

void drawMainScreen2() {
  clearDisplay();
  /* gps signal quality */
  if (gpsOn) {
    drawText("GPS signal", 1, WHITE, 0, 0);
    if (gps.hdop < 1) {
      drawText("excellent", 1, WHITE, 66, 0);
    } else if (gps.hdop < 2) {
      drawText("good", 1, WHITE, 66, 0);
    } else if (gps.hdop < 5) {
      drawText("normal", 1, WHITE, 66, 0);
    } else if (gps.hdop < 10) {
      drawText("sufficient", 1, WHITE, 66, 0);
    } else if (gps.hdop < 20) {
      drawText("poor", 1, WHITE, 66, 0);
    } else if (gps.hdop >= 20) {
      drawText("garbage", 1, WHITE, 66, 0);
    }
  } else {
    drawText("GPS disabled", 1, WHITE, 0, 0);
  }

  /* number of satellites in view */
  char satellites[10];
  sprintf(satellites, "Satellites: %d", gps.satellites);
  drawText(satellites, 1, WHITE, 0, 12);
  /* coordinates */
  drawText("Coordinates:", 1, WHITE, 0, 25);
  if (gps.state == 0 && halfSecToggle) {
    drawText("N/A", 1, WHITE, 0, 34);
    drawText("N/A", 1, WHITE, 0, 45);
    drawText("N/A", 1, WHITE, 57, 57);
  } else if (gps.state == 1 || gps.state == 2) {
    char latitude[20];
    char longitude[20];
    int la = gps.latitude;
    int latdeg = la / 10000;
    la %= 10000;
    int latprim = la / 100;
    la %= 100;
    int latsec = la;
    int lo = gps.longitude;
    int longdeg = lo / 10000;
    lo %= 10000;
    int longprim = lo / 100;
    lo %= 100;
    int longsec = lo;
    sprintf(latitude, "%02d %02d\'%02d\" %c", latdeg, latprim, latsec, gps.ns);
    sprintf(longitude, "%02d %02d\'%02d\" %c", longdeg, longprim, longsec, gps.ew);
    drawText(latitude, 1, WHITE, 0, 34);
    drawText(longitude, 1, WHITE, 0, 45);
    display.drawRect(13, 34, 2, 2, WHITE);
    display.drawRect(13, 46, 2, 2, WHITE);
    /* altitude */
    char altitude[10];
    sprintf(altitude, "%4.1fm", gps.altitude);
    drawText(altitude, 1, WHITE, 57, 57);
  }
  drawText("Altitude:", 1, WHITE, 0, 57);
  /* draw satellite gif */
  if (gpsOn == false) {
    display.drawBitmap(95, 19, mainScreen2IconsArr[0], 29, 29, WHITE);
    display.drawBitmap(113, 19, mainScreen2IconsArr[4], 11, 5, WHITE);
  } else {
    display.drawBitmap(113, 19, mainScreen2IconsArr[5], 8, 5, WHITE);
    display.drawBitmap(95, 19, mainScreen2IconsArr[fourFrameGifFrameNumber], 29, 29, WHITE);
  }
}

// ================================================================================================= //
//                                        MAIN MENU                                                  //
// ================================================================================================= //
void mainMenu() {
  drawMainMenu();
}

void mainMenuEvents(int event) {
  Serial.print("event: ");
  Serial.println(event);
  switch (event) {  // in base al pulsante premuto
    case EVENT_CLICK + B_UP_PIN:
      playBeep();
      menu_line = (menu_line + LINES_MAIN_MENU - 1) % LINES_MAIN_MENU;  // calcola la linea selezionata, deve diminuire il numero della linea
      break;
    case EVENT_CLICK + B_DWN_PIN:
      playBeep();
      menu_line = (menu_line + 1) % LINES_MAIN_MENU;  // calcola la linea selezionata, deve aumentare il numero della linea
      break;
    case EVENT_CLICK + B_R_PIN:  //entra menu premendo il pulsate destro
      switch (menu_line) {
        case MM_ENCODER_LINE:
          menu = ENCODER_MENU;
          menu_line = 0;
          Serial.println("encoder menu");
          break;
        case MM_LEVEL_LINE:
          menu = LEVEL_MENU;
          menu_line = 0;
          Serial.println("level menu");
          break;
        case MM_SETTINGS_LINE:
          menu = SETTINGS_MENU;
          menu_line = 0;
          Serial.println("settings menu");
          break;
      }
      playBeep();
      break;
    case EVENT_CLICK + B_L_PIN:
      menu = MAIN_SCREEN;
      menu_line = 0;
      Serial.println("main screen");
      playBeep();
      break;
    default:
      playErrorBeep();
      break;
  }
  calculatePrevNext(LINES_MAIN_MENU);
}

void drawMainMenu() {
  clearDisplay();
  /* background */
  display.drawBitmap(121, 0, mainMenuIconsArr[0], 7, 64, WHITE);   // sidebar
  display.drawBitmap(2, 22, mainMenuIconsArr[2], 118, 20, WHITE);  // selected
  display.drawBitmap(0, 5, mainMenuIconsArr[3], 74, 15, WHITE);    // unselected prev
  display.drawBitmap(0, 44, mainMenuIconsArr[3], 74, 15, WHITE);   // unselected next
  /* lines */
  drawText(mainMenuNames[menu_line_prev], 1, WHITE, 4, 9);
  drawText(mainMenuNames[menu_line], 2, WHITE, 12, 25);
  drawText(mainMenuNames[menu_line_next], 1, WHITE, 4, 48);
  drawScrollThing(scrollYPosition(LINES_MAIN_MENU));
  // Serial.print("scroll y pos: ");
  // Serial.println(scrollYPosition(LINES_MAIN_MENU));
}
// ================================================================================================= //
//                                       ENCODER MENU                                                //
// ================================================================================================= //
void encoderMenu() {
  drawEncoderMenu();
}

void encoderMenuEvents(int event) {
  Serial.println("encoder menu");

  switch (event) {  // in base al pulsante premuto cambia la linea selezionata
    case EVENT_CLICK + B_UP_PIN:
      playBeep();
      menu_line = (menu_line + LINES_ENCODER_MENU - 1) % LINES_ENCODER_MENU;  // calcola la linea selezionata, deve diminuire il numero della linea
      break;
    case EVENT_CLICK + B_DWN_PIN:
      playBeep();
      menu_line = (menu_line + 1) % LINES_ENCODER_MENU;  // calcola la linea selezionata, deve aumentare il numero della linea
      break;
    case EVENT_LONG_CLICK + B_L_PIN:
      menu = MAIN_MENU;
      menu_line = 0;
      Serial.println("main menu");
      playBeep();
      break;
    default:
      playErrorBeep();
      break;
  }
  calculatePrevNext(LINES_ENCODER_MENU);
}

void drawEncoderMenu() {
}

// ================================================================================================= //
//                                       SETTINGS MENU                                               //
// ================================================================================================= //
void settingsMenu() {
  drawSettingsMenu();
}

void drawSettingsMenu() {
  clearDisplay();
  /* lines of the menu */
  for (int i = 0; i < LINES_SETTINGS_MENU; i++) {
    drawText(settingsMenuNames[i], 1, WHITE, 12, (12 * i) + 3);
  }
  /* cursor */
  display.drawBitmap(3, (12 * menu_line) + 3, settingsMenuIconsArr[5], 4, 7, WHITE);
  /* sliders */
  if (gpsOn) {
    display.drawBitmap(104, 1, settingsMenuIconsArr[3], 23, 10, WHITE);
  } else {
    display.drawBitmap(104, 1, settingsMenuIconsArr[2], 23, 10, WHITE);
  }
  //------------
  if (soundOn) {
    display.drawBitmap(104, 14, settingsMenuIconsArr[3], 23, 10, WHITE);
  } else {
    display.drawBitmap(104, 14, settingsMenuIconsArr[2], 23, 10, WHITE);
  }
  //------------
  if (tempUnit == CELSIUS) {
    display.drawBitmap(104, 27, settingsMenuIconsArr[0], 23, 10, WHITE);
  } else {
    display.drawBitmap(104, 27, settingsMenuIconsArr[1], 23, 10, WHITE);
  }
  /* temp calib arrows */
  display.drawBitmap(124, 42, settingsMenuIconsArr[5], 4, 7, WHITE);
  display.drawBitmap(99, 42, settingsMenuIconsArr[4], 4, 7, WHITE);
  /* TEMPERATURE */
  int t = getTemp();
  char tstr[5];
  sprintf(tstr, "%d", t);
  if (tempUnit == CELSIUS) {
    if (t >= 10 || (t < 0 && t > -10)) {
      drawText(tstr, 1, WHITE, 108, 42);
    } else if (t <= -10) {
      drawText(tstr, 1, WHITE, 105, 42);
    } else {
      drawText(tstr, 1, WHITE, 112, 42);
    }
  } else {
    drawText(tstr, 1, WHITE, 105, 42);
  }
  /* UTC arrow */
  display.drawBitmap(124, 51, settingsMenuIconsArr[5], 4, 7, WHITE);
  display.drawBitmap(99, 51, settingsMenuIconsArr[4], 4, 7, WHITE);
  /* UTC */
  char UTCstr[5];
  if (UTC_zone > 0) {
    sprintf(UTCstr, "+%d", UTC_zone);
  } else {
    sprintf(UTCstr, "%d", UTC_zone);
  }
  if (UTC_zone == 0) {  // solo un carattere
    drawText(UTCstr, 1, WHITE, 112, 51);
  } else if (UTC_zone >= 10 || UTC_zone <= -10) {  // tre caratteri
    drawText(UTCstr, 1, WHITE, 105, 51);
  } else {  //due caratteri
    drawText(UTCstr, 1, WHITE, 108, 51);
  }
}

void settingsMenuEvents(int event) {
  switch (event) {  // in base al pulsante premuto cambia la linea selezionata
    case EVENT_CLICK + B_UP_PIN:
      playBeep();
      menu_line = (menu_line + LINES_SETTINGS_MENU - 1) % LINES_SETTINGS_MENU;  // calcola la linea selezionata, deve diminuire il numero della linea
      break;
    case EVENT_CLICK + B_DWN_PIN:
      playBeep();
      menu_line = (menu_line + 1) % LINES_SETTINGS_MENU;  // calcola la linea selezionata, deve aumentare il numero della linea
      break;
    case EVENT_CLICK + B_R_PIN:
      switch (menu_line) {
        case SM_GPS_ON_LINE:
          gpsOn = !gpsOn;
          playBeep();
          break;
        case SM_SOUND_ON_LINE:
          soundOn = !soundOn;
          playBeep();
          break;
        case SM_TEMP_UNIT_LINE:
          tempUnit = !tempUnit;
          playBeep();
          break;
        case SM_TEMP_CAL_LINE:
          tempCorrection++;
          playBeep();
          break;
        case SM_UTC_LINE:
          if (UTC_zone + 1 <= 12) {
            UTC_zone++;
            playBeep();
          } else {
            playErrorBeep();
          }
          break;
      }
      break;
    case EVENT_CLICK + B_L_PIN:
      switch (menu_line) {
        case SM_TEMP_CAL_LINE:
          tempCorrection--;
          playBeep();
          break;
        case SM_UTC_LINE:
          if (UTC_zone - 1 >= -14) {
            UTC_zone--;
            playBeep();
          } else {
            playErrorBeep();
          }
          break;
      }
      break;
    case EVENT_LONG_CLICK + B_L_PIN:
      storeSettings();
      menu = MAIN_MENU;
      menu_line = MM_SETTINGS_LINE;
      if (gpsOn) {
        enableGPS();
      } else {
        disableGPS();
      }
      Serial.println("main menu");
      playSuccessfulBeep();
      break;

    default:
      playErrorBeep();
      break;
  }
  calculatePrevNext(LINES_MAIN_MENU);
}

// ================================================================================================= //
//                                         LEVEL MENU                                                //
// ================================================================================================= //
void levelMenu() {
  drawLevelMenu();
  if (levelRunning) {
    updateLevel();
  } else {
    pixels.clear();
    pixels.show();
  }
}

void drawLevelMenu() {
  clearDisplay();
  /* selected line */
  display.drawBitmap(1, 49, levelMenuIconsArr[8], 32, 15, WHITE);
  display.drawBitmap(35, 49, levelMenuIconsArr[9], 53, 15, WHITE);
  display.drawBitmap(90, 49, levelMenuIconsArr[10], 36, 15, WHITE);
  switch (menu_line) {
    case LM_PAUSE_PLAY_LINE:
      display.drawBitmap(1, 10, levelMenuIconsArr[4], 19, 21, WHITE);
      break;
    case LM_PRECISION_LOW_LINE:
      display.drawBitmap(1, 49, levelMenuIconsArr[5], 32, 15, WHITE);
      break;
    case LM_PRECISION_MEDIUM_LINE:
      display.drawBitmap(35, 49, levelMenuIconsArr[6], 53, 15, WHITE);
      break;
    case LM_PRECISION_HIGH_LINE:
      display.drawBitmap(90, 49, levelMenuIconsArr[7], 36, 15, WHITE);
      break;
  }
  /* precision */
  switch (levelPrecision) {
    case LEVEL_PREC_LOW:
      drawText("Precision: L", 1, WHITE, 1, 39);
      break;
    case LEVEL_PREC_MEDIUM:
      drawText("Precision: M", 1, WHITE, 1, 39);
      break;
    case LEVEL_PREC_HIGH:
      drawText("Precision: H", 1, WHITE, 1, 39);
      break;
  }
  /* PLAY/PAUSE */
  if (levelRunning) {
    /* simbol */
    display.drawBitmap(5, 13, levelMenuIconsArr[3], 11, 15, WHITE);
    /* running gif */
    switch (fourFrameGifFrameNumber) {
      case 0:
        drawText("Running", 1, WHITE, 23, 17);
        break;
      case 1:
        drawText("Running.", 1, WHITE, 23, 17);
        break;
      case 2:
        drawText("Running..", 1, WHITE, 23, 17);
        break;
      case 3:
        drawText("Running...", 1, WHITE, 23, 17);
        break;
    }
  } else {
    drawText("On pause", 1, WHITE, 23, 17);
    display.drawBitmap(7, 13, levelMenuIconsArr[2], 8, 15, WHITE);
  }
  /* grafical visualization */
  //display.drawBitmap(94, 1, levelMenuIconsArr[1], 33, 33, WHITE);
}

void levelMenuEvents(int event) {
  switch (event) {
    case EVENT_CLICK + B_L_PIN:  // ritorna al menu precedente
      menu = MAIN_MENU;
      menu_line = MM_LEVEL_LINE;
      levelRunning = false;
      pixels.clear();
      pixels.show();
      playBeep();
      break;
    case EVENT_CLICK + B_R_PIN:
      switch (menu_line) {
        case LM_PAUSE_PLAY_LINE:
          levelRunning = !levelRunning;
          break;
        case LM_PRECISION_LOW_LINE:
          levelPrecision = LEVEL_PREC_LOW;
          break;
        case LM_PRECISION_MEDIUM_LINE:
          levelPrecision = LEVEL_PREC_MEDIUM;
          break;
        case LM_PRECISION_HIGH_LINE:
          levelPrecision = LEVEL_PREC_HIGH;
          break;
      }
      playBeep();
      break;
    case EVENT_CLICK + B_UP_PIN:
      menu_line = (menu_line + LINES_LEVEL_MENU - 1) % LINES_LEVEL_MENU;
      playBeep();
      break;
    case EVENT_CLICK + B_DWN_PIN:
      menu_line = (menu_line + 1) % LINES_LEVEL_MENU;
      playBeep();
      break;
    default:
      playErrorBeep();
      break;
      calculatePrevNext(LINES_MAIN_MENU);
  }
}
// ================================================================================================= //

void calculateMenu(int event) {
  switch (menu) {
    case MAIN_SCREEN:  //nessuna linea nel menu 0 (schermata principale)
      mainScreenEvents(event);
      break;
    case MAIN_MENU:  // main menu
      mainMenuEvents(event);
      break;
    case ENCODER_MENU:  // encoder menu
      encoderMenuEvents(event);
      break;
    case SETTINGS_MENU:  // settings menu
      settingsMenuEvents(event);
      break;

    case LEVEL_MENU:  // settings menu
      levelMenuEvents(event);
      break;
  }
}

void calculatePrevNext(uint8_t numberOfLines) {
  menu_line_next = (menu_line + 1) % numberOfLines;
  menu_line_prev = (menu_line + numberOfLines - 1) % numberOfLines;
}

uint8_t scrollYPosition(uint8_t maxlines) {
  //return (menu_line * ((SCROLL_TING_Y_MAX - SCROLL_TING_Y_MIN) / (maxlines - 1))) + 2;
  return map(menu_line, 0, maxlines - 1, SCROLL_TING_Y_MIN, SCROLL_TING_Y_MAX);
}