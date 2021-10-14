// remote

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(7, 8);
const byte address[6] = "85236";

void setup() {
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

int data = 1234;

void loop(){
  delay(60);
  radio.write(&data, sizeof(data));
  delay(60);
  Serial.println(data);
}
