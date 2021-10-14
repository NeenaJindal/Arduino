#define BLYNK_PRINT Serial
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266_SSL.h>
#include <Blynk.h>
#include <NewPing.h>
#include <Servo.h>

Servo myservo;

#define M1_p D0
#define M1_n D1
#define M2_p D2
#define M2_n D3

#define R D5
#define L A0

#define TRIG_PIN D7
#define ECHO_PIN D6
#define MAX_DISTANCE 200
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

#define soundp D8

int obstacle_avoiding = 0;
int vall = 0;
int valr = 0;
int distance = 100;
char val;
long duration;

#define auth "ac5eMJs3XZ5Pc5-FSLYkVgJpx6H22tex"
#define ssid "NIKUNJ"
#define pass "NIKUNJ987"
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "Ridhima"
#define AIO_KEY "aio_XROy930p7eLjUKuiMAOQKPBSSVhe"

BLYNK_WRITE(V0)
{
  int pinValue1 = param.asInt();
  Serial.println(pinValue1);
  if (pinValue1 == 1) {
    moveForward();
    Serial.println("GOING FORWARD");
  }
  else {
    moveStop();
    obstacle_avoiding = 0;
    Serial.println("STOP");
  }
}

BLYNK_WRITE(V1)
{
  int pinValue2 = param.asInt();
  Serial.println(pinValue2);
  if (pinValue2 == 1) {
    moveBackward();
    Serial.println("GOING BACKWARD");
  }
  else {
    moveStop();
    obstacle_avoiding = 0;
    Serial.println("STOP");
  }
}

BLYNK_WRITE(V2)
{
  int pinValue3 = param.asInt();
  Serial.println(pinValue3);
  if (pinValue3 == 1) {
    turnLeft();
    Serial.println("TURNING LEFT");
  }
  else {
    moveStop();
    obstacle_avoiding = 0;
    Serial.println("STOP");
  }
}

BLYNK_WRITE(V3)
{
  int pinValue4 = param.asInt();
  Serial.println(pinValue4);
  if (pinValue4 == 1) {
    turnRight();
    Serial.println("TURNING RIGHT");
  }
  else {
    moveStop();
    obstacle_avoiding = 0;
    Serial.println("STOP");
  }
}

BLYNK_WRITE(V4)
{
  int pinValue5 = param.asInt();
  Serial.println(pinValue5);
  if (pinValue5 == 1) {
    obstacle_avoiding = 1;
    Serial.println("OBSTACLE AVOIDING MODE");
  }
  else {
    moveStop();
    obstacle_avoiding = 0;
    Serial.println("STOP");
  }
}

BLYNK_WRITE(V5)
{
  int pinValue6 = param.asInt();
  Serial.println(pinValue6);
  if (pinValue6 == 1) {
    obstacle_avoiding = 2;
    Serial.println("LINE FOLLOWER MODE");
  }
  else {
    moveStop();
    obstacle_avoiding = 0;
    Serial.println("STOP");
  }
}

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe C1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Button1"); // FeedName
Adafruit_MQTT_Subscribe C2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Button2");
Adafruit_MQTT_Subscribe C3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Button3");
Adafruit_MQTT_Subscribe C4 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Button4");
Adafruit_MQTT_Subscribe C5 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Button5");
Adafruit_MQTT_Subscribe C6 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Button6");
Adafruit_MQTT_Subscribe C7 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Button7");

void MQTT_connect();

void setup()
{
  myservo.attach(D4);
  myservo.write(115);
  pinMode(M1_p, OUTPUT);
  pinMode(M1_n, OUTPUT);
  pinMode(M2_p, OUTPUT);
  pinMode(M2_n, OUTPUT);
  pinMode(R, INPUT);
  pinMode(L, INPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(soundp, OUTPUT);
  distance = readPing();
  delay(100);
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  Blynk.begin(auth, ssid, pass);

  mqtt.subscribe(&C1);
  mqtt.subscribe(&C2);
  mqtt.subscribe(&C3);
  mqtt.subscribe(&C4);
  mqtt.subscribe(&C5);
  mqtt.subscribe(&C6);
  mqtt.subscribe(&C7);
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");

}

int lookRight()
{
  myservo.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  return distance;
}
int lookLeft()
{
  myservo.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
  delay(100);
}
int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0)
  {
    cm = 250;
  }
  return cm;
}
void moveStop() {
  digitalWrite(M1_p, LOW);
  digitalWrite(M2_p, LOW);
  digitalWrite(M1_n, LOW);
  digitalWrite(M2_n, LOW);
}
void moveForward() {
  digitalWrite(M1_p, HIGH);
  digitalWrite(M2_p, HIGH);
  digitalWrite(M1_n, LOW);
  digitalWrite(M2_n, LOW);
}
void moveBackward() {
  digitalWrite(M1_n, HIGH);
  digitalWrite(M2_n, HIGH);
  digitalWrite(M1_p, LOW);
  digitalWrite(M2_p, LOW);
}
void turnRight() {
  digitalWrite(M1_n, HIGH);
  digitalWrite(M2_p, HIGH);
  digitalWrite(M1_p, LOW);
  digitalWrite(M2_n, LOW);
}
void turnLeft() {
  digitalWrite(M1_p, HIGH);
  digitalWrite(M2_n, HIGH);
  digitalWrite(M1_n, LOW);
  digitalWrite(M2_p, LOW);
}
void obstacleavoiding() {
  int distanceR = 0;
  int distanceL =  0;
  delay(40);

  if (distance <= 15)
  {
    moveStop();
    delay(100);
    moveBackward();
    delay(1000);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);

    if (distanceR >= distanceL)
    {
      myservo.write(115);
      turnRight();
      delay(1000);
    } else
    {
      myservo.write(115);
      turnLeft();
      delay(1000);
    }
  } else
  {
    moveForward();
  }
  distance = readPing();
}
void linefollower() {
  valr = digitalRead(R);
  vall = digitalRead(L);
  delay(10);
  if ((valr == 1) && (vall == 1)) {
    moveStop();
  }
  if ((valr == 0) && (vall == 0)) {
    moveForward();
  }
  if ((valr == 0) && (vall == 1)) {
    turnRight();
  }
  if ((valr == 1) && (vall == 0)) {
    turnLeft();
  }
}

void loop()
{
  MQTT_connect();
  Blynk.run();

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) {
    if (subscription == &C1) {
      Serial.print(F("Got: "));
      Serial.println((char *)C1.lastread);
      int C1_State = atoi((char *)C1.lastread);
      if (C1_State == 1) {
        moveForward();
        Serial.println("GOING FORWARD");
      }
      else {
        moveStop();
        Serial.println("STOP");
      }
    }
    if (subscription == &C2) {
      Serial.print(F("Got: "));
      Serial.println((char *)C2.lastread);
      int C2_State = atoi((char *)C2.lastread);
      if (C2_State == 1) {
        moveBackward();
        Serial.println("GOING BACKWARD");
      }
      else {
        moveStop();
        Serial.println("STOP");
      }
    }
    if (subscription == &C3) {
      Serial.print(F("Got: "));
      Serial.println((char *)C3.lastread);
      int C3_State = atoi((char *)C3.lastread);
      if (C3_State == 1) {
        turnLeft();
        Serial.println("TURNING LEFT");
      }
      else {
        moveStop();
        Serial.println("STOP");
      }
    }
    if (subscription == &C4) {
      Serial.print(F("Got: "));
      Serial.println((char *)C4.lastread);
      int C4_State = atoi((char *)C4.lastread);
      if (C4_State == 1) {
        turnRight();
        Serial.println("TURNING RIGHT");
      }
      else {
        moveStop();
        Serial.println("STOP");
      }
    }
    if (subscription == &C5) {
      Serial.print(F("Got: "));
      Serial.println((char *)C5.lastread);
      int C5_State = atoi((char *)C5.lastread);
      if (C5_State == 1){
       digitalWrite(soundp, HIGH);
       Serial.println("HORN ON"); 
      }
      else {
      digitalWrite(soundp, LOW);  
      Serial.println("HORN OFF");
      }
    }
    if (subscription == &C6) {
      Serial.print(F("Got: "));
      Serial.println((char *)C6.lastread);
      int C6_State = atoi((char *)C6.lastread);
      if (C6_State == 1) {
        obstacleavoiding();
        Serial.println("OBSTACLE AVOIDING MODE");
      }
      else {
        moveStop();
        Serial.println("STOP");
      }
    }
    if (subscription == &C7) {
      Serial.print(F("Got: "));
      Serial.println((char *)C7.lastread);
      int C7_State = atoi((char *)C7.lastread);
      if (C7_State == 1) {
        linefollower();
        Serial.println("LINE FOLLOWER MODE");
      }
      else {
        moveStop();
        Serial.println("STOP");
      }
    }
  }

  if (obstacle_avoiding == 1) {
    obstacleavoiding();
  }

  else if (obstacle_avoiding == 2) {
    linefollower();
  }

  while (Serial.available() > 0)
  {
    val = Serial.read();
    String voice = Serial.readString();
    Serial.println(val);
    Serial.println(voice);

    if (val ==  'A') {
      moveForward();
      Serial.println("GOING FORWARD");
    }

    else if (val == 'B') {
      moveBackward();
      Serial.println("GOING BACKWARD");
    }

    else if (val == 'C') {
      turnLeft();
      Serial.println("TURNING LEFT");
    }

    else if (val == 'D') {
      turnRight();
      Serial.println("TURNING RIGHT");
    }

    else if (val == 'E') {
      obstacle_avoiding = 1;
      Serial.println("OBSTACLE AVOIDING MODE");
    }

    else if (val == 'F') {
      obstacle_avoiding = 2;
      Serial.println("LINE FOLLOWER MODE");
    }

    else if ((val == 'a') || (val == 'b') || (val == 'c') || (val == 'd') || (val == 'e') || (val == 'f')) {
      obstacle_avoiding = 0;
      moveStop();
      Serial.println("STOP");
    }
    else if (val == 'H') {
      digitalWrite(soundp, HIGH);
      Serial.println("HORN ON");
    }
    else if (val == 'h') {
      digitalWrite(soundp, LOW);
      Serial.println("HORN OFF");
    }
  }
}
