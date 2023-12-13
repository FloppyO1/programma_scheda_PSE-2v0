// button_name.attachClick(function_name);
// button_name.attachDoubleClick(function_name);
// button_name.attachLongPressStart(function_name);
// button_name.attachLongPressStop(function_name);
// button_name.attachDuringLongPress(function_name);

void initButtons() {
  button_UP.attachClick(buttonUPClick);
  button_DWN.attachClick(buttonDWNClick);
  button_R.attachClick(buttonRClick);
  button_L.attachClick(buttonLClick);
  button_L.attachLongPressStart(buttonLLongClick);

  Serial.println("Buttons OK");
}


/* 
BUTTONS FUNCTIONS
*/
void buttonUPClick() {
  Serial.println("button UP single click");
  calculateMenu(EVENT_CLICK + B_UP_PIN);
}

void buttonDWNClick() {
  Serial.println("button DOWN single click");
  calculateMenu(EVENT_CLICK + B_DWN_PIN);
}

void buttonRClick() {
  Serial.println("button RIGHT single click");
  calculateMenu(EVENT_CLICK + B_R_PIN);
}

void buttonLClick() {
  Serial.println("button LEFT single click");
  calculateMenu(EVENT_CLICK + B_L_PIN);
}

void buttonLLongClick(){
  Serial.println("button LEFT long click");
  calculateMenu(EVENT_LONG_CLICK + B_L_PIN);
}
/*============================================================================*/

void checkButtons() {
  button_UP.tick();
  button_DWN.tick();
  button_R.tick();
  button_L.tick();
}