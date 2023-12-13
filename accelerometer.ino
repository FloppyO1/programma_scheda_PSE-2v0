void initAccelerometer() {
  int tries = 0;
  Serial.println("start MMA8451");
  while (!mma.begin(0x1C)) {
    Serial.println("Couldnt start accelerometer");
    tries++;
    delay(100);
    if (tries >= 5) {
      Serial.println("!ACCELEROMETER ERROR!");
      return;
    }
  }
  Serial.println("MMA8451 found!");
  mma.setRange(MMA8451_RANGE_2_G);
  Serial.print("Range = ");
  Serial.print(2 << mma.getRange());
  Serial.println("G");
}


void updateLevel() {
  sensors_event_t event;
  mma.getEvent(&event);
  float x = event.acceleration.x;
  float y = event.acceleration.y;
  float ro = sqrt((x * x) + (y * y));
  float p = 1;
  switch (levelPrecision) {
    case LEVEL_PREC_LOW:
      p = 1;
      break;
    case LEVEL_PREC_MEDIUM:
      p = 3;
      break;
    case LEVEL_PREC_HIGH:
      p = 5;
      break;
  }
  if (ro > 1.0 / p) {
    float rad = atan2(y, x);
    float deg = -rad * (180 / PI);
    if (deg < 0) {
      deg += 360.0;
    }
    int led_on = ((int)(deg / 45)) % 8;
    pixels.clear();
    pixels.setPixelColor(led_on, pixels.Color(map(ro, 0, 10, 0, 255), map(ro, 0, 10, 50, 0), 0));
    pixels.setPixelColor((led_on + 7) % 8, pixels.Color(map(ro, 0, 10, 0, 255), map(ro, 0, 10, 50, 0), 0));
    pixels.show();  // Send the updated pixel colors to the hardware.
  } else {
    for (int i = 0; i < 8; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    }
    pixels.show();
  }
}