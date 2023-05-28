#include <ESP8266WiFi.h>
#include <DHT.h>

const char* ssid = "B. RIEKE Bwh"; // Nama SSID WiFi Anda
const char* password = "gulamanis"; // Kata sandi WiFi Anda


#define DHTPIN D6 // Pin sensor DHT11 dihubungkan ke pin D3 (GPIO 0)
#define DHTTYPE DHT11 // Tipe sensor DHT11


DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(10);

  // Menghubungkan ke jaringan WiFi
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
    int pirValue = digitalRead(D1);
  int rainValue = digitalRead(D2);
  int cahayaValue = analogRead(A0);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Gagal membaca data dari sensor DHT11");
    return;
  }

  Serial.println(humidity);
  Serial.println(temperature);
  Serial.println(rainValue);
  Serial.println(cahayaValue);
  

  delay(1000);
  // Kode program utama
}
