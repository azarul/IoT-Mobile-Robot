#define M1 4
#define E1 5
void setup() {
  // put your setup code here, to run once:
  pinMode(M1, OUTPUT);
  pinMode(E1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(E1, HIGH);
  digitalWrite(M1, HIGH);
  delay(2000);
  digitalWrite(E1, LOW);
  digitalWrite(M1, LOW);
  delay(1000);
  digitalWrite(E1, HIGH);
  digitalWrite(M1, LOW);
  delay(2000);
  digitalWrite(E1, LOW);
  digitalWrite(M1, LOW);
  delay(1000);
}
