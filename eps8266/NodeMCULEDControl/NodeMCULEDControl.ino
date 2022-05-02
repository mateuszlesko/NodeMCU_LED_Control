#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define R 5 // PIN D1
#define Y 4 // PIN D2
#define G 2 // PIN D4

const char* ssid = "xxxxxx";
const char* password = "xxxxx";

const String serverName = "http://192.168.100.132:5108/led/checkstatus";

unsigned long lastTime = 0;

void setup() {

  Serial.println("CONFIG");
  Serial.begin(9600);
   
  //PORTS CONFIG
  pinMode(R,OUTPUT);
  pinMode(Y,OUTPUT);
  pinMode(G,OUTPUT);

  //CONN CONFIG
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Send an HTTP request depending on timerDelay
  if ((millis() - lastTime) > 2000) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      http.begin(client, serverName.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        switch(payload.toInt()){
          case 1:
          digitalWrite(G,1);
          digitalWrite(Y,0);
          digitalWrite(R,0);
          break;
          case 2:
          digitalWrite(G,0);
          digitalWrite(R,0);
          digitalWrite(Y,1);
          break;
          case 3:
          digitalWrite(R,0);
          digitalWrite(G,1);
          digitalWrite(Y,1);
          break;
          case 4:
          digitalWrite(G,0);
          digitalWrite(Y,0);
          digitalWrite(R,1);
          break;
          case 5:
          digitalWrite(Y,0);
          digitalWrite(G,1);
          digitalWrite(R,1);
          break;
          case 6:
          digitalWrite(G,0);
          digitalWrite(Y,1);
          digitalWrite(R,1);
          break;
          case 7:
          digitalWrite(Y,1);
          digitalWrite(G,1);
          digitalWrite(R,1);
          break;
          default:
          digitalWrite(Y,0);
          digitalWrite(G,0);
          digitalWrite(R,0);
          break;
        }
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
