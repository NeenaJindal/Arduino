#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "ac5eMJs3XZ5Pc5-FSLYkVgJpx6H22tex";  //Blynk Authentication Token
char ssid[] = "NIKUNJ";           //WIFI Name
char pass[] = "NIKUNJ987";           //WIFI Password

int minRange = 140;
int maxRange = 910;

void moveControl(int x, int y)
{
    if(y >= maxRange && x >= minRange && x<= maxRange)
    {
        Serial.println("forward");
    }

    else if(y <= minRange && x >= minRange && x <= maxRange)
    {
        Serial.println("backward");
    }

    else if(y <= maxRange && y >= minRange && x >= maxRange)
    {
        Serial.println("right");
    }

    else if(y <= maxRange && y >= minRange && x <= minRange)
    {
        Serial.println("left");
    }

    else if(y < maxRange && y > minRange && x < maxRange && x > minRange)
    {
        Serial.println("stop");
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


BLYNK_WRITE(V1)
{
    int x = param[0].asInt();
    int y = param[1].asInt();
    moveControl(x,y);
}
