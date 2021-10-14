#define x A0
#define y A1

int x_val;
int y_val;

int x_val2;
int y_val2;

void setup() {
  // put your setup code here, to run once:
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  Serial.begin(9600);
  x_val2 = analogRead(x);
  y_val2 = analogRead(y);
}

void loop()
{
  // put your main code here, to run repeatedly:
  x_val = analogRead(x);
  y_val = analogRead(y);

  int x_axis = x_val - x_val2;
  int y_axis = y_val - y_val2;

  if (y_axis >= 50)
  {
    Serial.println("A");
  }
  else if (y_axis <= -50)
  {
    Serial.println("B");
  }
  else if (x_axis >= 50)
  {
    Serial.println("C");
  }
  else if (x_axis <= -50)
  {
    Serial.println("D");
  }
  else
  {
    Serial.println("S");
  }
  delay(100);
}
