#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8); // CE, CSN

Servo ESC;
Servo myservo;
int pos = 60;

const byte address[6] = "00001";

int pwmOutputX;
int pwmOutputY;
int potVals[2];

void setup() {
  Serial.begin(9600);

  // Set motors to stop initially
  myservo.attach(3);
  myservo.write(pos);

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
    
    Serial.print("x:");
    Serial.print(pwmOutputX);
    Serial.print(" y:");
    Serial.println(pwmOutputY); 
    
    myservo.write(pwmOutputX);
    ESC.write(pwmOutputY);
    
  } else {
    ESC.write(90);
    myservo.write(60);
  }

}