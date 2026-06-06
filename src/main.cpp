#include<Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "TECNO SPARK 10 5G";
const char* password = "33333333";

// Assign output variables to GPIO pins
const int output16 = 16;
const int output04 = 4;
String output16State = "off";
String output04State = "off";

// Create a web server object
WebServer server(80);

// Function to handle the root URL and show the current states
void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<link rel=\"icon\" href=\"data:,\">";
  html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
  html += ".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
  html += ".button2 { background-color: #ff0000; }</style></head>";
  html += "<body><h1>ESP32 Web Server</h1>";

  // Display GPIO 16 controls
  html += "<p>GPIO 16 - State " + output16State + "</p>";
  if (output16State == "off") {
    html += "<p><a href=\"/16/on\"><button class=\"button\">ON</button></a></p>";
  } else {
    html += "<p><a href=\"/16/off\"><button class=\"button button2\">OFF</button></a></p>";
  }

  // Display GPIO 04 controls
  html += "<p>GPIO 04 - State " + output04State + "</p>";
  if (output04State == "off") {
    html += "<p><a href=\"/04/on\"><button class=\"button\">ON</button></a></p>";
  } else {
    html += "<p><a href=\"/04/off\"><button class=\"button button2\">OFF</button></a></p>";
  }

  html += "</body></html>";
  server.send(200, "text/html", html);
}

// Function to handle turning GPIO 16 on
void handleGPIO16On() {
  output16State = "on";
  digitalWrite(output16, HIGH);
  handleRoot();
}

// Function to handle turning GPIO 16 off
void handleGPIO16Off() {
  output16State = "off";
  digitalWrite(output16, LOW);
  handleRoot();
}

// Function to handle turning GPIO 04 on
void handleGPIO04On() {
  output04State = "on";
  digitalWrite(output04, HIGH);
  handleRoot();
}

// Function to handle turning GPIO 04 off
void handleGPIO04Off() {
  output04State = "off";
  digitalWrite(output04, LOW);
  handleRoot();
}

void setup() {
  Serial.begin(115200);

  // Initialize the output variables as outputs
  pinMode(output16, OUTPUT);
  pinMode(output04, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output16, LOW);
  digitalWrite(output04, LOW);

  // Connect to Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Set up the web server to handle different routes
  server.on("/", handleRoot);
  server.on("/16/on", handleGPIO16On);
  server.on("/16/off", handleGPIO16Off);
  server.on("/04/on", handleGPIO04On);
  server.on("/04/off", handleGPIO04Off);

  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}