// arduino code

#include <NewPing.h>
#include <Servo.h>
Servo myServo;

#define servo    2
#define horn     5
#define rightir  6
#define leftir   7
#define Motor1s  8
#define Motor1p  9
#define Motor1n  10
#define Motor2p  11
#define Motor2n  12
#define Motor2s  13
#define trig     4
#define echo     3
#define max_dis  200

NewPing sonar(trig, echo, max_dis);

char val;
int L = 1;
int R = 1;
int speed1 = 0;
int speed2 = 0;
int distance = 100;
int spee;
int pos = 95;
int mode;

void setup()
{
  Serial.begin(9600);
  myServo.attach(servo);
  myServo.write(pos);
  pinMode(Motor1s, OUTPUT);
  pinMode(Motor1p, OUTPUT);
  pinMode(Motor1n, OUTPUT);
  pinMode(Motor2p, OUTPUT);
  pinMode(Motor2n, OUTPUT);
  pinMode(Motor2s, OUTPUT);
  pinMode(horn, OUTPUT);
  pinMode(rightir, INPUT);
  pinMode(leftir, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  distance = readPing();
  delay(100);
}

void moveForward() {
  Serial.println("GOING FORWARD");
  digitalWrite(Motor1p, HIGH);
  digitalWrite(Motor1n, LOW);
  digitalWrite(Motor2p, HIGH);
  digitalWrite(Motor2n, LOW);
    digitalWrite(Motor1s, HIGH);
    digitalWrite(Motor2s, HIGH);
}

void moveBackward() {
  Serial.println("GOING BACKWARD");
  digitalWrite(Motor1p, LOW);
  digitalWrite(Motor1n, HIGH);
  digitalWrite(Motor2p, LOW);
  digitalWrite(Motor2n, HIGH);
  //  analogWrite(Motor1s, spee);
  //  analogWrite(Motor2s, spee);
}

void turnLeft() {
  Serial.println("TURNING LEFT");
  digitalWrite(Motor1p, LOW);
  digitalWrite(Motor1n, HIGH);
  digitalWrite(Motor2p, HIGH);
  digitalWrite(Motor2n, LOW);
  //  analogWrite(Motor1s, spee);
  //  analogWrite(Motor2s, spee);
}

void turnRight() {
  Serial.println("TURNING RIGHT");
  digitalWrite(Motor1p, HIGH);
  digitalWrite(Motor1n, LOW);
  digitalWrite(Motor2p, LOW);
  digitalWrite(Motor2n, HIGH);
  //  analogWrite(Motor1s, spee);
  //  analogWrite(Motor2s, spee);
}

void moveStop() {
  Serial.println("STOP");
  digitalWrite(Motor1p, LOW);
  digitalWrite(Motor1n, LOW);
  digitalWrite(Motor2p, LOW);
  digitalWrite(Motor2n, LOW);
  //  analogWrite(Motor1s, spee);
  //  analogWrite(Motor2s, spee);
}

int lookRight()
{
  myServo.write(0);
  delay(500);
  int distance = readPing();
  delay(100);
  return distance;
}

int lookLeft()
{
  myServo.write(180);
  delay(500);
  int distance = readPing();
  delay(100);
  myServo.write(pos);
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

void lineFollower() {
  R = digitalRead(rightir);
  L = digitalRead(leftir);
  Serial.println("RIGHT = ");
  Serial.println(R);
  Serial.println("LEFT = ");
  Serial.println(L);
  delay(100);
  if (R == 1 && L == 1) {
    moveStop();
  }
  else if (R == 0 && L == 0) {
    moveForward();
  }
  else if (R == 1 && L == 0) {
    turnLeft();
  }
  else if (R == 0 && L == 1) {
    turnRight();
  }
}

void obstacleAvoiding() {
  int distanceR = 0;
  int distanceL =  0;
  delay(40);
  if (distance <= 20)
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
      myServo.write(pos);
      turnRight();
      delay(800);
    }
    else {
      myServo.write(pos);
      turnLeft();
      delay(800);
    }
  }
  else {
    moveForward();
  }
  distance = readPing();
}

void loop()
{
  while (Serial.available() > 0)
  {
    val = Serial.read();
    Serial.println(val);
    if (val == 'F') {
      mode = 4;
    }
    else if (val == 'B') {
      mode = 5;
    }
    else if (val == 'L') {
     mode = 6;
    }
    else if (val == 'R') {
      mode = 7;
    }
    else if (val == 'S') {
      mode = 3;
    }
    else if (val == 'H') {
      Serial.println("HORN ON");
      digitalWrite(horn, HIGH);
    }
    else if (val == 'h') {
      Serial.println("HORN OFF");
      digitalWrite(horn, LOW);
    }
    else if (val == 'l') {
      Serial.println("LINE FOLLOWER MODE");
      mode = 1;
    }
    else if (val == 'O') {
      Serial.println("OBSTACLE AVOIDING MODE");
      mode = 2;
    }

    //speeds start
    else if (val == '0') {
      analogWrite(Motor1s, 0);
      analogWrite(Motor2s, 0);
    }
    else if (val == '1') {
      analogWrite(Motor1s, 28);
      analogWrite(Motor2s, 28);
    }
    else if (val == '2') {
      analogWrite(Motor1s, 56);
      analogWrite(Motor2s, 56);
    }
    else if (val == '3') {
      analogWrite(Motor1s, 84);
      analogWrite(Motor2s, 84);
    }
    else if (val == '4') {
      analogWrite(Motor1s, 112);
      analogWrite(Motor2s, 112);
    }
    else if (val == '5') {
      analogWrite(Motor1s, 140);
      analogWrite(Motor2s, 140);
    }
    else if (val == '6') {
      analogWrite(Motor1s, 168);
      analogWrite(Motor2s, 168);
    }
    else if (val == '7') {
      analogWrite(Motor1s, 196);
      analogWrite(Motor2s, 196);
    }
    else if (val == '8') {
      analogWrite(Motor1s, 224);
      analogWrite(Motor2s, 224);
    }
    else if (val == '9') {
      analogWrite(Motor1s, 252);
      analogWrite(Motor2s, 252);
    }
  }
  if (mode == 1){
    lineFollower();
  }
  else if (mode == 2){
    obstacleAvoiding();
  }
  else if (mode == 3){
    moveStop();
  }
  else if (mode == 4){
    moveForward();
  }
  else if (mode == 5){
    moveBackward();
  }
  else if (mode == 6){
    turnRight();
  }
  else if (mode == 7){
    turnLeft();
  }
}
