#include <ESP8266WiFi.h>
#include <NewPing.h>
#include <Servo.h>

Servo myservo;

#define M1_p D0
#define M1_n D1
#define M2_p D2
#define M2_n D3

#define R D4
#define L D5

#define TRIG_PIN D6
#define ECHO_PIN A0
#define MAX_DISTANCE 200
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

#define soundp 2

int obstacle_avoiding = 0;
int vall = 0;
int valr = 0;
int distance = 100;
char val;
long duration;

void setup() {
  Serial.begin(9600);
  WiFi.begin("NIKUNJ", "NIKUNJ987");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  
  myservo.attach(D7);
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
}

void loop() {
  if (obstacle_avoiding == 1) {
    obstacleavoiding();
  }

  else if (obstacle_avoiding == 2) {
    linefollower();
  }

  else if (obstacle_avoiding == 3) {
    obstacle_overcome();
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

    else  if (val == 'G') {
      obstacle_avoiding = 3;
      Serial.println("OBSTACLE OVERCOME MODE");
    }
    
    else if ((val == 'a') || (val == 'b') || (val == 'c') || (val == 'd') || (val == 'e') || (val == 'f') || (val == 'g')) {
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
void obstacle_overcome()
{
  int distanceR = 0;
  int distanceL =  0;
  delay(40);

  if (distance <= 15)
  {
    moveStop();
    delay(200);
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
      moveForward();
      delay(1500);
      turnLeft();
      delay(1000);
      moveForward();
      delay(3000);
      turnLeft();
      delay(1000);
      moveForward();
      delay(1500);
      turnRight();
      delay(1000);
    }
    else {
      myservo.write(115);
      turnLeft();
      delay(1000);
      moveForward();
      delay(1500);
      turnRight();
      delay(1000);
      moveForward();
      delay(3000);
      turnRight();
      delay(1000);
      moveForward();
      delay(1500);
      turnLeft();
      delay(1000);
    }
  }
  else {
    moveForward();
  }
  distance = readPing();
}
