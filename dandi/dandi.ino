#include "DHT.h"
#define DHTPIN 3
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  float mq=analogRead(A0);
  Serial.print("sensor mq = ");
  Serial.print(mq);
  Serial.println("\n");
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("humidity");
  Serial.print(h);
  Serial.println("\n");
  Serial.print("temperature");
  Serial.print(t);
  Serial.println("\n");
  float a=analogRead(A1);
  Serial.print("cahaya = ");
  Serial.print(a);
  Serial.println("\n");
  delay(1000);

}
