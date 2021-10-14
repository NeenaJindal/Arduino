#include <NewPing.h>
#include <Servo.h>
int obstacle_avoiding = 0;
#define TRIG_PIN A3
#define ECHO_PIN A2
#define MAX_DISTANCE 200
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
int M1_p = 4;
int M1_n = 5;
int M2_p = 6;
int M2_n = 7;
Servo myservo;
int R = A0; //sincer R
int L = A1; //sincer L
boolean goesForward = false;
int distance = 100;
void setup() {
  myservo.attach(11);
  myservo.write(115);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  distance = readPing();
  delay(100);
  Serial.begin(9600);
  pinMode(L, INPUT);
  pinMode(R, INPUT);
  Serial.begin(9600);
}
char val;
void loop() {
  if (obstacle_avoiding == 1)
  {
    obstacleavoiding();
  }
  else if (obstacle_avoiding == 2)
  {
    linefollower();
  }
  else if (obstacle_avoiding == 3)
  {
    obstacle_overcome();
  }
  else if (obstacle_avoiding == 0)
  {
    while (Serial.available() > 0)
    {
      val = Serial.read();
      Serial.println(val);
      if (val ==  'A')
      {
        moveForward();
      }
      else if (val == 'B')
      {
        moveBackward();
      }
      else if (val == 'C')
      {
        turnLeft();
      }
      else if (val == 'D')
      {
        turnRight();
      }
      else if ((val == 'a') || (val == 'b') || (val == 'c') || (val == 'd'))
      {
        moveStop();
      }
      else if (val == 'E')
      {
        obstacle_avoiding = 1;
      }
      else if (val == 'F')
      {
        obstacle_avoiding = 2;
      }
      else  if (val == 'G')
      {
        obstacle_avoiding = 3;
      }
      else if ((val == 'e') || (val == 'f') || (val =='g'))
      {
        obstacle_avoiding = 0;
      }
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
int moveForward1() {
  digitalWrite(M1_p, HIGH);
  digitalWrite(M2_p, HIGH);
  digitalWrite(M1_n, LOW);
  digitalWrite(M2_n, LOW);
  return readPing();
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
void obstacleavoiding()
{
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
      delay(800);
    } else
    {
      myservo.write(115);
      turnLeft();
      delay(800);
    }
  } else
  {
    moveForward();
  }
  distance = readPing();
}
void linefollower()
{
  if ((digitalRead(L) == 0) && (digitalRead(R) == 0)) {
    moveForward();
  }

  if ((digitalRead(L) == 1) && (digitalRead(R) == 0)) {
    turnLeft();
  }

  if ((digitalRead(L) == 0) && (digitalRead(R) == 1)) {
    turnRight();
  }
  if ((digitalRead(L) == 1) && (digitalRead(R) == 1)) {
    moveStop();
  }
  Serial.print(digitalRead(L));
  Serial.println("\n");
  Serial.print(digitalRead(R));
  Serial.println("\n");
}
void obstacle_overcome()
{
  int distanceR1 = 0;
  int distanceL1 =  0;
  int dist, dist1, dist2, dist3;
  delay(40);

  if (distance <= 15)
  {
    moveStop();
    delay(100);
    moveBackward();
    delay(1000);
    moveStop();
    delay(200);
    distanceR1 = lookRight();
    delay(200);
    distanceL1 = lookLeft();
    delay(200);

    if (distanceR1 >= distanceL1)
    {
      myservo.write(170);
      turnRight();
      delay(800);
      dist2 = readPing();
      dist3 = moveForward1();
      while (dist1 < dist)
      {
        dist3 = moveForward1();
      }
      turnLeft();
      delay(800);
      dist2 = readPing();
      dist3 = moveForward1();
      while (dist3 < dist2 + 20);
      {
        dist3 = moveForward1();
      }
      turnLeft();
      delay(800);
      dist2 = readPing();
      dist3 = moveForward1();
      while (dist3 < dist2 + 20);
      {
        dist3 = moveForward1();
      }
      turnRight();
      delay(800);
    }
    else
    {
      myservo.write(50);
      turnLeft();
      delay(800);
      dist = readPing();
      dist1 = moveForward1();
      while (dist1 < dist)
      {
        dist1 = moveForward1();
      }
      turnRight();
      delay(800);
      dist = readPing();
      dist1 = moveForward1();
      while (dist1 < dist + 20);
      {
        dist1 = moveForward1();
      }
      turnRight();
      delay(800);
      dist = readPing();
      dist1 = moveForward1();
      while (dist1 < dist + 20);
      {
        dist1 = moveForward1();
      }
      turnLeft();
      delay(800);
    }
  }
  else
  {
    moveForward();
  }
  distance = readPing();
}
