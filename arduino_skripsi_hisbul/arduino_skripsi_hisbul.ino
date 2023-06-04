void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  float tbdt = analogRead(A2);
  float tds = analogRead(A1);
  float ph = analogRead(A0);
   Serial.print("TBDT:");
  Serial.println(tbdt);
  Serial.print("TDS:");
  Serial.println(tds);
  Serial.print("pH:");
  Serial.println(ph);
  delay(1000);
  

}
