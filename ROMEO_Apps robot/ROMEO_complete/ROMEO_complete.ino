#include <SoftwareSerial.h>
#define M1 4
#define E1 5
#define M2 7
#define E2 6

SoftwareSerial blue(10,11);

void setup() {
  // put your setup code here, to run once:
  blue.begin(9600);
  Serial.begin(9600);
  pinMode(M1, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(E2, OUTPUT);
}

void loop() {
char in = blue.read();
Serial.println(in);
if(in == 'a'){
  digitalWrite(E1, HIGH);
  digitalWrite(M1, HIGH);
  digitalWrite(E2, HIGH);
  digitalWrite(M2, HIGH);
  delay(100);
}
if(in == 'b'){
  digitalWrite(E1, HIGH);
  digitalWrite(M1, LOW);
  digitalWrite(E2, HIGH);
  digitalWrite(M2, HIGH);
  delay(100);
}
if(in == 'c'){
  digitalWrite(E1, HIGH);
  digitalWrite(M1, HIGH);
  digitalWrite(E2, HIGH);
  digitalWrite(M2, LOW);
  delay(100);
}
if(in == 'd'){
   digitalWrite(E1, HIGH);
  digitalWrite(M1, LOW);
  digitalWrite(E2, HIGH);
  digitalWrite(M2, LOW);
  delay(100);
}
if(in == 'z'){
   digitalWrite(E1, LOW);
  digitalWrite(M1, LOW);
  digitalWrite(E2, LOW);
  digitalWrite(M2, LOW);
  delay(100);
}
}
