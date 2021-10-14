#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "0FieIMStyFgb2-dMhPaeBnTYaM36hzif";
char ssid[] = "NIKUNJ";
char pass[] = "NIKUNJ987";

WiFiClient client;
WiFiServer server(80);

#define Relay1 D0+
#define Relay2 D1
#define Relay3 D2
#define Relay4 D3

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  Blynk.begin(auth, ssid, pass);
  server.begin();
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
}

void loop() 
{
  client = server.available();  //Gets a client that is connected to the server and has data available for reading.    
  if (client == 1)
  {  
    String request =  client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    if(request == "GET /A HTTP/1.1")
    {
      digitalWrite(Relay1, LOW);
    }
    if(request == "GET /a HTTP/1.1")
    {
      digitalWrite(Relay1, HIGH);
    }
    if(request == "GET /B HTTP/1.1")
    {
      digitalWrite(Relay2, LOW);
    }
    if(request == "GET /b HTTP/1.1")
    {
      digitalWrite(Relay2, HIGH);
    }
    if(request == "GET /C HTTP/1.1")
    {
      digitalWrite(Relay3, LOW);
    }
    if(request == "GET /c HTTP/1.1")
    {
      digitalWrite(Relay3, HIGH);
    }
    if(request == "GET /D HTTP/1.1")
    {
      digitalWrite(Relay4, HIGH);
    }
    if(request == "GET /d HTTP/1.1")
    {
      digitalWrite(Relay4, LOW);
    }
  }
  Blynk.run();
}
