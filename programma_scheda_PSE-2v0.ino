#include <OneButton.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <SparkFun_External_EEPROM.h>
#include <math.h>
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include "images.h"
#include "constants.h"
#include "prototipes.h"


void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Starting...");

  Wire.setClock(1000000);
  Serial.println("I2C freq 1Mbit/sec");

  initialBoot();
}

unsigned int halfSecTime = 0;
bool halfSecToggle = false;

unsigned int quarterSecTime = 0;
bool quarterSecToggle = false;

unsigned int fourFrameGifTime = 0;
int fourFrameGifFrameNumber = 0;


void loop() {
  updateHalfSecToggle();        // aggiorna il oneSecToggle
  updateQuarterSecToggle();     // aggiorna il quarterSecToggle
  updateFourFrameGifCounter();  // aggiorna il frame delle gif fourFrameGifFrameNumber
  checkButtons();               // controlla se i pulsanti sono stati premuti o meno
  if (gpsOn) {
    updateGGA();
  }

  switch (menu) {
    case MAIN_SCREEN:
      mainScreen();
      break;
    case MAIN_MENU:
      mainMenu();
      break;
    case ENCODER_MENU:
      encoderMenu();
      break;
    case SETTINGS_MENU:
      settingsMenu();
      break;
    case LEVEL_MENU:
      levelMenu();
      break;
  }
  updateDisplay();
}



void initialBoot() {
  //scritte da visualizzare

  //inizializzazione di tutto
  initDisplay();
  delay(1000);  //per far vedere il logo

  clearDisplay();
  drawTextCentered("SYSTEM", 6, 2, WHITE, 16);
  drawTextCentered("BOOT", 4, 2, WHITE, 36);
  updateDisplay();

  initLedRGB();
  initButtons();
  gpsInit();
  enableGPS();
  initTempSensor();
  initEEPROM();
  initAccelerometer();

  delay(500);
  clearDisplay();
  updateDisplay();
}

void updateHalfSecToggle() {
  if (millis() - halfSecTime >= 500) {
    halfSecTime = millis();
    //halfSecToggle =!halfSecToggle;
    if (halfSecToggle == false) {
      halfSecToggle = true;
      //Serial.println("toggle true");
    } else {
      halfSecToggle = false;
      //Serial.println("toggle false");
    }
  }
}

void updateQuarterSecToggle() {
  if (millis() - quarterSecTime >= 250) {
    //quarterSecTime = millis();
    quarterSecToggle = !quarterSecToggle;
    if (quarterSecToggle == false) {
      quarterSecToggle = true;
      //Serial.println("toggle true");
    } else {
      quarterSecToggle = false;
      //Serial.println("toggle false");
    }
  }
}

void updateFourFrameGifCounter() {
  if (millis() - fourFrameGifTime >= 250) {
    fourFrameGifTime = millis();
    fourFrameGifFrameNumber = (fourFrameGifFrameNumber + 1) % 4;
  }
}
