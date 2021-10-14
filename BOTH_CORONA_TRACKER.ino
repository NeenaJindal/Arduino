#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <StringSplitter.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const char *host = "api.thingspeak.com";
const int httpPort = 80;  
const char* url1 = "https://api.thingspeak.com/apps/thinghttp/send_request?api_key=Z6YW1G8Z507JQA2V"; 
HTTPClient http;
const char* url2 = "https://api.thingspeak.com/apps/thinghttp/send_request?api_key=DMT74D45WHYUCPNG"; 
HTTPClient http2; 

String cases;
String death;
String recover;

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
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   Wi-Fi not   ");
    lcd.setCursor(0,1);
    lcd.print("   Available   ");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   NodeMCU is   ");
  lcd.setCursor(0,1);
  lcd.print("   Connected!   ");
  Serial.println(WiFi.localIP());
}

void loop() 
{
  http.begin(host,httpPort,url1); 
  int httpCode = http.GET();
  String data = http.getString();
  Serial.println(httpCode);
  Serial.println("***************        Data Read        ***************");
  Serial.println(data);
  
  StringSplitter *splitter = new StringSplitter(data, '/', 3);  // new StringSplitter(string_to_split, delimiter, limit)
  int itemCount = splitter->getItemCount();
  Serial.println("***************        Data Splited        ***************");
  Serial.println("Item count: " + String(itemCount));

  for(int i = 0; i < itemCount; i++)
  {
    String item = splitter->getItemAtIndex(i);
    Serial.println("Item @ index " + String(i) + ": " + String(item));
    if(i == 0)
    {
      cases = item;
    }
    if(i == 1)
    {
      death = item;
    }
    if(i == 2)
    {
      recover = item;
    }
  }

  Serial.println("***************        Data Filtered        ***************");
  Serial.println(cases);
  Serial.println(death);
  Serial.println(recover);

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
  
  cases.remove(0,26);
  cases.remove(cases.length()-2,cases.length());
  death.remove(0,13);
  death.remove(death.length()-1,death.length());
  recover.remove(0,13);
  recover.remove(recover.length()-8, recover.length());
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("COVID-19 India");
  lcd.setCursor(0,1);
  lcd.print("Cases:" + (String) cases);
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("COVID-19 India");
  lcd.setCursor(0,1);
  lcd.print("Deaths:" + (String) death);
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("COVID-19 India");
  lcd.setCursor(0,1);
  lcd.print("Rcvrd:" + (String) recover);
  delay(3000);

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
  lcd.print("Rcvrd:" + (String) recoverwo);
  delay(3000);
}
