#include <Servo.h>

//ESC Map
Servo esc[2];
int analog_pin[] = {1, 2};
int read_pin[] = {9, 10};

int potValue;

//-------------Basic Functions------------//
void init_esc(int index) {
  esc[index].attach(read_pin[index]);
}

void write_esc(int index, int value) {
  esc[index].write(value);
}

//------------Run Functions------------//
void run_esc(int esc_index) {
  potValue = analogRead(analog_pin[esc_index]);
  potValue = map(potValue, 0, 1023, -5, 5) + 45;

  write_esc(esc_index, potValue);

  Serial.print(potValue);
  Serial.print("\t");
}

