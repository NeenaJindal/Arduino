#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <StringSplitter.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const char *host = "api.thingspeak.com";
const int httpPort = 80;  
const char* url2 = "https://api.thingspeak.com/apps/thinghttp/send_request?api_key=W5XOIVJLDTJTXBZ6"; 
HTTPClient http2; 

String caseswo;
String deathwo;
String recoverwo;

void setup() 
{
  // put your setup code here, to run once:
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
  WiFi.begin("NIKUNJ", "NIKUNJ987");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
}

void loop() 
{
  http2.begin(host,httpPort,url2); 
  int http2Code = http2.GET();
  String data2 = http2.getString();
  Serial.println(http2Code);
  Serial.println("***************       WORLD Data Read        ***************");
  Serial.println(data2);
  
  StringSplitter *splitter2 = new StringSplitter(data2, '/', 3);  // new StringSplitter(string_to_split, delimiter, limit)
  int itemCount2 = splitter2->getItemCount();
  Serial.println("***************       WORLD Data Splited        ***************");
  Serial.println("Item count: " + String(itemCount2));

  for(int i2 = 0; i2 < itemCount2; i2++)
  {
    String item2 = splitter2->getItemAtIndex(i2);
    Serial.println("Item @ index " + String(i2) + ": " + String(item2));
    if(i2 == 0)
    {
      caseswo = item2;
    }
    if(i2 == 1)
    {
      deathwo = item2;
    }
    if(i2 == 2)
    {
      recoverwo = item2;
    }
  }
  caseswo.remove(0,26);
  caseswo.remove(caseswo.length()-2,caseswo.length());
  deathwo.remove(0,13);
  deathwo.remove(deathwo.length()-1,deathwo.length());
  recoverwo.remove(0,13);
  recoverwo.remove(recoverwo.length()-8, recoverwo.length());
  
  Serial.println("***************       WORLD Data Filtered        ***************");
  Serial.println(caseswo);
  Serial.println(deathwo);
  Serial.println(recoverwo);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("COVID-19 World");
  lcd.setCursor(0,1);
  lcd.print("Cases:" + (String) caseswo);
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("COVID-19 World");
  lcd.setCursor(0,1);
  lcd.print("Deaths:" + (String) deathwo);
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("COVID-19 World");
  lcd.setCursor(0,1);
  lcd.print("Recover:" + (String) recoverwo);
  delay(3000);
}
