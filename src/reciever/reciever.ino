/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define enA 5 //L298N Enable/Speed
#define in1 4 //L298N In1
#define in2 3 //L298N In2

//Jitter tolerances
#define DCError 5

RF24 radio(7, 8); // CE, CSN
Servo ESC;

const byte address[6] = "00001";

int pwmOutputX;
int pwmOutputY;
int potVals[2];

int DCDir = 0; //L298N

void setup() {
  Serial.begin(9600);

  // Set motors to stop initially
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  ESC.attach(2, 1000, 3000);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {

  if (radio.available()) {
    
    radio.read(&potVals, sizeof(potVals));
    //Serial.println(potVals);

    pwmOutputX = potVals[0];
    pwmOutputY = potVals[1];
    
    Serial.println(pwmOutputY);

    ESC.write(pwmOutputY);
    
    if (abs(pwmOutputX) < DCError && DCDir != 0){
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      DCDir = 0;

    } else if (pwmOutputX < 0 && DCDir != 1){
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      DCDir = 1;

    } else if (pwmOutputX > 0 && DCDir != -1) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      DCDir = -1;
    }

    analogWrite(enA, abs(pwmOutputX)); // Send PWM signal to L298N Enable pin
  }

}