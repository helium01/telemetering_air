#include "DHT.h"
#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("humidity");
  Serial.println(h);
  Serial.print("temperature");
  Serial.println(t);
  float k=analogRead(A0);
  Serial.println(k);
  delay(1000);

}
