int S_A = 8;  //speed motor a
int M_A1 = 9; //motor a = +
int M_A2 = 10; //motor a = -
int M_B1 = 11; //motor b = -
int M_B2 = 12; //motor b = +
int S_B = 13;  //speed motor b
 
int R_S = 6; //sincer R
int L_S = 7; //sincer L
 
void setup() 
{
pinMode(M_B1, OUTPUT);
pinMode(M_B2, OUTPUT);
pinMode(M_A1, OUTPUT);
pinMode(M_A2, OUTPUT);
pinMode(S_B, OUTPUT);
pinMode(S_A, OUTPUT);
 
pinMode(L_S, INPUT);
pinMode(R_S, INPUT); 
}
void loop()
{  
if ((digitalRead(L_S) == 0)&&(digitalRead(R_S) == 0)){forward();}
if ((digitalRead(L_S) == 1)&&(digitalRead(R_S) == 0)){turnLeft();}
if ((digitalRead(L_S) == 0)&&(digitalRead(R_S) == 1)){turnRight();}
if ((digitalRead(L_S) == 1)&&(digitalRead(R_S) == 1)){Stop();}
}
 
void forward(){
digitalWrite(M_A1, HIGH);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW);  
analogWrite(S_A, 80); 
analogWrite(S_B, 80);
}
 
 
void turnRight(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW);
analogWrite(S_A, 100); 
analogWrite(S_B, 100);
}
 
void turnLeft(){
digitalWrite(M_A1, HIGH);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, LOW);
analogWrite(S_A, 100); 
analogWrite(S_B, 100);
}
 
void Stop(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, LOW);
}
