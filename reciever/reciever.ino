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

#define enA 5 //L298N Enable/Speed
#define in1 4 //L298N In1
#define in2 3 //L298N In2

//Jitter tolerances
#define DCError 5

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

int pwmOutputY;
int DCDir = 0; //L298N

void setup() {
  Serial.begin(9600);

  // Set motors to stop initially
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {

  if (radio.available()) {
    int potVals[2];
    radio.read(&potVals, sizeof(potVals));
    //Serial.println(potVals);

    pwmOutputY = potVals[1];
    Serial.println(pwmOutputY);
    
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
  }

}