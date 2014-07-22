float getReadLine()
{
    union u_tag
    {
        byte b[4];
        float fval;
    } u;
    
    Wire.requestFrom(LIGHT_ARDUINO_ADDRESS, 4);
    for (int i = 0; Wire.available(); i++) u.b[i] = Wire.read();
    delay(40);
    return u.fval;
}

void lineFollowingLoop()
{
  int intersectionCount = 0;
  while(!reachedEndTile){
    float currentReadLine = (float)getReadLine();
    float currentLinePosition = linePosition(currentReadLine);
    
    if (currentReadLine != 0.0 && currentReadLine != 5000.0) {
      setLineFollowingSpeeds(currentLinePosition);
    
      if(reachedIntersectionLeft()){
        navigateIntersection(LEFT, intersectionCount);
        intersectionCount++;
      }
    
      if(reachedIntersectionRight()){
        navigateIntersection(RIGHT, intersectionCount);
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
  return false;
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
  float lineReadScaled = currentReadLine / 2500.0; 
  return (lineReadScaled - 1.0);
}

