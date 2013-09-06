void setupRobot(){
  Wire.begin();
  Scheduler.startLoop(runMotorLoop);
  motors.setup();
  Serial.begin(9600);
 //calibrateLineFollowing();
 qtra.calibrate();
 
 //Room 10
//Calibration Values: 
 
qtra.calibratedMinimumOn[0] = 37;
qtra.calibratedMinimumOn[1] = 36;
qtra.calibratedMinimumOn[2] = 37;
qtra.calibratedMinimumOn[3] = 38;
qtra.calibratedMinimumOn[4] = 36;
qtra.calibratedMinimumOn[5] = 33;
qtra.calibratedMinimumOn[6] = 37;
qtra.calibratedMinimumOn[7] = 39;

qtra.calibratedMaximumOn[0] = 67;
qtra.calibratedMaximumOn[1] = 54;
qtra.calibratedMaximumOn[2] = 60;
qtra.calibratedMaximumOn[3] = 64;
qtra.calibratedMaximumOn[4] = 55;
qtra.calibratedMaximumOn[5] = 48;
qtra.calibratedMaximumOn[6] = 60;
qtra.calibratedMaximumOn[7] = 104;
 
 pinMode(PIN_LEFT_COLOUR, INPUT);
 pinMode(PIN_RIGHT_COLOUR, INPUT);
 delay(500); //To let compass sensor protocol get ready
 initialHeading = (int)compass.correctedHeading();

}


void calibrateLineFollowing()
{
  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  motors.setMaxSpeeds(300.0, 300.0);
  motors.rotate(360*2);
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
    yield();
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration
  motors.wait();
  motors.setMaxSpeeds(500, 500);
}
