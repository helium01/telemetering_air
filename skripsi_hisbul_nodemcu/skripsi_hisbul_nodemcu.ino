#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "aku";
const char* password = "sayang13";
#define ECHO_PIN D5  // Pin Echo pada sensor (D5/GPIO14)
#define TRIG_PIN D6  // Pin Trig pada sensor (D6/GPIO12)
int tbdtValue;
int tdsValue;
int phValue;
#define ONE_WIRE_BUS D7 // Menggunakan pin D2 (GPIO4) pada NodeMCU
const char* serverkekeruhan = "http://iot.mtsshifa.com/api/kekeruhan";
const char* serverphair = "http://iot.mtsshifa.com/api/ph_air";
const char* servertds = "http://iot.mtsshifa.com/api/tds";
const char* serverultrasonik = "http://iot.mtsshifa.com/api/ultrasonik";
const char* servervalve = "http://iot.mtsshifa.com/api/valve";
const char* serverwater = "http://iot.mtsshifa.com/api/water_pumps";
const char* serversuhu = "http://iot.mtsshifa.com/api/suhu";

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
void setup() {
  Serial.begin(9600); // Inisialisasi komunikasi serial
  sensors.begin();
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (Serial.available() > 0) {
    String receivedData = Serial.readStringUntil('\n'); // Membaca data dari NodeMCU sampai karakter '\n' (baris baru)

    // Memproses data yang diterima dari NodeMCU
    if (receivedData.startsWith("TBDT:")) {
      tbdtValue = receivedData.substring(5).toInt(); // Mengambil nilai dari data TBDT
    } else if (receivedData.startsWith("TDS:")) {
      tdsValue = receivedData.substring(4).toInt(); // Mengambil nilai dari data TDS
    } else if (receivedData.startsWith("pH:")) {
      phValue = receivedData.substring(3).toInt(); // Mengambil nilai dari data pH
    }

    // Menampilkan data yang diterima dari NodeMCU
    Serial.println("Data yang diterima dari NodeMCU:");
    Serial.print("TBDT: ");
    Serial.println(tbdtValue);
    sendSensorkekeruhan(tbdtValue);
    Serial.print("TDS: ");
    Serial.println(tdsValue);
    sendSensortds(tdsValue);
    Serial.print("pH: ");
    Serial.println(phValue);
    sendSensorph(phValue);
    Serial.println("--------------------");
  }
   // Mengirim sinyal trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Menerima waktu respons dari sensor
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Menghitung jarak berdasarkan waktu respons
  float distance_cm = duration * 0.034 / 2;

  // Menampilkan jarak ke Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance_cm);
    sendSensorultrasonik(distance_cm);
  Serial.println(" cm");
 sensors.requestTemperatures();

  float temperatureC = sensors.getTempCByIndex(0);

  // Menampilkan suhu dalam Celcius ke Serial Monitor
  Serial.print("Suhu: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
    sendSensorsuhu(temperatureC);
  delay(3000);
  
}
void sendSensorkekeruhan(int value) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Membuat permintaan POST ke API
    http.begin(client, serverkekeruhan);

    // Mengatur header permintaan
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Membuat payload data
    String postData = "node=" + String(value) + "&value=" + String(value);

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
void sendSensorph(int value) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Membuat permintaan POST ke API
    http.begin(client, serverphair);

    // Mengatur header permintaan
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Membuat payload data
    String postData = "node=" + String(value) + "&value=" + String(value);

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
void sendSensortds(int value) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Membuat permintaan POST ke API
    http.begin(client, servertds);

    // Mengatur header permintaan
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Membuat payload data
    String postData = "node=" + String(value) + "&value=" + String(value);

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
void sendSensorultrasonik(int value) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Membuat permintaan POST ke API
    http.begin(client, serverultrasonik);

    // Mengatur header permintaan
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Membuat payload data
    String postData = "node=" + String(value) + "&value=" + String(value);

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
void sendSensorsuhu(int value) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Membuat permintaan POST ke API
    http.begin(client, serversuhu);

    // Mengatur header permintaan
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Membuat payload data
    String postData = "node=" + String(value) + "&value=" + String(value);

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
