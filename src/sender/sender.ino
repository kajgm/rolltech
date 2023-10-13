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
  digitalWrite(RED_PIN2, LOW);
  digitalWrite(GREEN_PIN2, HIGH);
  digitalWrite(BLUE_PIN2, LOW);

  int potValueX = analogRead(inX); // Read joystick X value
  int pwmOutputX = map(potValueX, 0, 1023, -255, 255); // Map the joystick X value from -15 to 15

  int potValueY = analogRead(inY); // Read joystick Y value
  int pwmOutputY = map(potValueY, 0, 1023, 45, 135); // Map the joystick Y value from -128 to 128

  if (abs(pwmOutputX) > 10){
    buffer[0] = pwmOutputX;
    digitalWrite(RED_PIN1, LOW);
    digitalWrite(GREEN_PIN1, LOW);
    digitalWrite(BLUE_PIN1, HIGH);
  }
  
  if (abs(pwmOutputY-90) > 20){
    buffer[1] = pwmOutputY;
    digitalWrite(RED_PIN1, LOW);
    digitalWrite(GREEN_PIN1, LOW);
    digitalWrite(BLUE_PIN1, HIGH);
  }

  if((abs(pwmOutputX) < 10) && (abs(pwmOutputY-90) < 20)) {
    buffer[0] = 0;
    buffer[1] = 90;
    digitalWrite(RED_PIN1, LOW);
    digitalWrite(GREEN_PIN1, LOW);
    digitalWrite(BLUE_PIN1, LOW);
  }

  radio.write(&buffer, sizeof(buffer));

  Serial.println(pwmOutputX);
  Serial.println(pwmOutputY);
}