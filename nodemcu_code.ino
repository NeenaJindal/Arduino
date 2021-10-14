// nodemcu code

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Blynk.h>

char auth[] = "ac5eMJs3XZ5Pc5-FSLYkVgJpx6H22tex";
char ssid[] = "NIKUNJ";
char pass[] = "NIKUNJ987";

int minRange = 140;
int maxRange = 910;

void moveControl(int x, int y)
{
    if(y >= maxRange && x >= minRange && x<= maxRange)
    {
        Serial.println("F");
    }

    else if(y <= minRange && x >= minRange && x <= maxRange)
    {
        Serial.println("B");
    }

    else if(y <= maxRange && y >= minRange && x >= maxRange)
    {
        Serial.println("R");
    }

    else if(y <= maxRange && y >= minRange && x <= minRange)
    {
        Serial.println("L");
    }

    else if(y < maxRange && y > minRange && x < maxRange && x > minRange)
    {
        Serial.println("S");
    }
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V0) {
  int pinValue = param.asInt();
//  Serial.print("Speed= ");
  Serial.print(pinValue);
}

BLYNK_WRITE(V2)
{
  int pinValue2 = param.asInt();
  if (pinValue2 == 1) {
    Serial.println("H");            // HORN ON
  }
  else {
    Serial.println("h");           // HORN OFF
  }
}

BLYNK_WRITE(V3)
{
  int pinValue3 = param.asInt();
  if (pinValue3 == 1) {
    Serial.println("O");           // OBSTACLE
  }
  else {
    Serial.println("S");
  }
}

BLYNK_WRITE(V4)
{
  int pinValue4 = param.asInt();
  if (pinValue4 == 1) {
    Serial.println("l");           // LINE FOLLOW
  }
  else {
    Serial.println("S");
  }
}

BLYNK_WRITE(V1)
{
    int x = param[0].asInt();
    int y = param[1].asInt();
    moveControl(x,y);
}
