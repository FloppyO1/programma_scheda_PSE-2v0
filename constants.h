#ifndef CONSTANTS_H
#define CONSTANTS_H

/* ACTIVATE CODE PARTS */
#define PRETTYBOOT

/* BUTTONS */
#define B_UP_PIN 22
#define B_DWN_PIN 23
#define B_R_PIN 24
#define B_L_PIN 25


/* DISPLAY */
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32


/* LED */
#define LED_ALIVE_PIN 20

#define PIN_WS2812 13  // PIN NEOPIXEL
#define NUMPIXELS 8 //numero led striscia


/* BUZZER */
#define BUZZER_PIN 21

/* EEPROM */
#define GPS_ON_EEPROM_ADDRESS 0
#define SOUND_ON_EEPROM_ADDRESS 4
#define TEMP_UNIT_EEPROM_ADDRESS 8
#define TEMP_CAL_EEPROM_ADDRESS 12
#define UTC_EEPROM_ADDRESS 16


/* SENSORS */
// TEMPERATURE
// temp vs voltage -> 10mV/°C   T[°C]=(Vread-500mV)/10mV
#define TEMP_SENS_PIN 26
#define REF_VOLTAGE 3.127
#define ADC_RES 12

// GPS
#define GPS_EN_PIN 18
#define GPS_PPS_PIN 19

/* OTHER */
#define UTC_RANGE_POSITIVE 12
#define UTC_RANGE_NEGATIVE -14
#define UTC 2
#define WHITE 1
#define BLACK 1

#endif