// remote

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

const int potx = A0;
const int poty = A1;

RF24 radio(7, 8);
const byte address[6] = "85236";

void setup() {

  pinMode(potx, INPUT);
  pinMode(poty, INPUT);
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

int data[2];

void loop(){
  delay(60);
  data[0] = analogRead(potx);
  data[1] = analogRead(poty);
  radio.write(&data, sizeof(data));
  delay(60);
}
