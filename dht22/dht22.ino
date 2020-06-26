#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
   Serial.begin(9600);
   Serial.println("DHTxx test!");
   dht.begin();
} 

void loop() {
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
}
