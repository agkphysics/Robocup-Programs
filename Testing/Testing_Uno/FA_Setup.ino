void definePins()
{
  pinMode(PIN_TOWER_SWITCH, INPUT);
  pinMode(PIN_BOARD_LED, OUTPUT);
}

void setupCompass()
{
  delay(500);
  //initialHeading = (int)compass.correctedHeading();
  initialHeading = INITIAL_HEADING;
}

void setupAll()
{
  Wire.begin();
  definePins();
  setupCompass();
  Serial.begin(9600);
  //printArrayCalibrationValues();
}

/*
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
*/
