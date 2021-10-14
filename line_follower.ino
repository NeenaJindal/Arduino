int m1P = 4; //motor a = +
int m1N = 5; //motor a = -
int m2P = 6; //motor b = -
int m2N = 7; //motor b = +

int R = A0; //sincer R
int L = A1; //sincer L

void setup()
{
  pinMode(m1P, OUTPUT);
  pinMode(m2P, OUTPUT);
  pinMode(m1N, OUTPUT);
  pinMode(m2N, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  pinMode(L, INPUT);
  pinMode(R, INPUT);

}
void loop()
{
  if ((digitalRead(L) == 0) && (digitalRead(R) == 0)) {
    forword();
  }

  if ((digitalRead(L) == 1) && (digitalRead(R) == 0)) {
    turnRight();
  }

  if ((digitalRead(L) == 0) && (digitalRead(R) == 1)) {
    turnLeft();
  }
  if ((digitalRead(L) == 1) && (digitalRead(R) == 1)) {
    Stop();
  }
  Serial.print(digitalRead(L));
  Serial.println("\n");
  Serial.print(digitalRead(R));
  Serial.println("\n"); 
 }

void forword() {
  digitalWrite(m1P, HIGH);
  digitalWrite(m1N, LOW);
  digitalWrite(m2P, HIGH);
  digitalWrite(m2N, LOW);
}


void turnRight() {
  digitalWrite(m1P, LOW);
  digitalWrite(m1N, HIGH);
  digitalWrite(m2P, HIGH);
  digitalWrite(m2N, LOW);
}

void turnLeft() {
  digitalWrite(m1P, HIGH);
  digitalWrite(m1N, LOW);
  digitalWrite(m2P, LOW);
  digitalWrite(m2N, HIGH);
}

void Stop() {
  digitalWrite(m1P, LOW);
  digitalWrite(m1N, LOW);
  digitalWrite(m2P, LOW);
  digitalWrite(m2N, LOW);
}
