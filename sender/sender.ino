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

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {

  int potValueX = analogRead(inX); // Read joystick X value
  int pwmOutputX = map(potValueX, 0, 1023, -15, 15); // Map the joystick X value from -10 to 10
  int potValueY = analogRead(inY); // Read joystick Y value
  int pwmOutputY = map(potValueY, 0, 1023, -255, 255); // Map the joystick Y value from -128 to 128


  const int buffer[2] = {pwmOutputX, pwmOutputY};
  radio.write(&buffer, sizeof(buffer));
}