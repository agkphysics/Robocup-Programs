void setupLineArray() {
   qtra.calibrate();
 
//Competition Day Values:
qtra.calibratedMinimumOn[0] = 36;

qtra.calibratedMinimumOn[1] = 34;

qtra.calibratedMinimumOn[2] = 35;

qtra.calibratedMinimumOn[3] = 37;

qtra.calibratedMinimumOn[4] = 34;

qtra.calibratedMinimumOn[5] = 31;

qtra.calibratedMinimumOn[6] = 36;

qtra.calibratedMinimumOn[7] = 38;



qtra.calibratedMaximumOn[0] = 98;

qtra.calibratedMaximumOn[1] = 67;

qtra.calibratedMaximumOn[2] = 76;

qtra.calibratedMaximumOn[3] = 178;

qtra.calibratedMaximumOn[4] = 81;

qtra.calibratedMaximumOn[5] = 51;

qtra.calibratedMaximumOn[6] = 86;

qtra.calibratedMaximumOn[7] = 227;




}

void definePins() {
  //pinMode(PIN_LEFT_COLOUR, INPUT);// Uncomment out if using DIGITAL pins
  //pinMode(PIN_RIGHT_COLOUR, INPUT);// Uncomment out if using DIGITAL pins
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
  digitalWrite(3, LOW);
  Scheduler.startLoop(runMotorLoop);
  motors.setup();
}

void setupCompass() {
  Wire.begin();
  delay(500);
  //initialHeading = (int)compass.correctedHeading();
  initialHeading = INITIAL_HEADING;
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
