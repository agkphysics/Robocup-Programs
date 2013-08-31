void setLineFollowingSpeeds()
{
  float currentLinePosition = linePosition();
  float currentBlacknessRatio = (1-blackness())/0.8;
  if (currentBlacknessRatio < 0.1) {
    currentBlacknessRatio = 0.1;
  }
  if (currentBlacknessRatio > 1){
    currentBlacknessRatio = 1;
  }
  
  //linePositionBuffer.putValue(currentLinePosition);
  //float averageLinePosition = linePositionBuffer.getAverage();
  
  if (currentLinePosition <= 0.0)
  {
    leftSpeed =  leftSpeedFactor * (1.0 - 1.0 * currentLinePosition* currentLinePosition* currentLinePosition*currentLinePosition);//Linepos needs to  be minused for this one in the end
    rightSpeed = rightSpeedFactor;

  }
  else
  {
    leftSpeed = leftSpeedFactor;
    rightSpeed = rightSpeedFactor * (1.0 - 1.0 * currentLinePosition* currentLinePosition* currentLinePosition*currentLinePosition); //Line pos needs to be minused in the end
  }
  /*
  Serial.print(currentLinePosition);
  Serial.print(" ");
//  Serial.print(averageLinePosition);
  Serial.print(" ");
  Serial.print(leftSpeed);
  Serial.print(" ");
  Serial.print(rightSpeed);
  Serial.print(" ");
  Serial.print(currentBlacknessRatio);
  Serial.print(" ");
*/
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
  qtra.readCalibrated(currentSensorValues);
  unsigned int sum = 0;
  for (int i=0; i<8; i++) {
    sum += currentSensorValues[i];
  }
  return (float)sum/6000.0;  
}
