#define M1 4
#define E1 5
#define M2 7
#define E2 6

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(M1, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(E2, OUTPUT);
}

void loop() {
char in = Serial.read();
Serial.println(in);
if(in == 'A'){
  digitalWrite(E1, HIGH);
  digitalWrite(M1, HIGH);
  digitalWrite(E2, HIGH);
  digitalWrite(M2, HIGH);
  delay(100);
}
if(in == 'B'){
  digitalWrite(E1, HIGH);
  digitalWrite(M1, LOW);
  digitalWrite(E2, HIGH);
  digitalWrite(M2, HIGH);
  delay(100);
}
if(in == 'C'){
  digitalWrite(E1, HIGH);
  digitalWrite(M1, HIGH);
  digitalWrite(E2, HIGH);
  digitalWrite(M2, LOW);
  delay(100);
}
if(in == 'D'){
   digitalWrite(E1, HIGH);
  digitalWrite(M1, LOW);
  digitalWrite(E2, HIGH);
  digitalWrite(M2, LOW);
  delay(100);
}
if(in == 'Z'){
   digitalWrite(E1, LOW);
  digitalWrite(M1, LOW);
  digitalWrite(E2, LOW);
  digitalWrite(M2, LOW);
  delay(100);
}
}
