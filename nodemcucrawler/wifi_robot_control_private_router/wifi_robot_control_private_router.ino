// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "gulai itik";
const char* password = "itiksedap";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String rightState = "off";
String leftState = "off";
String backwardState = "off";
String forwardState = "off";
String stopState = "off";

// Assign output variables to GPIO pins
const int pwm_right = 5;
const int dir_right = 4;
const int pwm_left = 0;
const int dir_left = 2;

void setup() {
  Serial.begin(115200);
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

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            // turns the GPIOs on and off
            if (header.indexOf("/5/on") >= 0) {
              Serial.println("GPIO 5 on");
              forwardState = "off";
              rightState = "off";
              leftState = "on";
              stopState = "off";
              backwardState = "off";
            } else if (header.indexOf("/5/off") >= 0) {
              Serial.println("GPIO 5 off");
              forwardState = "off";
              rightState = "off";
              leftState = "off";
              stopState = "off";
              backwardState = "off";
            } else if (header.indexOf("/4/on") >= 0) {
              Serial.println("GPIO 4 on");
              forwardState = "off";
              rightState = "off";
              leftState = "off";
              stopState = "off";
              backwardState = "on";
            } else if (header.indexOf("/4/off") >= 0) {
              Serial.println("GPIO 4 off");
              forwardState = "off";
              rightState = "off";
              leftState = "off";
              stopState = "off";
              backwardState = "off";
            } else if (header.indexOf("/16/on") >= 0) {
              Serial.println("GPIO 16 on");
              forwardState = "off";
              rightState = "on";
              leftState = "off";
              stopState = "off";
              backwardState = "off";
            } else if (header.indexOf("/16/off") >= 0) {
              Serial.println("GPIO 16 off");
              forwardState = "off";
              rightState = "off";
              leftState = "off";
              stopState = "off";
              backwardState = "off";
            } else if (header.indexOf("/14/on") >= 0) {
              Serial.println("GPIO 14 on");
              forwardState = "on";
              rightState = "off";
              leftState = "off";
              stopState = "off";
              backwardState = "off"; forwardState = "on";
            } else if (header.indexOf("/14/off") >= 0) {
              Serial.println("GPIO 14 off");
              forwardState = "off";
              rightState = "off";
              leftState = "off";
              stopState = "off";
              backwardState = "off";
            } else if (header.indexOf("/12/on") >= 0) {
              Serial.println("GPIO 12 on");
              forwardState = "off";
              rightState = "off";
              leftState = "off";
              stopState = "on";
              backwardState = "off";
            } else if (header.indexOf("/12/off") >= 0) {
              Serial.println("GPIO 12 off");
              forwardState = "off";
              rightState = "off";
              leftState = "off";
              stopState = "off";
              backwardState = "off";
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".grid {display: inline-flex; flex-flow: row wrap;}");
            client.println(".up, .down {flex: 0 0 100%; text-align: center;}");
            client.println(".left, .right {flex: 1 0 1%; display: flex;}");
            client.println(".left {justify-content: flex-end;}");
            client.println(".right {justify-content: flex-start;}");
            client.println(".ok {}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            // Web Page Heading
            client.println("<body><h1>NADIBOT V2.5</h1>");
            client.println("<div class=\"grid\">");
            // If the leftState is off, it displays the ON button
            if (forwardState == "off") {
              client.println("<form action=\"/keyboard/\" class=\"up\">");
              client.println("<a href=\"/14/on\"><button class=\"button\">UP</button></a>");
              client.println("</form>");
            }
            if (forwardState == "on") {
              client.println("<form action=\"/keyboard/\" class=\"up\">");
              client.println("<a href=\"/14/off\"><button class=\"button button2\">UP</button></a>");
              client.println("</form>");
              digitalWrite(pwm_right, HIGH);
              digitalWrite(dir_right, LOW);
              digitalWrite(pwm_left, HIGH);
              digitalWrite(dir_left, HIGH);
            }
            if (leftState == "off") {
              client.println("<form action=\"/keyboard/\" class=\"left\">");
              client.println("<a href=\"/5/on\"><button class=\"button\">Left</button></a>");
              client.println("</form>");
            }
            if (leftState == "on") {
              client.println("<form action=\"/keyboard/\" class=\"left\">");
              client.println("<a href=\"/5/off\"><button class=\"button button2\">Left</button></a>");
              client.println("</form>");
              digitalWrite(pwm_right, HIGH);
              digitalWrite(dir_right, LOW);
              digitalWrite(pwm_left, HIGH);
              digitalWrite(dir_left, LOW);
            }
            if (stopState == "off") {
              client.println("<form action=\"/keyboard/\" class=\"ok\">");
              client.println("<a href=\"/12/on\"><button class=\"button\">STOP</button></a>");
              client.println("</form>");
            }
            if (stopState == "on") {
              client.println("<form action=\"/keyboard/\" class=\"ok\">");
              client.println("<a href=\"/12/off\"><button class=\"button button2\">STOP</button></a>");
              client.println("</form>");
              digitalWrite(pwm_right, LOW);
              digitalWrite(dir_right, LOW);
              digitalWrite(pwm_left, LOW);
              digitalWrite(dir_left, LOW);
            }
            if (rightState == "off") {
              client.println("<form action=\"/keyboard/\" class=\"right\">");
              client.println("<a href=\"/16/on\"><button class=\"button\">RIGHT</button></a>");
              client.println("</form>");
            }
            if (rightState == "on") {
              client.println("<form action=\"/keyboard/\" class=\"right\">");
              client.println("<a href=\"/16/off\"><button class=\"button button2\">RIGHT</button></a>");
              client.println("</form>");
              digitalWrite(pwm_right, HIGH);
              digitalWrite(dir_right, HIGH);
              digitalWrite(pwm_left, HIGH);
              digitalWrite(dir_left, HIGH);
            }
            if (backwardState == "off") {
              client.println("<form action=\"/keyboard/\" class=\"down\">");
              client.println("<a href=\"/4/on\"><button class=\"button\">DOWN</button></a>");
              client.println("</form>");
            }
            if (backwardState == "on") {
              client.println("<form action=\"/keyboard/\" class=\"down\">");
              client.println("<a href=\"/4/off\"><button class=\"button button2\">DOWN</button></a>");
              client.println("</form>");
              digitalWrite(pwm_right, HIGH);
              digitalWrite(dir_right, HIGH);
              digitalWrite(pwm_left, HIGH);
              digitalWrite(dir_left, LOW);
            }
            client.println("</div></body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
