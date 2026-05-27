#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "TECNO SPARK 10 5G";
const char* password = "22222222";

WiFiServer server(80);

int LED_PIN = 2;


void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(16, OUTPUT);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  
}

int value = 0;

void loop() {
WiFiClient client = server.available();

  if (client)
  {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);
        
        if (c == '\n')
        {
          if (currentLine.length() == 0)
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.println("<h1>ESP32 Remote</h1>");
            client.println("<a href=\"/H\"><button>ON</button></a> <a href=\"/L\"><button>OFF</button></a>");

            break;
          } else
          {
            currentLine = "";
          }
        } else if (c != '\r')
        {
          currentLine += c;
        }
        
        if (currentLine.endsWith("GET /H"))
        {
          digitalWrite(LED_PIN, HIGH);
          digitalWrite(4, HIGH);
          digitalWrite(16, HIGH);
        }
        if (currentLine.endsWith("GET /L"))
        {
          digitalWrite(LED_PIN, LOW);
          digitalWrite(4, LOW);
          digitalWrite(16, LOW);
        }
      }     
    }   
    client.stop();
  } 
}