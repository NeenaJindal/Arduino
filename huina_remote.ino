const int BUTTON1 = D1;
const int BUTTON2 = D2;
const int BUTTON3 = D3;
const int BUTTON4 = D4;
const int BUTTON5 = D5;
const int BUTTON6 = D6;
const int BUTTON7 = D7;

int BUTTONstate1 = 0;
int BUTTONstate2 = 0;
int BUTTONstate3 = 0;
int BUTTONstate4 = 0;
int BUTTONstate5 = 0;
int BUTTONstate6 = 0;
int BUTTONstate7 = 0;

void setup()
{
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);
  pinMode(BUTTON5, INPUT_PULLUP);
  pinMode(BUTTON6, INPUT_PULLUP);
  pinMode(BUTTON7, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  BUTTONstate1 = digitalRead(BUTTON1);
  if (BUTTONstate1 == LOW)
  {
    Serial.println("F");
  }
  
  BUTTONstate2 = digitalRead(BUTTON2);
  if (BUTTONstate2 == LOW)
  {
    Serial.println("G");
  }

  BUTTONstate3 = digitalRead(BUTTON3);
  if (BUTTONstate3 == LOW)
  {
    Serial.println("A");
  }
  
  BUTTONstate4 = digitalRead(BUTTON4);
  if (BUTTONstate4 == LOW)
  {
    Serial.println("D");
  } 

  BUTTONstate5 = digitalRead(BUTTON5);
  if (BUTTONstate5 == LOW)
  {
    Serial.println("E");
  } 
  
  BUTTONstate6 = digitalRead(BUTTON6);
  if (BUTTONstate6 == LOW)
  {
    Serial.println("B");
  } 

  BUTTONstate7 = digitalRead(BUTTON7);
  if (BUTTONstate7 == LOW)
  {
    Serial.println("C");
  }  
}
