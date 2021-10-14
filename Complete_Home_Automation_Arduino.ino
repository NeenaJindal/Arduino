void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  while (Serial.available() > 0)
  {
    char val = Serial.read();
    Serial.println(val);
    if (val == 'A') {
      digitalWrite(2, LOW);
      Serial.println("SWITCH 1 ON");
    }
    else if (val == 'a') {
      digitalWrite(2, HIGH);
      Serial.println("SWITCH 1 OFF");
    }
    else if (val == 'B') {
      digitalWrite(4, LOW);
      Serial.println("SWITCH 2 ON");
    }
    else if (val == 'b') {
      digitalWrite(4, HIGH);
      Serial.println("SWITCH 2 OFF");
    }
    else if (val == 'C') {
      digitalWrite(5, LOW);
      Serial.println("SWITCH 3 ON");
    }
    else if (val == 'c') {
      digitalWrite(5, HIGH);
      Serial.println("SWITCH 3 OFF");
    }
    else if (val == 'D') {
      digitalWrite(6, LOW);
      Serial.println("SWITCH 4 ON");
    }
    else if (val == 'd') {
      digitalWrite(6, HIGH);
      Serial.println("SWITCH 4 OFF");
    }
  }
}
