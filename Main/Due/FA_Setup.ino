void setupLineArray() {
   qtra.calibrate();
 
 //Room 10 dark
//Calibration Values: 
 
qtra.calibratedMinimumOn[0] = 35;
qtra.calibratedMinimumOn[1] = 33;
qtra.calibratedMinimumOn[2] = 34;
qtra.calibratedMinimumOn[3] = 35;
qtra.calibratedMinimumOn[4] = 33;
qtra.calibratedMinimumOn[5] = 30;
qtra.calibratedMinimumOn[6] = 35;
qtra.calibratedMinimumOn[7] = 36;

qtra.calibratedMaximumOn[0] = 80;
qtra.calibratedMaximumOn[1] = 57;
qtra.calibratedMaximumOn[2] = 70;
qtra.calibratedMaximumOn[3] = 100;
qtra.calibratedMaximumOn[4] = 69;
qtra.calibratedMaximumOn[5] = 51;
qtra.calibratedMaximumOn[6] = 106;
qtra.calibratedMaximumOn[7] = 229;


}

void definePins() {
  pinMode(PIN_LEFT_COLOUR, INPUT);
  pinMode(PIN_RIGHT_COLOUR, INPUT);
  pinMode(PIN_LEOSTICK_EXTRA, INPUT);
  pinMode(PIN_LIFT_MOTOR, OUTPUT);
  pinMode(PIN_TOWER_SWITCH, INPUT);
  pinMode(PIN_BOARD_LED, OUTPUT);
  digitalWrite(PIN_LIFT_MOTOR, LOW);
}

void setupOutputs() {
  closeArm.attach(3);
  closeArm.write(60);
  delay(500);
  Scheduler.startLoop(runMotorLoop);
  motors.setup();
}

void setupCompass() {
  Wire.begin();
  delay(500);
  initialHeading = (int)compass.correctedHeading();
}

void setupAll() {
  definePins();
  setupLineArray();
  setupCompass();
  setupOutputs();
  Serial.begin(9600);
  printArrayCalibrationValues();
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
