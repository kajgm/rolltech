#include <Servo.h>

Servo esc[3];

int potValue;

void init_esc(int index, int pin) {
  esc[index].attach(pin);
}

void write_esc(int index, int value) {
  esc[index].write(value);
}


void run_esc(int pot_index, int esc_index) {
  potValue = analogRead(pot_index);
  potValue = map(potValue, 0, 1023, -5, 5) + 45;

  write_esc(esc_index, potValue);

  Serial.print(potValue);
  Serial.print("\t");
}

