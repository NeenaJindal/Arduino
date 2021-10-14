// Arduino mega

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(7, 8);
const byte address[6] = "85236";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

int data[2];

void loop(){
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    for(int i=0; i<2; i++){
      Serial.print(data[i]);
      Serial.print(" ");
    }
    Serial.println("");
  }

int potx = data[0];
int poty = data[1];

if (potx == 0){
  digitalWrite(6, 1);
  Serial.println("horn");
}
}
