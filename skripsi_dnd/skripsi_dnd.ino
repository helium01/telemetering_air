#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

const char* ssid = "iPhone";
const char* password = "1234567890";
#define DHTPIN D6 // Pin sensor DHT11 dihubungkan ke pin D3 (GPIO 0)
#define DHTTYPE DHT11 // Tipe sensor DHT11
const char* serverAddress = "http://monitoringgabah.patusaninc.com/api/pirs";

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(D3,OUTPUT);
  Serial.println();
  Serial.print("Menghubungkan ke ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Koneksi WiFi berhasil");
  Serial.print("Alamat IP: ");
  Serial.println(WiFi.localIP());
  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

//  if (isnan(humidity) || isnan(temperature)) {
//    Serial.println("Gagal membaca data dari sensor DHT11");
//    return;
//  }

  Serial.println(humidity);
  Serial.println(temperature);
  float getar=digitalRead(D1);
  
    Serial.println(getar);
  float gas = analogRead(A0);
    Serial.println(gas);
  if(getar>0 || gas>=200){
    Serial.println(getar);
    Serial.println(gas);
    digitalWrite(D3,HIGH);
    delay(1000);
  }
  digitalWrite(D3,LOW);
  // Kode lainnya di sini
  delay(1000);
}
