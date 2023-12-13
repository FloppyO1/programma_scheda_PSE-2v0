//================================================ buttons ================================================
#define EVENT_CLICK 100
#define EVENT_DOUBLE_CLICK 200
#define EVENT_LONG_CLICK 300

void initButtons();
void buttonUPClick();
void buttonDWNClick();
void buttonRClick();
void buttonLClick();
void buttonLLongClick();

void checkButtons();

//================================================ ledRGB ================================================
void initLedRGB();

//==================================== sensore temperatura (TC1047A) =====================================
#define KELVIN false
#define CELSIUS true
int getTemp();

//================================================ display ================================================
void initDisplay();
void drawText(char* word, uint8_t fontSize, uint8_t color, uint8_t x, uint8_t y);
void drawTextCentered(char* word, uint8_t length, uint8_t fontSize, uint8_t color, uint8_t y);
void updateDisplay();
void clearDisplay();

void drawScrollThing(uint8_t y);

//================================================ buzzer ================================================
void playBeep();
void playErrorBeep();
void playSuccessfulBeep();

//================================================ EEPROM ================================================
ExternalEEPROM myMem;

void initEEPROM();
void storeSettings();
void loadSettings();

//============================================ ACCELEROMETER ===========================================
void initAccelerometer();
void updateLevel();

//================================================ GPS ================================================
typedef struct GPSdata {
  int utc_time = 0;
  int latitude = 0;
  int longitude = 0;
  float hdop = 0;
  float altitude = 0;
  int state = 0;
  int satellites = 0;
  char ns = 0;
  char ew = 0;
  char units = 0;
} GPSdata;

typedef struct tempo {
  uint8_t ore = 0;
  uint8_t minuti = 0;
  uint8_t secondi = 0;
} tempo;

void gpsInit();
void enableGPS();
void disableGPS();
void getGGA();
int GPSChecksumOK(char* Buffer, int comandLength);
char Hex(char Character);
void printPosition();
void calculateTime();

//================================================ menu ================================================
enum menus { MAIN_SCREEN,
             MAIN_MENU,
             ENCODER_MENU,
             LEVEL_MENU,
             SETTINGS_MENU };

#define LINES_MAIN_SCREEN 2  // screen1, screen2
enum mainScreenLinesName { MS_SCREEN1,
                           MS_SCREEN2 };

#define LINES_MAIN_MENU 3  // encoder, level, settings
enum mainMenuLinesName { MM_ENCODER_LINE,
                         MM_LEVEL_LINE,
                         MM_SETTINGS_LINE };
char mainMenuNames[LINES_MAIN_MENU][20]{
  { "Encoder" },
  { "Level" },
  { "Settings" }
};

#define LINES_ENCODER_MENU 2
enum encoderMenuLinesName { EM_MEASURE_DISTANCE_LINE,
                            EM_MEASURE_ANGLE_LINE,
                            EM_SETTINGS_LINE };
char encoderMenuNames[LINES_MAIN_MENU][20]{
  { "Distance" },
  { "Angle" },
  { "Settings" }
};

#define LINES_SETTINGS_MENU 5
enum settingsMenuLinesName { SM_GPS_ON_LINE,
                             SM_SOUND_ON_LINE,
                             SM_TEMP_UNIT_LINE,
                             SM_TEMP_CAL_LINE,
                             SM_UTC_LINE
};
char settingsMenuNames[LINES_SETTINGS_MENU][20]{
  { "GPS" },
  { "Sound" },
  { "Temperature" },
  { "Temp. calib." },
  { "Jet lag" }
};

#define LINES_LEVEL_MENU 4
enum levelMenuLinesName { LM_PAUSE_PLAY_LINE,
                          LM_PRECISION_LOW_LINE,
                          LM_PRECISION_MEDIUM_LINE,
                          LM_PRECISION_HIGH_LINE
};

void mainScreen();
void drawMainScreen1();
void drawMainScreen2();
void mainScreenEvents(int event);

void mainMenu();
void drawMainMenu();
void mainMenuEvents(int event);

void encoderMenu();
void drawEncoderMenu();
void encoderMenuEvents(int event);

void settingsMenu();
void drawSettingsMenu();
void settingsMenuEvents(int event);

void levelMenu();
void drawLevelMenu();
void levelMenuEvents(int event);

void calculateMenu(int event);                  // aggiorna la linea selezionata e il menu in base all'evento avvenuto (evento = EVENT_XXX + B_XXX_PIN)
void calculatePrevNext(uint8_t numberOfLines);  // calcola la linea sucessiva e precendente in base al menu e linea selezionata e al numero di linee del menu(da chiamare dopo aver cambiato linea selezionata)
uint8_t scrollYPosition(uint8_t maxlines);

//================================================ altro ================================================
void updateHalfSecToggle();
void updateQuarterSecToggle();
void updateFourFrameGifCounter();

//================================================ variabili ================================================
uint8_t menu = 0;
uint8_t menu_line = 0;   // linea selezionata del menu visualizzato
uint8_t menu_line_prev;  // linea precedente selezionata del menu visualizzato
uint8_t menu_line_next;  // linea successiva selezionata del menu visualizzato

/* IMPOSTAZIONI SALVATE IN EEPROM */
bool gpsOn = false;
bool soundOn = true;
bool tempUnit = CELSIUS;
int tempCorrection = 0;  // valore aggiunto al valore di temperatura letto
int8_t UTC_zone = 2;     // utc+2 rome
/*------------------*/

enum precisionLevels { LEVEL_PREC_LOW,
                       LEVEL_PREC_MEDIUM,
                       LEVEL_PREC_HIGH,
};
uint8_t levelPrecision = LEVEL_PREC_LOW;
bool levelRunning = false;


GPSdata gps;
tempo orario;
Adafruit_MMA8451 mma = Adafruit_MMA8451();
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_WS2812, NEO_GRB + NEO_KHZ800);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
OneButton button_UP(B_UP_PIN, true, false);
OneButton button_DWN(B_DWN_PIN, true, false);
OneButton button_R(B_R_PIN, true, false);
OneButton button_L(B_L_PIN, true, false);