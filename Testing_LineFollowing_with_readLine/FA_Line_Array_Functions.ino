void setLineFollowingSpeeds()
{
  float currentLinePosition = linePosition();
  
  if (currentLinePosition <= 0.0)
  {
    leftSpeed = leftSpeedFactor * (1.0 - 30.0 * currentLinePosition * currentLinePosition * currentLinePosition * currentLinePosition);
    rightSpeed = rightSpeedFactor;
//    leftSpeed = (1.5-blackness())*leftSpeedFactor * (1.0 + 15.0 * currentLinePosition* currentLinePosition*currentLinePosition);
//    rightSpeed = (1.5-blackness())*rightSpeedFactor;
  }
  else
  {
    leftSpeed = leftSpeedFactor;
    rightSpeed = rightSpeedFactor * (1.0 - 30.0 * currentLinePosition * currentLinePosition * currentLinePosition * currentLinePosition);
  //  leftSpeed = (1.5-blackness())*leftSpeedFactor;
  //  rightSpeed = (1.5-blackness())*rightSpeedFactor * (1.0 - 15.0 * currentLinePosition* currentLinePosition*currentLinePosition);
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
  motors.rotate(10000);
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
    yield();
  }
  motors.setSpeeds(0.0,0.0);
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration
}

float blackness() { //0 to 8000
  //Must have just called this in LineFollowingSetSpeeds: qtra.readCalibrated(currentSensorValues);
  unsigned int sum = 0;
  for (int i=0; i<8; i++) {
    sum += currentSensorValues[i];
  }
  return (float)sum/6000.0;  
}
