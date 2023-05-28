#include <OneWire.h>
#include <DallasTemperature.h>
#define ECHO_PIN D5  // Pin Echo pada sensor (D5/GPIO14)
#define TRIG_PIN D6  // Pin Trig pada sensor (D6/GPIO12)
int tbdtValue;
int tdsValue;
int phValue;
#define ONE_WIRE_BUS D7 // Menggunakan pin D2 (GPIO4) pada NodeMCU

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
void setup() {
  Serial.begin(9600); // Inisialisasi komunikasi serial
  sensors.begin();
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
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
    Serial.print("TDS: ");
    Serial.println(tdsValue);
    Serial.print("pH: ");
    Serial.println(phValue);
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
  Serial.println(" cm");
 sensors.requestTemperatures();

  float temperatureC = sensors.getTempCByIndex(0);

  // Menampilkan suhu dalam Celcius ke Serial Monitor
  Serial.print("Suhu: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  delay(3000);
  
}
