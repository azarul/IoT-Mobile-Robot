#include <ESP8266WiFi.h>

const char* ssid = "gulai itik";
const char* password = "itiksedap";
long counter;
String rightState = "off";
String leftState = "off";
String backwardState = "off";
String forwardState = "off";

const int pwm_right = 5;
const int dir_right = 4;
const int pwm_left = 14;
const int dir_left = 12;
WiFiServer server(80);

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

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {
  // Check if a client has connected
 // unsigned long interrupt_time = millis();
 counter++;
 Serial.print("COUNTER");
 Serial.println(counter);
  if (counter > 5){ 
    Serial.println("LOL");
      counter = 0;
  WiFiClient client = server.available();
   if (!client) {
      return;
   }

  // Wait until the client sends some data
  Serial.println("new client");
    if (!client.available()) {
      delay(1);
    }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request


  if (request.indexOf("/lefton") >= 0) {
    Serial.println("GPIO 5 on");
    forwardState = "off";
    rightState = "off";
    leftState = "on";
    backwardState = "off";
  } if (request.indexOf("/leftoff") >= 0) {
    Serial.println("GPIO 5 off");
    forwardState = "off";
    rightState = "off";
    leftState = "off";
    backwardState = "off";
  } if (request.indexOf("/backwardon") >= 0) {
    Serial.println("GPIO 4 on");
    forwardState = "off";
    rightState = "off";
    leftState = "off";
    backwardState = "on";
  } if (request.indexOf("/backwardoff") >= 0) {
    Serial.println("GPIO 4 off");
    forwardState = "off";
    rightState = "off";
    leftState = "off";
    backwardState = "off";
  } if (request.indexOf("/righton") >= 0) {
    Serial.println("GPIO 16 on");
    forwardState = "off";
    rightState = "on";
    leftState = "off";
    backwardState = "off";
  } if (request.indexOf("/rightoff") >= 0) {
    Serial.println("GPIO 16 off");
    forwardState = "off";
    rightState = "off";
    leftState = "off";
    backwardState = "off";
  } if (request.indexOf("/forwardon") >= 0) {
    Serial.println("GPIO 14 on");
    forwardState = "on";
    rightState = "off";
    leftState = "off";
    backwardState = "off";

  } if (request.indexOf("/forwardoff") >= 0) {
    Serial.println("GPIO 14 off");
    forwardState = "off";
    rightState = "off";
    leftState = "off";
    backwardState = "off";
  }
  // Set ledPin according to the request
  //digitalWrite(ledPin, value);

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
  client.println("</head>");
  client.println("<body bgcolor = \"#f7e6ec\">");
  client.println("<hr/><hr>");
  client.println("<h4><center> Esp8266 Robot Control </center></h4>");
  client.println("<hr/><hr>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("FORWARD");
  client.println("<a href=\"/forwardon\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/forwardoff\"\"><button>Turn Off </button></a><br />");
  client.println("</center>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("LEFT");
  client.println("<a href=\"/lefton\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/leftoff\"\"><button>Turn Off </button></a><br />");
  client.println("</center>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("RIGHT");
  client.println("<a href=\"/righton\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/rightoff\"\"><button>Turn Off </button></a><br />");
  client.println("</center>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("BACKWARD");
  client.println("<a href=\"/backwardon\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/backwardoff\"\"><button>Turn Off </button></a><br />");
  client.println("</center>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("<table border=\"5\">");
  client.println("<tr>");
  if (forwardState == "off") {
    client.print("<td>Light 1 is OFF</td>");
  }
  if (forwardState == "on")  {
    client.print("<td>Light 1 is ON</td>");
  }
  client.println("<br />");
  if (leftState == "off") {
    client.print("<td>Light 2 is off</td>");
  }
  if (leftState == "on") {
    client.print("<td>Light 2 is on</td>");
  }
  client.println("</tr>");
  client.println("<tr>");
  if (rightState == "off") {
    client.print("<td>Light 3 is Off</td>");
  }
  if (rightState == "on") {
    client.print("<td>Light 3 is on</td>");
  }
  if (backwardState == "off") {
    client.print("<td>Light 4 is Off</td>");
  }
  if (backwardState == "on") {
    client.print("<td>Light 4 is ON</td>");
  }
  client.println("</tr>");
  client.println("</table>");
  client.println("</center>");
  client.println("</html>");
  Serial.println("Client disonnected");
  Serial.println("");
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
    delay(8);
    digitalWrite(pwm_right, LOW);
    digitalWrite(dir_right, LOW);
    digitalWrite(pwm_left, LOW);
    digitalWrite(dir_left, LOW);
    delay(2);
  }
  if (rightState == "on") {
    Serial.println("RIGHT");
    digitalWrite(pwm_right, HIGH);
    digitalWrite(dir_right, HIGH);
    digitalWrite(pwm_left, HIGH);
    digitalWrite(dir_left, HIGH);
    delay(8);
    digitalWrite(pwm_right, LOW);
    digitalWrite(dir_right, LOW);
    digitalWrite(pwm_left, LOW);
    digitalWrite(dir_left, LOW);
    delay(2);
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
    digitalWrite(pwm_right, LOW);
    digitalWrite(dir_right, LOW);
    digitalWrite(pwm_left, LOW);
    digitalWrite(dir_left, LOW);
  }
}

