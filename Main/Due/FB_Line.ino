void lineFollowingLoop(){
  
  while(!reachedEndTile){
    float currentReadLine = (float)qtra.readLine(currentSensorValues);
    float currentLinePosition = linePosition(currentReadLine);
    
    if (currentReadLine != 0.0 && currentReadLine != 7000.0) {
      setLineFollowingSpeeds(currentLinePosition);
      boolean randomTest = checkForGreen();
      if(digitalRead(PIN_TOWER_SWITCH) == HIGH){
        moveWaterTower();
      }
      delay(2);
    }
  else offLineAction(currentReadLine);
  }
}

void offLineAction(float currentLinePosition) {
  motors.straight(1);
  motors.wait();
  if(checkForGreen()) return;
  motors.straight(1);
  motors.wait();
  if(checkForGreen()) return;
  motors.straight(1);
  motors.wait();
  if(checkForGreen()) return;
   
  if(checkForEndTile()) { //true means end tile is reached
    reachedEndTile = true;
    return;
  }
  else { //if it is not end tile
    scanForLine();
  }
}

boolean checkForEndTile() {
  motors.straight(7); //Only 7 rather than 10 since 3 have already been done in checking for green
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

boolean checkForGreen(){

      if(digitalRead(PIN_LEFT_COLOUR) == HIGH){
        navigateIntersection(LEFT);
        intersectionCount++;
        return true;
      }
      
      else if(digitalRead(PIN_RIGHT_COLOUR) == HIGH){
        navigateIntersection(RIGHT);
        intersectionCount++;
        return true;
      }
      else return false;
}

float linePosition(float currentReadLine)
{
  float lineReadScaled = currentReadLine / 3500.0; 
  return (lineReadScaled - 1.0);
}
