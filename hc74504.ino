int latchPin = 5;
int clkPin = 6;
int dataPin = 4;

byte LED = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clkPin, OUTPUT);
}

void loop() 
{
  int i=0;
  LED = 0;
  shiftLED();
  delay(500);
  for (i = 0; i < 8; i++)
  {
    bitSet(LED, i);
    Serial.println(LED);
    shiftLED();
    delay(500);
  }
}

void shiftLED()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clkPin, MSBFIRST, LED);
   digitalWrite(latchPin, HIGH);
}
