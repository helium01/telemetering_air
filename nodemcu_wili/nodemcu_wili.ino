#include "DHT.h"
#define DHTPIN D3
#define DHTTYPE DHT11
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "iPhone";      // Nama SSID WiFi Anda
const char* password = "1234567890";  // Kata sandi WiFi Anda
const char* serversoil = "http://monitoringtanah.id.mtsshifa.com/api/soil";
const char* serverph = "http://monitoringtanah.id.mtsshifa.com/api/phs";
const char* serversuhu = "http://monitoringtanah.id.mtsshifa.com/api/dht11s";
DHT dht(DHTPIN, DHTTYPE);
const int pHSensorPin = A0;
void setup() {
  Serial.begin(9600);
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
  // put your setup code here, to run once:

}

void suhu(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print("\n");
  Serial.print(F("  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  delay(2000);
  sendsensordht(h,t);
}
void soil(){

  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');  // Membaca data dari Arduino melalui komunikasi serial

    // Memproses data yang diterima
//    if (data.startsWith("Moisture: ")) {
//      int moistureValue = data.substring(10).toInt();  // Mengambil nilai kelembaban tanah sebagai integer
      Serial.print("Moisture Value: ");
//      Serial.println(moistureValue);
      sendsensorsoil(data.toInt());
//    }
}}
void ph(){
  int sensorValue = analogRead(pHSensorPin);  // Membaca nilai analog dari sensor pH

  // Mengkonversi nilai analog menjadi pH
  float voltage = sensorValue * (5.0 / 1023.0);  // Menghitung tegangan dari nilai pembacaan
  float pHValue = 7 - (voltage - 2.5);  // Menghitung pH dari tegangan

  // Menampilkan nilai pH pada monitor serial
  Serial.print("pH: ");
  Serial.println(pHValue, 2);  // Mencetak nilai pH dengan 2 digit desimal
  sendsensorph(pHValue);

  delay(1000);  // Jeda 1 detik sebelum membaca sensor lagi
}
void loop() {
  // put your main code here, to run repeatedly:
  suhu();
  soil();
  ph();
  delay(1000);

}
void sendsensorsoil(int value) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Membuat permintaan POST ke API
    http.begin(client, serversoil);

    // Mengatur header permintaan
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Membuat payload data
    String postData = "node1=" + String(value) + "&value=" + String(value);

    // Mengirim permintaan POST dengan payload data
    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Respon dari server: " + response);
    } else {
      Serial.println("Gagal mengirim permintaan POST");
    }

    http.end();
  } else {
    Serial.println("Tidak terhubung ke jaringan WiFi");
  }
}
void sendsensorph(int value) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Membuat permintaan POST ke API
    http.begin(client, serverph);

    // Mengatur header permintaan
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Membuat payload data
    String postData = "node1=" + String(value) + "&value=" + String(value);

    // Mengirim permintaan POST dengan payload data
    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Respon dari server: " + response);
    } else {
      Serial.println("Gagal mengirim permintaan POST");
    }

    http.end();
  } else {
    Serial.println("Tidak terhubung ke jaringan WiFi");
  }
}
void sendsensordht(int value1,int value2) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Membuat permintaan POST ke API
    http.begin(client, serversuhu);

    // Mengatur header permintaan
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Membuat payload data
    String postData = "node1=" + String(value1) + "&node2=" + String(value2);

    // Mengirim permintaan POST dengan payload data
    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Respon dari server: " + response);
    } else {
      Serial.println("Gagal mengirim permintaan POST");
    }

    http.end();
  } else {
    Serial.println("Tidak terhubung ke jaringan WiFi");
  }
}
