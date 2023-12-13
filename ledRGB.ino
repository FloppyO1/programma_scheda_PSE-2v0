void initLedRGB() {
  pixels.begin();

#ifdef PRETTYBOOT
  pixels.clear();
  for (int i = 0; i < NUMPIXELS; i++) {
    for (int b = 0; b < 256; b++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, b));
      pixels.show();
      delay(1);
    }
    pixels.show();
  }

//blink with fade
#define BLINKNUM 1
  for (int n = 0; n < BLINKNUM; n++) {
    for (int b = 255; b >= 0; b--) {
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, b));
        pixels.show();
      }
      delay(1);
    }
    for (int b = 0; b < 256; b++) {
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, b));
        pixels.show();
      }
      delay(1);
    }
  }
  for (int b = 255; b >= 0; b--) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, b));
      pixels.show();
    }
    delay(1);
  }
#endif
}
