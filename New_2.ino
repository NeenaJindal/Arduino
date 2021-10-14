#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int BUTTON1 = 10;
const int BUTTON2 = 4;
const int BUTTON3 = 5;
const int BUTTON4 = 6;
const int BUTTON5 = 7;
const int BUTTON6 = 8;
const int BUTTON7 = 9;

int BUTTONstate1 = 0;
int BUTTONstate2 = 0;
int BUTTONstate3 = 0;
int BUTTONstate4 = 0;
int BUTTONstate5 = 0;
int BUTTONstate6 = 0;
int BUTTONstate7 = 0;

byte up1[] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00100,};
byte up2[] = {B00000, B00000, B00000, B00000, B00000, B00000, B00100, B01110,};
byte up3[] = {B00000, B00000, B00000, B00000, B00000, B00100, B01110, B11111,};
byte up4[] = {B00000, B00000, B00000, B00000, B00100, B01110, B11111, B11111,};
byte up5[] = {B00000, B00000, B00000, B00100, B01110, B11111, B11111, B01110,};
byte up6[] = {B00000, B00000, B00100, B01110, B11111, B11111, B01110, B01110,};
byte up7[] = {B00000, B00100, B01110, B11111, B11111, B01110, B01110, B01110,};
byte up8[] = {B00100, B01110, B11111, B11111, B01110, B01110, B01110, B01110,};

byte down1[] = {B00100, B00000, B00000, B00000, B00000, B00000, B00000, B00000,};
byte down2[] = {B01110, B00100, B00000, B00000, B00000, B00000, B00000, B00000,};
byte down3[] = {B11111, B01110, B00100, B00000, B00000, B00000, B00000, B00000,};
byte down4[] = {B11111, B11111, B01110, B00100, B00000, B00000, B00000, B00000,};
byte down5[] = {B01110, B11111, B11111, B01110, B00100, B00000, B00000, B00000,};
byte down6[] = {B01110, B01110, B11111, B11111, B01110, B00100, B00000, B00000,};
byte down7[] = {B01110, B01110, B01110, B11111, B11111, B01110, B00100, B00000,};
byte down8[] = {B01110, B01110, B01110, B01110, B11111, B11111, B01110, B00100,};

byte right1[] = {B00000, B00000, B00000, B10000, B00000, B00000, B00000, B00000,};
byte right2[] = {B00000, B00000, B10000, B11000, B10000, B00000, B00000, B00000,};
byte right3[] = {B00000, B10000, B11000, B11100, B11000, B10000, B00000, B00000,};
byte right4[] = {B00000, B11000, B11100, B11110, B11100, B11000, B00000, B00000,};
byte right5[] = {B00000, B01100, B11110, B11111, B11110, B01100, B00000, B00000,};
byte right6[] = {B00000, B00110, B11111, B11111, B11111, B00110, B00000, B00000,};
byte right7[] = {B00000, B00011, B11111, B11111, B11111, B00011, B00000, B00000,};
byte right8[] = {B00000, B00001, B11111, B11111, B11111, B00001, B00000, B00000,};

byte left1[] = {B00000, B00000, B00000, B00001, B00000, B00000, B00000, B00000,};
byte left2[] = {B00000, B00000, B00001, B00011, B00001, B00000, B00000, B00000,};
byte left3[] = {B00000, B00001, B00011, B00111, B00011, B00001, B00000, B00000,};
byte left4[] = {B00000, B00011, B00111, B01111, B00111, B00011, B00000, B00000,};
byte left5[] = {B00000, B00110, B01111, B11111, B01111, B00110, B00000, B00000,};
byte left6[] = {B00000, B01100, B11111, B11111, B11111, B01100, B00000, B00000,};
byte left7[] = {B00000, B11000, B11111, B11111, B11111, B11000, B00000, B00000,};
byte left8[] = {B00000, B10000, B11111, B11111, B11111, B10000, B00000, B00000,};
byte clean[] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000,};
byte stopp[] = {B00000, B01110, B11111, B11111, B11111, B11111, B01110, B00000,};
byte horn[] = {B00001, B00011, B00111, B11111, B11111, B00111, B00011, B00001,};

void setup()
{
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
  Serial.begin(9600);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);
  pinMode(BUTTON5, INPUT_PULLUP);
  pinMode(BUTTON6, INPUT_PULLUP);
  pinMode(BUTTON7, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
}

void loop()
{
  BUTTONstate1 = digitalRead(BUTTON1);
  BUTTONstate2 = digitalRead(BUTTON2);
  BUTTONstate3 = digitalRead(BUTTON3);
  BUTTONstate4 = digitalRead(BUTTON4);
  BUTTONstate5 = digitalRead(BUTTON5);
  BUTTONstate6 = digitalRead(BUTTON6);
  BUTTONstate7 = digitalRead(BUTTON7);

  if (BUTTONstate4 == LOW)
  {
    Serial.println("A");
    up();
  }

  else if (BUTTONstate1 == LOW)
  {
    Serial.println("B");
    down();
  }

  else if (BUTTONstate6 == LOW)
  {
    Serial.println("C");
    left();
  }

  else if (BUTTONstate5 == LOW)
  {
    Serial.println("D");
    right();
  }

  else if (BUTTONstate7 == LOW)
  {
    Serial.println("H");
    lcd.setCursor(0, 0);
    lcd.print("HORN");
    delay(500);
    lcd.clear();
    delay(500);
  }

  else if (BUTTONstate2 == LOW)
  {
    Serial.println("L");
    lcd.setCursor(6, 0);
    lcd.print("LINE");
    lcd.setCursor(1,1);
    lcd.print("FOLLOWER MODE");
    delay(500);
    lcd.clear();
    delay(500);
  }

  else if (BUTTONstate3 == LOW)
  {
    Serial.println("O");
    lcd.setCursor(4, 0);
    lcd.print("OBSTACLE");
    lcd.setCursor(1,1);
    lcd.print("AVOIDING MODE");
    delay(500);
    lcd.clear();
    delay(500);
  }
  else {
    Serial.println("S");
    lcd.setCursor(6, 0);
    lcd.print("STOP");
    delay(500);
    lcd.clear();
    delay(500);
  }
}

void up() {
  lcd.clear();
  lcd.setCursor(4, 0); lcd.print("FORWARD"); lcd.createChar(0, up1); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, up1); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, up1); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, up1); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, up2); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, up2); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, up2); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, up2); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(4, 0); lcd.print("FORWARD"); lcd.createChar(0, up2); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, up2); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, up2); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, up2); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, up2); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, up2); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, up2); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, up2); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(4, 0); lcd.print("FORWARD"); lcd.createChar(0, up3); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, up3); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, up3); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, up3); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, up3); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, up3); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, up3); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, up3); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(4, 0); lcd.print("FORWARD"); lcd.createChar(0, up4); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, up4); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, up4); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, up4); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, up4); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, up4); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, up4); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, up4); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(4, 0); lcd.print("FORWARD"); lcd.createChar(0, up5); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, up5); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, up5); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, up5); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, up5); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, up5); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, up5); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, up5); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(4, 0); lcd.print("FORWARD"); lcd.createChar(0, up6); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, up6); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, up6); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, up6); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, up6); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, up6); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, up6); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, up6); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(4, 0); lcd.print("FORWARD"); lcd.createChar(0, up7); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, up7); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, up7); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, up7); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, up7); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, up7); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, up7); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, up7); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(4, 0); lcd.print("FORWARD"); lcd.createChar(0, up8); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, up8); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, up8); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, up8); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, up8); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, up8); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, up8); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, up8); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(4, 0); lcd.print("FORWARD"); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
}
void down() {
  lcd.clear();
  lcd.setCursor(4, 0); lcd.print("BACKWARD"); lcd.createChar(0, down1); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, down1); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, down1); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, down1); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, down1); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, down1); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, down1); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, down1); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(4, 0); lcd.print("BACKWARD"); lcd.createChar(0, down2); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, down2); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, down2); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, down2); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, down2); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, down2); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, down2); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, down2); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(4, 0); lcd.print("BACKWARD"); lcd.createChar(0, down3); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, down3); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, down3); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, down3); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, down3); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, down3); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, down3); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, down3); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(4, 0); lcd.print("BACKWARD"); lcd.createChar(0, down4); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, down4); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, down4); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, down4); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, down4); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, down4); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, down4); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, down4); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(4, 0); lcd.print("BACKWARD"); lcd.createChar(0, down5); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, down5); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, down5); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, down5); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, down5); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, down5); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, down5); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, down5); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(4, 0); lcd.print("BACKWARD"); lcd.createChar(0, down6); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, down6); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, down6); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, down6); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, down6); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, down6); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, down6); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, down6); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(4, 0); lcd.print("BACKWARD"); lcd.createChar(0, down7); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, down7); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, down7); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, down7); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, down7); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, down7); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, down7); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, down7); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(4, 0); lcd.print("BACKWARD"); lcd.createChar(0, down8); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, down8); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, down8); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, down8); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, down8); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, down8); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, down8); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, down8); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(4, 0); lcd.print("BACKWARD"); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
}
void left() {
  lcd.clear();
  lcd.setCursor(6, 0); lcd.print("LEFT"); lcd.createChar(0, left1); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, left1); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, left1); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, left1); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, left1); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, left1); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, left1); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, left1); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(6, 0); lcd.print("LEFT"); lcd.createChar(0, left2); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, left2); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, left2); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, left2); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, left2); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, left2); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, left2); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, left2); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(6, 0); lcd.print("LEFT"); lcd.createChar(0, left3); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, left3); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, left3); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, left3); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, left3); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, left3); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, left3); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, left3); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(6, 0); lcd.print("LEFT"); lcd.createChar(0, left4); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, left4); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, left4); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, left4); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, left4); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, left4); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, left4); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, left4); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(6, 0); lcd.print("LEFT"); lcd.createChar(0, left5); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, left5); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, left5); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, left5); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, left5); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, left5); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, left5); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, left5); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(6, 0); lcd.print("LEFT"); lcd.createChar(0, left6); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, left6); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, left6); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, left6); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, left6); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, left6); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, left6); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, left6); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(6, 0); lcd.print("LEFT"); lcd.createChar(0, left7); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, left7); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, left7); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, left7); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, left7); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, left7); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, left7); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, left7); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(6, 0); lcd.print("LEFT"); lcd.createChar(0, left8); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, left8); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, left8); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, left8); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, left8); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, left8); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, left8); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, left8); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(6, 0); lcd.print("LEFT"); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
}
void right() {
  lcd.clear();
  lcd.setCursor(5, 0); lcd.print("RIGHT"); lcd.createChar(0, right1); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, right1); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, right1); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, right1); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, right1); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, right1); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, right1); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, right1); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(5, 0); lcd.print("RIGHT"); lcd.createChar(0, right2); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, right2); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, right2); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, right2); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, right2); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, right2); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, right2); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, right2); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(5, 0); lcd.print("RIGHT"); lcd.createChar(0, right3); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, right3); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, right3); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, right3); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, right3); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, right3); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, right3); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, right3); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(5, 0); lcd.print("RIGHT"); lcd.createChar(0, right4); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, right4); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, right4); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, right4); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, right4); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, right4); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, right4); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, right4); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(5, 0); lcd.print("RIGHT"); lcd.createChar(0, right5); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, right5); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, right5); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, right5); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, right5); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, right5); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, right5); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, right5); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(5, 0); lcd.print("RIGHT"); lcd.createChar(0, right6); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, right6); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, right6); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, right6); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, right6); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, right6); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, right6); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, right6); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(5, 0); lcd.print("RIGHT"); lcd.createChar(0, right7); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, right7); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, right7); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, right7); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, right7); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, right7); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, right7); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, right7); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(5, 0); lcd.print("RIGHT"); lcd.createChar(0, right8); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, right8); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, right8); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, right8); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, right8); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, right8); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, right8); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, right8); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
  lcd.setCursor(5, 0); lcd.print("RIGHT"); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(1, 0); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(0, 0); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(1, 1); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(0, 1); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(14, 1); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(14, 0); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(15, 1); lcd.write(byte(0)); lcd.createChar(0, clean); lcd.home(); lcd.setCursor(15, 0); lcd.write(byte(0)); delay(100);
}
