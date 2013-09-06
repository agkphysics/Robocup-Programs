void lineFollowingLoop(){
  
  while(!reachedEndTile){
    float currentReadLine = (float)qtra.readLine(currentSensorValues);
    float currentLinePosition = linePosition(currentReadLine);
    
    setLineFollowingSpeeds(currentLinePosition);
    
    if(leftDetectedGreen()){
      motors.straight(0);
      delay(200);
      if(leftDetectedGreen()){
        reachedIntersectionLeft = true;
      }
    }
      
    if(rightDetectedGreen()){
      motors.straight(0);
      delay(200);
      if(rightDetectedGreen()) {
        reachedIntersectionRight = true;
      }
    }
    
    if (currentReadLine == 0.0 || currentReadLine == 7000.0) { //i.e. if Off the Line
      offLineAction(currentReadLine);
    }
    
    if(reachedIntersectionLeft) {
      navigateIntersection(LEFT);
      intersectionCount++;
      reachedIntersectionLeft = false;
    }
    
    if(reachedIntersectionRight) {
      navigateIntersection(RIGHT);
      intersectionCount++;
      reachedIntersectionRight = false;
    }
      
      
    
    if(digitalRead(PIN_TOWER_SWITCH) == HIGH){
      moveWaterTower();
    }
    delay(2);
  }
}

void offLineAction(float currentReadLine) {
  motors.setMaxSpeeds(maxSpeedManualSections, maxSpeedManualSections);
  motors.straight(1);
  motors.wait();
  
  if(leftDetectedGreen()){
    motors.straight(0);
    delay(200);
    if(leftDetectedGreen()){
      reachedIntersectionLeft = true;
    }
  }
      
  if(rightDetectedGreen()){
    motors.straight(0);
    delay(200);
    if(rightDetectedGreen()) {
      reachedIntersectionRight = true;
    }
  }
  
    motors.straight(1);
  motors.wait();
  
  if(leftDetectedGreen()){
    motors.straight(0);
    delay(200);
    if(leftDetectedGreen()){
      reachedIntersectionLeft = true;
    }
  }
      
  if(rightDetectedGreen()){
    motors.straight(0);
    delay(200);
    if(rightDetectedGreen()) {
      reachedIntersectionRight = true;
    }
  }
  
    motors.straight(1);
  motors.wait();
  
  if(leftDetectedGreen()){
    motors.straight(0);
    delay(200);
    if(leftDetectedGreen()){
      reachedIntersectionLeft = true;
    }
  }
      
  if(rightDetectedGreen()){
    motors.straight(0);
    delay(200);
    if(rightDetectedGreen()) {
      reachedIntersectionRight = true;
    }
  }
  
  
    
  boolean  foundIntersection = reachedIntersectionLeft || reachedIntersectionRight;
  
  if(!foundIntersection) {
    reachedEndTile = checkForEndTile();
  }
  
  if(!foundIntersection && !reachedEndTile) {
    scanForLine(currentReadLine);
  }
  motors.setMaxSpeeds(leftSpeedFactor, rightSpeedFactor);
}

boolean checkForEndTile() {
  motors.straight(7); //Only 7 rather than 10 since 3 have already been done in checking for green
  motors.wait();
  if (leftDetectedGreen() && rightDetectedGreen()) {
    motors.straight(-11); //Optional, could just stay where we were BUT REMEMBER the implications of changing this on scanForLine!!!
    motors.wait();
    return true;  
  }
  else return false;
}

void scanForLine(float currentReadLine){ //starts from 10cm forwards
  motors.straight(-15.0);
  motors.wait();
  if (currentReadLine == 0.0) motors.swingWithLeft(20.0);
  else if (currentReadLine == 7000.0) motors.swingWithRight(20.0);
  motors.wait();
  delay(250);
  float newReadLine = (float)(qtra.readLine(currentSensorValues));
    
    if (newReadLine == 0.0) {
      motors.swingWithLeft(-20.0);
      motors.wait();
      motors.swingWithRight(20.0);
      motors.wait();
    }
    
    if (newReadLine == 7000.0) {
      motors.swingWithRight(-20.0);
      motors.wait();
      motors.swingWithLeft(20.0);
      motors.wait();
    }
  
}
  
  

void setLineFollowingSpeeds(float currentLinePosition)
{
  
  
   if (currentLinePosition <= 0.0)
   {
      leftSpeed = leftSpeedFactor * (1.0 + 18*currentLinePosition*currentLinePosition*currentLinePosition);
//      leftSpeed = leftSpeedFactor * (1.0 + 5*currentLinePosition);
      rightSpeed = rightSpeedFactor;
   }
   else
   { 
      leftSpeed = leftSpeedFactor;
      rightSpeed = rightSpeedFactor * (1.0 - 18 *currentLinePosition*currentLinePosition*currentLinePosition);
//      rightSpeed = rightSpeedFactor * (1.0 - 5 *currentLinePosition);
   }
   
  motors.setActiveSpeeds(leftSpeed, rightSpeed);
}

boolean checkForGreen(){

      if(leftDetectedGreen()){
        navigateIntersection(LEFT);
        intersectionCount++;
        return true;
      }
      
      else if(rightDetectedGreen()){
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

boolean leftDetectedGreen() {
  return  (analogRead(PIN_LEFT_COLOUR) > 100);
}
    
boolean rightDetectedGreen() {
  return (analogRead(PIN_RIGHT_COLOUR) > 100);
}
