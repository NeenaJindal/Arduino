// Arduino Mega

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(48, 49); // CE, CSN
const byte address[6] = "85236";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

int data;

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    Serial.println(data);
  }
//  else{
//    Serial.println("no");
//  }
}
