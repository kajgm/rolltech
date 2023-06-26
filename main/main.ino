#include "defines.h"

//Init Functions
void setup() {                
  init_esc(ESC0);
  init_esc(ESC1);
  Serial.begin(default_baud);
}

//Run Functions
void loop() {
  run_esc(ESC0);
  run_esc(ESC1);

  Serial.println();
  //delay(200);
}