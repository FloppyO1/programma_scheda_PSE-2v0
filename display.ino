#define WIDTHFONT 6
#define HEIGHTFONT 8

void initDisplay() {
  int tries = 0;
  while (tries < 5) {
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
      Serial.println(F("SSD1306 allocation failed"));
      tries++;
    } else {
      display.clearDisplay();
      display.drawBitmap(0, 0, image_floppylab_logo, 128, 64, WHITE);
      display.display();
      Serial.println("Display OK");
      return;
    }
  }
}

void drawText(char* word, uint8_t fontSize, uint8_t color, uint8_t x, uint8_t y) {
  display.setTextSize(fontSize);  // Draw 2X-scale text
  display.setTextColor(color);
  display.setCursor(x, y);
  display.print(word);
}

void drawTextCentered(char* word, uint8_t length, uint8_t fontSize, uint8_t color, uint8_t y) {
  int wordDimX = WIDTHFONT * length * fontSize;
  display.setTextSize(fontSize);  // Draw 2X-scale text
  display.setTextColor(color);
  display.setCursor((display.width() - wordDimX) / 2, y);
  display.print(word);
}

void updateDisplay() {
  display.display();
}

void clearDisplay() {
  display.clearDisplay();
}

void drawMenuBackground() {
  display.clearDisplay();
  switch (menu) {
    case MAIN_SCREEN:
      display.drawBitmap(0, 53, mainScreenIconsArr[0], 7, 11, WHITE);   // altitude
      display.drawBitmap(0, 0, mainScreenIconsArr[4], 7, 16, WHITE);    // temperature
      break;
    case MAIN_MENU:
      display.drawBitmap(121, 0, mainMenuIconsArr[0], 7, 64, WHITE);   // sidebar
      display.drawBitmap(2, 22, mainMenuIconsArr[2], 118, 20, WHITE);  // selected
      display.drawBitmap(0, 5, mainMenuIconsArr[3], 74, 15, WHITE);    // unselected prev
      display.drawBitmap(0, 44, mainMenuIconsArr[3], 74, 15, WHITE);   // unselected next
      break;
  }
}

void drawScrollThing(uint8_t y) {
  display.drawBitmap(123, y, mainMenuIconsArr[1], 3, 8, WHITE);  //scroll thing
}