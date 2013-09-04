void setupRobot(){
  Wire.begin();
  Scheduler.startLoop(runMotorLoop);
  motors.setup();
  Serial.begin(9600);
 //calibrateLineFollowing();
 qtra.calibrate();
 
qtra.calibratedMinimumOn[0] = 36;
qtra.calibratedMinimumOn[1] = 34;
qtra.calibratedMinimumOn[2] = 35;
qtra.calibratedMinimumOn[3] = 36;
qtra.calibratedMinimumOn[4] = 34;
qtra.calibratedMinimumOn[5] = 31;
qtra.calibratedMinimumOn[6] = 36;
qtra.calibratedMinimumOn[7] = 37;

qtra.calibratedMaximumOn[0] = 62;
qtra.calibratedMaximumOn[1] = 53;
qtra.calibratedMaximumOn[2] = 58;
qtra.calibratedMaximumOn[3] = 63;
qtra.calibratedMaximumOn[4] = 54;
qtra.calibratedMaximumOn[5] = 46;
qtra.calibratedMaximumOn[6] = 56;
qtra.calibratedMaximumOn[7] = 78;


 
 pinMode(53, INPUT);
 pinMode(51, INPUT);
 pinMode(49, INPUT);
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
