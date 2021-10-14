#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define RightMotorSpeed       D0   //14 
#define RightMotorDir         D1   //12 
#define LeftMotorSpeed        D2   //13 
#define LeftMotorDir          D3   //15 

char auth[] = "ac5eMJs3XZ5Pc5-FSLYkVgJpx6H22tex";  //Blynk Authentication Token
char ssid[] = "NIKUNJ";           //WIFI Name
char pass[] = "NIKUNJ987";           //WIFI Password

int minRange = 312;
int maxRange = 712;

int minspeed = 450;
int maxspeed = 1020;
int nospeed = 0;


void moveControl(int x, int y)
{
//Move Forward
    if(y >= maxRange && x >= minRange && x<= maxRange)
    {
        digitalWrite( RightMotorDir,HIGH);
        digitalWrite(LeftMotorDir,HIGH);
        analogWrite(RightMotorSpeed, maxspeed);
        analogWrite(LeftMotorSpeed , maxspeed);
        Serial.println("forward");
    }


//Move Forward Right
    else if(x >= maxRange && y >= maxRange)
    {
        digitalWrite( RightMotorDir, HIGH);
        digitalWrite(LeftMotorDir,HIGH);
        analogWrite(RightMotorSpeed,minspeed);
        analogWrite(LeftMotorSpeed ,maxspeed);
        Serial.println("right");
    }

//Move Forward Left
    else if(x <= minRange && y >= maxRange)
    {
        digitalWrite( RightMotorDir,HIGH);
        digitalWrite(LeftMotorDir,HIGH);
        analogWrite(RightMotorSpeed,maxspeed);
        analogWrite(LeftMotorSpeed ,minspeed);
        Serial.println("left");
    }

//No Move
    else if(y < maxRange && y > minRange && x < maxRange && x > minRange)
    {
        analogWrite(RightMotorSpeed,nospeed);
        analogWrite(LeftMotorSpeed , nospeed);
        Serial.println("stop");
    }

//Move Backward
    else if(y <= minRange && x >= minRange && x <= maxRange)
    {
        digitalWrite( RightMotorDir,LOW);
        digitalWrite(LeftMotorDir,LOW);
        analogWrite(RightMotorSpeed,maxspeed);
        analogWrite(LeftMotorSpeed ,maxspeed);
        Serial.println("backward");
    }

//Move Backward Right
    else if(y <= minRange && x <= minRange)
    {
        digitalWrite( RightMotorDir,LOW);
        digitalWrite(LeftMotorDir,LOW);
        analogWrite(RightMotorSpeed,minspeed);
        analogWrite(LeftMotorSpeed ,maxspeed);
        Serial.println("right");
    }

//Move Backward Left
    else if(y <= minRange && x >= maxRange)
    {
        digitalWrite( RightMotorDir,LOW);
        digitalWrite(LeftMotorDir,LOW);
        analogWrite(RightMotorSpeed,maxspeed);
        analogWrite(LeftMotorSpeed ,minspeed);
        Serial.println("left");
    }
}

void setup()
{
    Serial.begin(9600);

  WiFi.begin("NIKUNJ", "NIKUNJ987");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  Blynk.begin(auth, ssid, pass);

    pinMode(RightMotorSpeed, OUTPUT);
    pinMode(LeftMotorSpeed , OUTPUT);
    pinMode( RightMotorDir, OUTPUT);
    pinMode(LeftMotorDir, OUTPUT);

    digitalWrite(RightMotorSpeed, LOW);
    digitalWrite(LeftMotorSpeed , LOW);
    digitalWrite( RightMotorDir, HIGH);
    digitalWrite(LeftMotorDir, HIGH);
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
