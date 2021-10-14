#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "0FieIMStyFgb2-dMhPaeBnTYaM36hzif";
char ssid[] = "NIKUNJ";
char pass[] = "NIKUNJ987";


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}
void loop()
{
Blynk.run();
}
