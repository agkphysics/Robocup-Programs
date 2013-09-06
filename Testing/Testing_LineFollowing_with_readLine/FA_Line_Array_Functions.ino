void lineFollowingLoop(){
  
  int intersectionCount = 0;
  while(!reachedEndTile){
    float currentReadLine = (float)qtra.readLine(currentSensorValues);
    float currentLinePosition = linePosition(currentReadLine);
    
    if (currentReadLine != 0.0 && currentReadLine != 7000.0) {
      setLineFollowingSpeeds(currentLinePosition);
    
      if(reachedIntersectionLeft()){
        navigateIntersection(TRIGGERED_BY_LEFT, intersectionCount);
        intersectionCount++;
      }
    
      if(reachedIntersectionRight()){
        navigateIntersection(TRIGGERED_BY_RIGHT, intersectionCount);
        intersectionCount++;
      }
    
      if(reachedWaterTower()){
        navigateWaterTower();
      }
      delay(2);
    }
  else offLineAction(currentReadLine);
  }
}

void offLineAction(float currentLinePosition) {
  
  if(checkForEndTile()) { //true means end tile is reached
    reachedEndTile = true;
  }
  else { //if it is not end tile
    scanForLine();
  }
}

boolean checkForEndTile() {
  motors.straight(10);
  motors.wait();
  if(digitalRead(PIN_LEFT_COLOUR) == HIGH && digitalRead(PIN_RIGHT_COLOUR) == HIGH) {
    motors.straight(-11); //Optional, could just stay where we were BUT REMEMBER the implications of changing this on scanForLine!!!
    motors.wait();
    return true;  
  }
  else return false;
}

void scanForLine(){
  //TODO
}
  
  

void setLineFollowingSpeeds(float currentLinePosition)
{
  
  
   if (currentLinePosition <= 0.0)
   {
      leftSpeed = leftSpeedFactor * (1.0 + 15.0 * currentLinePosition* currentLinePosition*currentLinePosition);
      rightSpeed = rightSpeedFactor;
   }
   else
   { 
      leftSpeed = leftSpeedFactor;
      rightSpeed = rightSpeedFactor * (1.0 - 15.0 * currentLinePosition* currentLinePosition*currentLinePosition);
   }
   
  motors.setActiveSpeeds(leftSpeed, rightSpeed);
}



float linePosition(float currentReadLine)
{
  float lineReadScaled = currentReadLine / 3500.0; 
  return (lineReadScaled - 1.0);
}

float blackness() { //0 to 8000
  //Must have just called this in LineFollowingSetSpeeds: qtra.readCalibrated(currentSensorValues);
  unsigned int sum = 0;
  for (int i=0; i<8; i++) {
    sum += currentSensorValues[i];
  }
  return (float)sum/8000.0;  
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


