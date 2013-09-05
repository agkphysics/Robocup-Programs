void setup() {
  Serial.begin(9600);
  pinMode(PIN_TOWER_SWITCH, INPUT);
  pinMode(PIN_BOARD_LED, OUTPUT);
  digitalWrite(PIN_BOARD_LED, LOW);
}

void loop() {
  while(digitalRead(PIN_TOWER_SWITCH) == LOW); //Wait till Tower switch is pressed
  calibrateLineFollowing();
  Serial.println("Calibration Values: ");
  Serial.println(" ");
  printArrayCalibrationValues();
  Serial.println(" ");
  Serial.println(" ");
}
