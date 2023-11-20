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

void setup() {
  Serial.begin(19200);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  //setup led pins 1 and 2
  pinMode(RED_PIN1, OUTPUT);
  pinMode(GREEN_PIN1, OUTPUT);
  pinMode(BLUE_PIN1, OUTPUT);

  pinMode(RED_PIN2, OUTPUT);
  pinMode(GREEN_PIN2, OUTPUT);
  pinMode(BLUE_PIN2, OUTPUT);

  //set leds to off
  digitalWrite(RED_PIN1, LOW);
  digitalWrite(GREEN_PIN1, LOW);
  digitalWrite(BLUE_PIN1, LOW);

  digitalWrite(RED_PIN2, LOW);
  digitalWrite(GREEN_PIN2, LOW);
  digitalWrite(BLUE_PIN2, LOW);

}

void loop() {
  //assume full charge -will need to change
  digitalWrite(GREEN_PIN2, HIGH);

  int potValueX = analogRead(inX); 
  int pwmOutputX = map(potValueX, 0, 1023, 0, 120); 

  int potValueY = analogRead(inY); 
  int pwmOutputY = map(potValueY, 0, 1023, 45, 135); 


  if (abs(pwmOutputX-60) <= 20 && pwmOutputY<80){
    //Forward
    buffer[0] = 60;
    buffer[1] = 70;
    Serial.println("Forward");
  } else if (abs(pwmOutputX-60) <= 20 && pwmOutputY>100) {
    //Backward
    buffer[0] = 60;
    buffer[1] = 110;
    Serial.println("Backward");
  } else if (pwmOutputX > 80 && abs(pwmOutputY-90) <= 20) {
    // right
    buffer[0] = 120;
    buffer[1] = 60;
    Serial.println("right");
  } else if (pwmOutputX < 40 && abs(pwmOutputY-90) <= 20) {
    //left
    buffer[0] = 0;
    buffer[1] = 60;
    Serial.println("left");
  } else if (pwmOutputX > 80 && pwmOutputY < 70) {
    //forward right
    buffer[0] = 90;
    buffer[1] = 60;
    Serial.println("forward right");
  } else if (pwmOutputX < 40 && pwmOutputY < 70) {
    //forward left
    buffer[0] = 30;
    buffer[1] = 60;
    Serial.println("forward left");
  } else if (pwmOutputX > 80 && pwmOutputY > 110) {
    //backward right
    buffer[0] = 30;
    buffer[1] = 120;
    Serial.println("backward right");
  } else if (pwmOutputX < 40 && pwmOutputY > 110) {
    //backward left
    buffer[0] = 90;
    buffer[1] = 120;
    Serial.println("backward left");
  } else {
    // No movement
    buffer[0] = 60;
    buffer[1] = 90;
    Serial.println("No movement");
  }

  radio.write(&buffer, sizeof(buffer));
  
  // Serial.print("x:");
  // Serial.print(pwmOutputX);
  // Serial.print(" y:");
  // Serial.println(pwmOutputY); 
}