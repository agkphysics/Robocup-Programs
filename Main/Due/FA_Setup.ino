void setupLineArray() {
   qtra.calibrate();
 
 //Room 10 dark
//Calibration Values: 
 
qtra.calibratedMinimumOn[0] = 38;

qtra.calibratedMinimumOn[1] = 35;

qtra.calibratedMinimumOn[2] = 36;

qtra.calibratedMinimumOn[3] = 38;

qtra.calibratedMinimumOn[4] = 35;

qtra.calibratedMinimumOn[5] = 33;

qtra.calibratedMinimumOn[6] = 37;

qtra.calibratedMinimumOn[7] = 39;



qtra.calibratedMaximumOn[0] = 69;

qtra.calibratedMaximumOn[1] = 55;

qtra.calibratedMaximumOn[2] = 59;

qtra.calibratedMaximumOn[3] = 70;

qtra.calibratedMaximumOn[4] = 57;

qtra.calibratedMaximumOn[5] = 48;

qtra.calibratedMaximumOn[6] = 61;

qtra.calibratedMaximumOn[7] = 213;



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
