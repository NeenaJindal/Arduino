#include <NewPing.h>
#include <Servo.h>
#define TRIG_PIN 4
#define ECHO_PIN 3
#define MAX_DISTANCE 200
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

#define Motor1p  9
#define Motor1n  10
#define Motor2p  11
#define Motor2n  12

Servo myservo;
int distance = 100;
void setup() {
  myservo.attach(2);
  myservo.write(100);
  distance = readPing();
  delay(100);
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}
char val;

void loop() {
    obstacleavoiding();
}

int lookRight()
{
  myservo.write(0);
  delay(500);
  int distance = readPing();
  delay(100);
  return distance;
}

int lookLeft()
{
  myservo.write(180);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(100);
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

void obstacleavoiding()
{
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
      myservo.write(100);
      turnRight();
      delay(800);
    } 
    else {
      myservo.write(100);
      turnLeft();
      delay(800);
    }
  } 
  else {
    moveForward();
  }
  distance = readPing();
}

void moveForward() {
  Serial.println("GOING FORWARD");
  digitalWrite(Motor1p, HIGH);
  digitalWrite(Motor1n, LOW);
  digitalWrite(Motor2p, HIGH);
  digitalWrite(Motor2n, LOW);
  //  analogWrite(Motor1s, spee);
  //  analogWrite(Motor2s, spee);
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
