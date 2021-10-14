#define m1 D0
#define m2 D1
#define m3 D2
#define m4 D3

#define soundp D8

char val;
void setup()
{
  Serial.begin(9600);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(soundp, OUTPUT);
}

void loop()
{
  while (Serial.available() > 0)
  {
    val = Serial.read();
    Serial.println(val);
    if (val == 'A') {
      moveForward();
    }
    else if (val == 'B') {
      moveBackward();
    }
    else if (val == 'C') {
      turnLeft();
    }
    else if (val == 'D') {
      turnRight();
    }
    else {
      moveStop();
    }
  }
}
void moveStop() {
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
}
void moveForward() {
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
}
void moveBackward() {
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);
}
void turnRight() {
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
}
void turnLeft() {
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);
}
