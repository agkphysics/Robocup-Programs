void lineFollowingLoop(){
  
  while(!reachedEndTile){
    float currentReadLine = (float)qtra.readLine(currentSensorValues);
    float currentLinePosition = linePosition(currentReadLine);
    
    setLineFollowingSpeeds(currentLinePosition);
    
    if(digitalRead(PIN_LEFT_COLOUR) == HIGH){
        navigateIntersection(LEFT);
        intersectionCount++;
    }
      
    if(digitalRead(PIN_RIGHT_COLOUR) == HIGH){
      navigateIntersection(RIGHT);
      intersectionCount++;
    }
    
    //if (currentReadLine == 0.0 || currentReadLine == 7000.0) { //i.e. if Off the Line
    //  offLineAction(currentReadLine);
    //}
    
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
  motors.straight(3);
  while(motors.running() && !reachedIntersectionLeft && !reachedIntersectionRight){
    if(digitalRead(PIN_LEFT_COLOUR) == HIGH){
      reachedIntersectionLeft = true;
    }
    
    if(digitalRead(PIN_RIGHT_COLOUR) == HIGH){
      reachedIntersectionRight = true;
    }
    delay(50);
  }
    
  boolean  foundIntersection = reachedIntersectionLeft || reachedIntersectionRight;
  
  if(!foundIntersection) {
    reachedEndTile = checkForEndTile();
  }
  
  if(!foundIntersection && !reachedEndTile) {
    scanForLine();
  }
}

boolean checkForEndTile() {
  motors.straight(7); //Only 7 rather than 10 since 3 have already been done in checking for green
  motors.wait();
  if (digitalRead(PIN_LEFT_COLOUR) == HIGH && digitalRead(PIN_RIGHT_COLOUR) == HIGH) {
    motors.straight(-11); //Optional, could just stay where we were BUT REMEMBER the implications of changing this on scanForLine!!!
    motors.wait();
    return true;  
  }
  else return false;
}

void scanForLine(){ //starts from 10cm forwards
  motors.rotate(360);
  motors.wait();
}
  
  

void setLineFollowingSpeeds(float currentLinePosition)
{
  
  
   if (currentLinePosition <= 0.0)
   {
      leftSpeed = leftSpeedFactor * (1.0 + 8 * currentLinePosition);
      rightSpeed = rightSpeedFactor;
   }
   else
   { 
      leftSpeed = leftSpeedFactor;
      rightSpeed = rightSpeedFactor * (1.0 - 8 *currentLinePosition);
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
