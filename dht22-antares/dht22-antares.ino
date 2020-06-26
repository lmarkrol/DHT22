#include <AntaresESP8266MQTT.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT22 

#define ACCESSKEY "" 
#define projectName ""
#define deviceName "" 

AntaresESP8266MQTT antares(ACCESSKEY);

const char* ssid = "";
const char* password = ""; 


float h;
float t;
float f;
float hic;
float hif;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
   Serial.begin(9600);

  antares.setDebug(true);   
  antares.wifiConnection(ssid, password);  
  antares.setMqttServer();  
   
   Serial.println("DHTxx test!");
   dht.begin();

   Serial.println("Connecting to");
   Serial.println(ssid);

   WiFi.begin(ssid, password);

   while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WIFI CONNECTED..!");
} 

void loop() {

   antares.checkMqttConnection(); 
  
   delay(2000);
   float h = dht.readHumidity();
   
   float t = dht.readTemperature();
   
   float f = dht.readTemperature(true);
   
   if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
   }
   
  
   float hif = dht.computeHeatIndex(f, h);
  
   float hic = dht.computeHeatIndex(t, h, false);
   Serial.print ("Humidity: ");
   Serial.print (h);
   Serial.print (" %\t");
   Serial.print ("Temperature: ");
   Serial.print (t);
   Serial.print("\xC2\xB0");
   Serial.print ("C\t ");
   Serial.print (f);
   Serial.print("\xC2\xB0");
   Serial.print ("F\t");
   Serial.print ("Heat index: ");
   Serial.print (hic);
   Serial.print("\xC2\xB0");
   Serial.print ("C\t ");
   Serial.print (hif);
   Serial.print("\xC2\xB0");
   Serial.println ("F ");

   antares.add("Humidity: ", h);
   antares.add("Celsius: ", t);
   antares.add("Fahrenheit: ", f);
   antares.add("Heat Index: ", hic);
   antares.add("Heat Index: ", hif);

  antares.publish(projectName, deviceName);
  delay(3000);
}
