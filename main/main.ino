#include <Servo.h>

Servo esc1, esc2;

int potX = 1;
int potY = 2;
int potValueX;
int potValueY;

void setup() {                
  esc1.attach(9);
  esc2.attach(10);
  Serial.begin(9600);
}

void loop() {
  potValueX = analogRead(potX);
  potValueY = analogRead(potY);

  potValueX = map(potValueX, 0, 1023, -5, 5) + 45;
  potValueY = map(potValueY, 0, 1023, -5, 5) + 45;

  esc1.write(potValueX);
  esc2.write(potValueY);

  Serial.print(potValueX);
  Serial.print("\t");
  Serial.print(potValueY);
  Serial.println();
  delay(200);
}
