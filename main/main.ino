int potX = 1;
int potY = 2;


void setup() {                
  init_esc(0, 9);
  init_esc(1, 10);
  Serial.begin(9600);
}

void loop() {
  run_esc(potX, 0);
  run_esc(potY, 1);
  Serial.println();
  delay(200);
}