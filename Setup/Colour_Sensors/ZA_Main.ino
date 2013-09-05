void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Waiting for 'Y'");
  waitForY();
  calibrateSensors();
  printCalibrationValues();
}
