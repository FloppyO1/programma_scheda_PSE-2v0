void playBeep() {
  if (soundOn) {
    tone(BUZZER_PIN, 2000, 50);
  }
}

void playErrorBeep() {
  if (soundOn) {
    tone(BUZZER_PIN, 500, 50);
    delay(100);
    tone(BUZZER_PIN, 500, 50);
  }
}

void playSuccessfulBeep() {
  if (soundOn) {
    tone(BUZZER_PIN, 500, 100);
    delay(100);
    tone(BUZZER_PIN, 1000, 100);
    delay(100);
    tone(BUZZER_PIN, 2000, 100);
  }
}
