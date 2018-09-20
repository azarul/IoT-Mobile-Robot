String rightState = "off";
String leftState = "off";
String backwardState = "off";
String forwardState = "off";

const int pwm_right = 5;
const int dir_right = 4;
const int pwm_left = 14;
const int dir_left = 12;

void setup() {
  Serial.begin(115200);
  delay(10);
  // Initialize the output variables as outputs
  pinMode(pwm_right, OUTPUT);
  pinMode(dir_right, OUTPUT);
  pinMode(pwm_left, OUTPUT);
  pinMode(dir_left, OUTPUT);
  // Set outputs to LOW
  digitalWrite(pwm_right, LOW);
  digitalWrite(dir_right, LOW);
  digitalWrite(pwm_left, LOW);
  digitalWrite(dir_left, LOW);
}

void loop() {
  char c = Serial.read();
  if (c == 'A') {
    forwardState = "off";
    rightState = "off";
    leftState = "on";
    backwardState = "off";
  } if (c == 'B') {
    forwardState = "off";
    rightState = "off";
    leftState = "off";
    backwardState = "off";
  } if (c == 'C') {
    forwardState = "off";
    rightState = "off";
    leftState = "off";
    backwardState = "on";
  } if (c == 'D') {
    forwardState = "off";
    rightState = "on";
    leftState = "off";
    backwardState = "off";
  } if (c == 'E') {
    forwardState = "on";
    rightState = "off";
    leftState = "off";
    backwardState = "off";
  } 
  if (forwardState == "on")  {
    Serial.println("FORWARD");
    digitalWrite(pwm_right, HIGH);
    digitalWrite(dir_right, LOW);
    digitalWrite(pwm_left, HIGH);
    digitalWrite(dir_left, HIGH);
    delay(2);
    digitalWrite(pwm_right, LOW);
    digitalWrite(dir_right, LOW);
    digitalWrite(pwm_left, LOW);
    digitalWrite(dir_left, LOW);
    delay(8);
  }
  if (leftState == "on") {
    Serial.println("LEFT");
    digitalWrite(pwm_right, HIGH);
    digitalWrite(dir_right, LOW);
    digitalWrite(pwm_left, HIGH);
    digitalWrite(dir_left, LOW);
    delay(2);
    digitalWrite(pwm_right, LOW);
    digitalWrite(dir_right, LOW);
    digitalWrite(pwm_left, LOW);
    digitalWrite(dir_left, LOW);
    delay(8);
  }
  if (rightState == "on") {
    Serial.println("RIGHT");
    digitalWrite(pwm_right, HIGH);
    digitalWrite(dir_right, HIGH);
    digitalWrite(pwm_left, HIGH);
    digitalWrite(dir_left, HIGH);
    delay(2);
    digitalWrite(pwm_right, LOW);
    digitalWrite(dir_right, LOW);
    digitalWrite(pwm_left, LOW);
    digitalWrite(dir_left, LOW);
    delay(8);
  }
  if (backwardState == "on") {
    Serial.println("BACKWARD");
    digitalWrite(pwm_right, HIGH);
    digitalWrite(dir_right, HIGH);
    digitalWrite(pwm_left, HIGH);
    digitalWrite(dir_left, LOW);
    delay(2);
    digitalWrite(pwm_right, LOW);
    digitalWrite(dir_right, LOW);
    digitalWrite(pwm_left, LOW);
    digitalWrite(dir_left, LOW);
    delay(8);
  }
  if (forwardState == "off" && leftState == "off" && rightState == "off" && backwardState == "off") {
    Serial.println("STOP");
    digitalWrite(pwm_right, LOW);
    digitalWrite(dir_right, LOW);
    digitalWrite(pwm_left, LOW);
    digitalWrite(dir_left, LOW);
  }
}
