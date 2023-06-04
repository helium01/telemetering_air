#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "iPhone";
const char* password = "1234567890";
const char* serverstatus = "http://smartkost.id.mtsshifa.com/api/status/1";

void setup() {
  Serial.begin(9600);
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
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readString();
    Serial.println("Data received: " + data);
      Serial.println("sampai sini");
      sendDatastatus("1");
    
  }
}

void sendDatastatus(String value) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Membuat permintaan POST ke API
    http.begin(client, serverstatus);

    // Mengatur header permintaan
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Membuat payload data
    String postData = "status=" + String(value) + "&value=" + String(value);

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
