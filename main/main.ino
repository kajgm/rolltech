#include <Stepper.h>

#define inX 1 //Joystick X input
#define inY 0 //Joystick Y input

#define enA 9 //L298N Enable/Speed
#define in1 6 //L298N In1
#define in2 7 //L298N In2

#define sIN1 10
#define sIN2 11
#define sIN3 12
#define sIN4 13

int rotDirection = -1;
int sign = 1;

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;
Stepper stpr = Stepper(stepsPerRevolution, sIN1, sIN3, sIN2, sIN4);

//[IN1 HIGH, IN2 LOW] - CCW
//[IN1 LOW, IN2 HIGH] - CW
//[IN1 HIGH, IN2 HIGH] or [IN1 LOW, IN2 LOW] - STOP

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Set motors to stop initially
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  Serial.begin(9600);
}

void loop() {

  int potValueY = analogRead(inY); // Read potentiometer Y value
  int pwmOutputY = map(potValueY, 0, 1023, -128, 128); // Map the potentiometer Y value from -128 to 128
  int potValueX = analogRead(inX); // Read potentiometer X value
  int pwmOutputX = map(potValueX, 0, 1023, -10, 10); // Map the potentiometer X value from -10 to 10
  
  Serial.print(pwmOutputX);
  Serial.print("\t");
  Serial.print(pwmOutputY);
  Serial.println();

  if (abs(pwmOutputY) < 5 && rotDirection != -1){
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    rotDirection = -1;

  } else if (pwmOutputY < 0 && rotDirection != 1){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    rotDirection = 1;

  } else if (pwmOutputY > 0 && rotDirection != 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    rotDirection = 0;
  }

  analogWrite(enA, abs(pwmOutputY)); // Send PWM signal to L298N Enable pin

  if (abs(pwmOutputX) > 2){
    if (pwmOutputX > 0){
      sign = 1;
    } else {
      sign = -1;
    }
    stpr.setSpeed(abs(pwmOutputX) + 10);
    stpr.step(sign * 10);
  }

}