void setupRobot(){
  Wire.begin();
  Scheduler.startLoop(runMotorLoop);
  motors.setup();
  Serial.begin(9600);
 calibrateLineFollowing();
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
