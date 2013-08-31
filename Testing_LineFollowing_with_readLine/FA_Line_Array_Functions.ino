void setLineFollowingSpeeds()
{
  float currentLinePosition = linePosition();
  
  if (currentLinePosition <= 0.0)
  {
    leftSpeed = leftSpeedFactor * (1.0 + 5.0 * currentLinePosition);
    rightSpeed = rightSpeedFactor;
  }
  else
  {
    leftSpeed = leftSpeedFactor;
    rightSpeed = rightSpeedFactor * (1.0 - 5.0 * currentLinePosition);
  }

  motors.setActiveSpeeds(leftSpeed, rightSpeed);
}

float linePosition()
{
  float lineReadScaled = (float)qtra.readLine(currentSensorValues) / 3500.0; 
  return (lineReadScaled - 1.0);
}

boolean reachedEndTile() { //TODO
  return false;
}

void calibrateLineFollowing()
{
  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration
}
