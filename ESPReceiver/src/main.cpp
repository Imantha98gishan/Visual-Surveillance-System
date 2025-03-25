#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "Dialog 4G 071";
const char* password = "334Cc9e3";

String data;

WiFiServer server(80);

void setup() {
  pinMode(2,OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.print("Server begin");
}

void loop() {
  WiFiClient client = server.available();
  
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        data = client.readStringUntil('\n'); 
        Serial.println("Received from client: " + data); 
      }
      if (data == "1"){
        Serial.println("nonintruder");
        digitalWrite(2, HIGH);
        delay(1000); // Wait for 1 second
      }
      if (data == "0"){
        Serial.println("NO");
        digitalWrite(2, LOW);
      }
    client.stop();
    }
  }
}