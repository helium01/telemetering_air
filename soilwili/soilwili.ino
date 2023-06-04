// Pin sensor tanah terhubung ke pin analog A0
const int soilMoisturePin = A0;

void setup() {
  Serial.begin(9600);  // Memulai komunikasi serial dengan baud rate 9600
}

void loop() {
  int soilMoistureValue = analogRead(soilMoisturePin);  // Membaca nilai analog dari sensor

  // Menghitung persentase kelembaban tanah berdasarkan nilai pembacaan
  int moisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);

  // Menampilkan nilai kelembaban tanah pada monitor serial
  Serial.print(moisturePercentage);

  delay(1000);  // Jeda 1 detik sebelum membaca sensor lagi
}
