void calibrateLineFollowing()
{
  delay(500);
  digitalWrite(PIN_BOARD_LED, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(PIN_BOARD_LED, LOW);     // turn off Arduino's LED to indicate we are through with calibration
}

void printArrayCalibrationValues() {
  for (int i = 0; i < 8; i++)
  {
    Serial.print("qtra.calibratedMinimumOn[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.print(qtra.calibratedMinimumOn[i]);
    Serial.println(";");
  }
  Serial.println();
  for (int i = 0; i < 8; i++)
  {
    Serial.print("qtra.calibratedMaximumOn[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.print(qtra.calibratedMaximumOn[i]);
    Serial.println(";");
  }
  Serial.println();
  
}
