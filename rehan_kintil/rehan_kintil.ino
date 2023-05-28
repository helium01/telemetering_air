#include "DHT.h"
#define DHTPIN D3
#define DHTTYPE DHT11

const int ldrPin = A0; 

int ombrometerPin = D2;  // Pin digital yang terhubung ke sensor ombrometer
volatile unsigned int rainCount = 0;  // Jumlah pulsa yang terhitung
float rainIntensity = 0.0;  // Intensitas curah hujan (mm/menit)
float rainTotal = 0.0;  // Curah hujan total (mm)

// Inisialisasi pin dan variabel
int anemometerPin = D1;       // Pin digital yang terhubung ke sensor anemometer
volatile unsigned int pulseCount = 0;   // Jumlah pulsa yang terhitung
unsigned int previousTime = 0;   // Waktu sebelumnya
float windSpeed = 0.0;   // Kecepatan angin


DHT dht(DHTPIN, DHTTYPE);

void ICACHE_RAM_ATTR countPulse() {
  pulseCount++;   // Menghitung setiap kali terjadi pulsa
}

void ICACHE_RAM_ATTR countRain() {
  rainCount++;
  rainIntensity = rainCount / 60.0;  // Menghitung intensitas curah hujan per menit
  rainTotal += rainIntensity;  // Menambahkan intensitas curah hujan ke total curah hujan
}

void setup() {
  Serial.begin(9600);  // Inisialisasi komunikasi serial
  pinMode(ombrometerPin, INPUT_PULLUP);  // Mengatur pin sebagai input dengan pull-up internal
  attachInterrupt(digitalPinToInterrupt(ombrometerPin), countRain, FALLING);  // Mengaitkan interupsi dengan pin sensor ombrometer
  attachInterrupt(digitalPinToInterrupt(anemometerPin), countPulse, RISING);   // Mengaitkan interupsi dengan pin sensor anemometer
  dht.begin();
}

void angin(){
    unsigned int currentTime = millis();   // Waktu saat ini

  if (currentTime - previousTime >= 1000) {   // Menghitung kecepatan angin setiap 1 detik
    windSpeed = calculateWindSpeed(pulseCount);   // Menghitung kecepatan angin dalam m/s
    pulseCount = 0;   // Mengatur ulang jumlah pulsa

    Serial.print("Kecepatan Angin: ");
    Serial.print(windSpeed);
    Serial.println(" m/s");

    previousTime = currentTime;   // Menyimpan waktu sekarang sebagai waktu sebelumnya
  }
}

void hujan(){
  Serial.print("Intensitas Curah Hujan: ");
  Serial.print(rainIntensity);
  Serial.println(" mm/menit");

  Serial.print("Curah Hujan Total: ");
  Serial.print(rainTotal);
  Serial.println(" mm");

  delay(1000);  // Jeda 1 detik
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
}

void mq_seris(){
    if (Serial.available()) {
    String data = Serial.readStringUntil('\n');  // Membaca data yang dikirim dari Arduino

    // Memisahkan nilai-nilai sensor yang dikirimkan
    int sensorValueA0 = data.substring(0, data.indexOf(',')).toInt();
    data = data.substring(data.indexOf(',') + 1);
    int sensorValueA1 = data.substring(0, data.indexOf(',')).toInt();
    data = data.substring(data.indexOf(',') + 1);
    int sensorValueA2 = data.toInt();

    // Melakukan apa pun yang diperlukan dengan nilai-nilai sensor yang diterima
    // Misalnya, tampilkan nilai-nilai sensor pada Serial Monitor
    Serial.print("Nilai Sensor A0: ");
    Serial.println(sensorValueA0);
    Serial.print("Nilai Sensor A1: ");
    Serial.println(sensorValueA1);
    Serial.print("Nilai Sensor A2: ");
    Serial.println(sensorValueA2);
  }
}
void cahaya(){
   int ldrValue = analogRead(ldrPin);  // Membaca nilai analog dari pin LDR
  Serial.print("Nilai LDR: ");
  Serial.println(ldrValue);
  
  delay(1000);  // Tunda selama 1 detik sebelum membaca nilai sensor lagi
}

void loop() {
  hujan();
  angin();
  suhu();
  mq_seris();
  cahaya();
}

float calculateWindSpeed(unsigned int pulseCount) {
  // Konversi jumlah pulsa menjadi kecepatan angin (misalnya dalam m/s)
  // Anda dapat menyesuaikan rumus konversi sesuai dengan karakteristik sensor anemometer yang Anda gunakan
  // Contoh: Rumus umum untuk sensor anemometer tertentu adalah V = (pulseCount * K) / T
  // Di mana V adalah kecepatan angin dalam m/s, pulseCount adalah jumlah pulsa, K adalah faktor konversi, dan T adalah waktu pengukuran dalam detik
  // Anda perlu menyesuaikan rumus ini sesuai dengan spesifikasi sensor anemometer yang Anda gunakan
  // Misalnya, jika sensor Anda menghasilkan 1 pulsa per putaran dan K = 2.4 (misalnya dari spesifikasi sensor), rumusnya menjadi V = (pulseCount * 2.4) / T

  // Menghitung kecepatan angin dengan rumus sederhana
  float windSpeed = pulseCount * 2.4;

  return windSpeed;
}
