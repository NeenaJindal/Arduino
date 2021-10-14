// connected from deepakjindaljind@gmail.com and Nikunj987.. as pass

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "qcsPwISZ3X1IJq2O0KSvO921omYqbERJ";
char ssid[] = "NIKUNJ";
char pass[] = "NIKUNJ987";

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();
  if (pinValue == 1) {
    Serial.println("A");
  }
  else {
    Serial.println("a");
  }
}

BLYNK_WRITE(V2)
{
  int pinValue2 = param.asInt();
  if (pinValue2 == 1) {
    Serial.println("B");
  }
  else {
    Serial.println("b");
  }
}

BLYNK_WRITE(V3)
{
  int pinValue3 = param.asInt();
  if (pinValue3 == 1) {
    Serial.println("C");
  }
  else {
    Serial.println("c");
  }
}

BLYNK_WRITE(V4)
{
  int pinValue4 = param.asInt();
  if (pinValue4 == 1) {
    Serial.println("D");
  }
  else {
    Serial.println("d");
  }
}
