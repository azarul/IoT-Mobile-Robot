const int pwm_right = 5;
const int dir_right = 4;

void setup() {
  Serial.begin(115200);
  delay(10);
  // Initialize the output variables as outputs
  pinMode(pwm_right, OUTPUT);
  pinMode(dir_right, OUTPUT);
  // Set outputs to LOW
  digitalWrite(pwm_right, LOW);
  digitalWrite(dir_right, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pwm_right, HIGH);
  digitalWrite(dir_right, LOW);
  delay(2000);
  digitalWrite(pwm_right, HIGH);
  digitalWrite(dir_right, HIGH);
  delay(2000);
  digitalWrite(pwm_right, LOW);
  digitalWrite(dir_right, LOW);
  delay(2000);
}
