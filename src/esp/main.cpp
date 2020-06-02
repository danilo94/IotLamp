#include "ESP8266WiFi.h"
#include "secrets.h" 
#define R D1
#define G D2
#define B D4
WiFiServer wifiServer(5000);
void setAnalogWrites(int r,int g, int b);
void setSignals(int value);

void setup() {
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  setSignals(0);
  Serial.begin(9600);
 
  delay(1000);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
 
  Serial.print("Connected to WiFi. IP:");
  Serial.println(WiFi.localIP());
  wifiServer.begin();
}
 
void loop() {
 
  WiFiClient client = wifiServer.available();
 
  if (client) {
 
    while (client.connected()) {
      Serial.println("OPA");
      delay(8);
      while (client.available()>0) {
        String c = client.readString();
        Serial.println(c);
        int valor = c.toInt();
        setSignals(valor);
      }
 
      delay(10);
    }
 
    client.stop();
    delay(1);
    Serial.println("Client disconnected");
 
  }
}


void setSignals(int value)
{
 switch(value){
   case 0:
    setAnalogWrites(0,0,0);
   break;
   case 1:
    setAnalogWrites(1024,0,0);
   break;
   case 2:
    setAnalogWrites(0,1024,0);
   break;
   case 3:
    setAnalogWrites(0,0,1024);
   break;
 }
}

void setAnalogWrites(int r,int g, int b){
  analogWrite(R,r);
  analogWrite(G,g);
  analogWrite(B,b);
}
