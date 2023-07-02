#include <Stepper.h>

#define inX 1 //Joystick X input
#define inY 0 //Joystick Y input

#define enA 5 //L298N Enable/Speed
#define in1 6 //L298N In1
#define in2 7 //L298N In2

#define sIN1 10 //ULN2003 In1
#define sIN2 11 //ULN2003 In2
#define sIN3 12 //ULN2003 In3
#define sIN4 13 //ULN2003 In4

//Jitter tolerances
#define DCError 5
#define StepError 2

// Direction of rotation for controllers
// 0 = Stopped
// 1 = CW
// -1 = CCW
int DCDir = 0; //L298N
int StepDir = 0; //ULN2003

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;

//Create stepper object
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

  Serial.begin(9600); //Debug
}

void loop() {

  int potValueY = analogRead(inY); // Read joystick Y value
  int pwmOutputY = map(potValueY, 0, 1023, -255, 255); // Map the joystick Y value from -128 to 128
  int potValueX = analogRead(inX); // Read joystick X value
  int pwmOutputX = map(potValueX, 0, 1023, -15, 15); // Map the joystick X value from -10 to 10
  
  //Debug
  Serial.print(pwmOutputX);
  Serial.print("\t");
  Serial.print(pwmOutputY);
  Serial.println();

  //DC motor movement (L298N)
  if (abs(pwmOutputY) < DCError && DCDir != 0){
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    DCDir = 0;

  } else if (pwmOutputY < 0 && DCDir != 1){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    DCDir = 1;

  } else if (pwmOutputY > 0 && DCDir != -1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    DCDir = -1;
  }

  analogWrite(enA, abs(pwmOutputY)); // Send PWM signal to L298N Enable pin

  //Stepper motor movement (ULN2003)
  if (abs(pwmOutputX) < StepError){
    StepDir = 0;
  } else if (pwmOutputX < 0 && StepDir != 1){
    StepDir = 1;
  } else if (pwmOutputX > 0 && StepDir != -1) {
    StepDir = -1;
  }

  stpr.setSpeed(abs(pwmOutputX));
  stpr.step(StepDir * 10);

}