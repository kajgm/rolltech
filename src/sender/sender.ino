/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define inX 0 //Joystick X input
#define inY 1 //Joystick Y input

#define RED_PIN1 5
#define GREEN_PIN1 6
#define BLUE_PIN1 7

#define RED_PIN2 2
#define GREEN_PIN2 3
#define BLUE_PIN2 4

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";
int buffer[2];
int currentSpeed = 90;
int currentDir = 60;

void setup() {
  Serial.begin(19200);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  init_LED(RED_PIN1, BLUE_PIN1, GREEN_PIN1);
  init_LED(RED_PIN2, BLUE_PIN2, GREEN_PIN2);

  currentSpeed = 90; 
  currentDir = 60;
}

void loop() {
  //assume full charge -will need to change
  digitalWrite(GREEN_PIN2, HIGH);

  int potValueX = analogRead(inX); 
  int pwmOutputX = map(potValueX, 0, 1023, 0, 120); 

  int potValueY = analogRead(inY); 
  int pwmOutputY = map(potValueY, 0, 1023, 45, 135); 


  if(abs(pwmOutputX-60) <= 5 && abs(pwmOutputY-90) <= 5){
    digitalWrite(GREEN_PIN1, LOW);
  }
  else {
    digitalWrite(GREEN_PIN1, HIGH);
  }

  if (abs(pwmOutputX-60) <= 40 && pwmOutputY<70) {
    //Left
    currentDir = 0;
    buffer[0] = currentDir;
    buffer[1] = changeSpeed(105);
    Serial.println("Left");
  } else if (abs(pwmOutputX-60) <= 40 && pwmOutputY>110) {
    //Right
    currentDir = 120;
    buffer[0] = currentDir;
    buffer[1] = changeSpeed(105);
    Serial.println("Right");
  } else if (pwmOutputX > 80 && abs(pwmOutputY-90) <= 40) {
    //Backward
    currentDir = 60;
    buffer[0] = currentDir;
    buffer[1] = changeSpeed(75);
    Serial.println("Backward");
  } else if (pwmOutputX < 40 && abs(pwmOutputY-90) <= 40) {
    //Forward
    currentDir = 60;
    buffer[0] = currentDir;
    buffer[1] = changeSpeed(105);
    Serial.println("Forward");
  } else if (pwmOutputX > 80 && pwmOutputY < 70) {
    //backward right
    currentDir = 30;
    buffer[0] = currentDir;
    buffer[1] = changeSpeed(75);
    Serial.println("backward right");
    
  } else if (pwmOutputX < 40 && pwmOutputY < 70) {
    //forward left
    currentDir = 30;
    buffer[0] = currentDir;
    buffer[1] = changeSpeed(105);
    Serial.println("forward left");
  } else if (pwmOutputX > 80 && pwmOutputY > 110) {
    //backward left
    currentDir = 90;
    buffer[0] = currentDir;
    buffer[1] = changeSpeed(75);
    Serial.println("backward left");
  } else if (pwmOutputX < 40 && pwmOutputY > 110) {
    //forward right
    currentDir = 90;
    buffer[0] = currentDir;
    buffer[1] = changeSpeed(105);
    Serial.println("forward right");

  } 
  else {
    // No movement
    if(currentSpeed != 90 && currentDir != 60) {
      buffer[0] = currentDir;
    } else {
      buffer[0] = 60;
    }
    buffer[1] = changeSpeed(90);
    //Serial.print("No movement:");
    //Serial.println(currentSpeed);

  }

  radio.write(&buffer, sizeof(buffer));

  delay(50);
  
  Serial.print("x:");
  Serial.print(pwmOutputX);
  Serial.print(" y:");
  Serial.println(pwmOutputY); 
}

void init_LED(int red, int blue, int green) {
  //setup led pins 1 and 2
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
}


int changeSpeed(int finalSpeed) {
  int tmp_curSpeed = 0; 

  if(finalSpeed > currentSpeed) {
    tmp_curSpeed = currentSpeed++;
  } else if (finalSpeed < currentSpeed) {
    tmp_curSpeed = currentSpeed--;
  } else {
    tmp_curSpeed = currentSpeed;
  }

  return tmp_curSpeed;
}