#include <Servo.h>

Servo ESC1, ESC2, ESC3, ESC4;     // create servo object to control the ESC

int potValue;  // value from the analog pin

void setup() {
  // Attach the ESC on pin 9
  ESC1.attach(9);
  //ESC2.attach(10);
  //ESC3.attach(11);
  //ESC4.attach(12);
}

void loop() {
  potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue = map(potValue, 0, 1023, 0, 400);   // scale it to use it with the servo library (value between 0 and 180)
  ESC1.write(potValue);    // Send the signal to the ESC
  //ESC2.write(potValue); 
  //ESC3.write(potValue); 
  //ESC4.write(potValue); 
}