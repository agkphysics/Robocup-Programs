float getReadLine()
{
    Wire.requestFrom(LIGHT_ARDUINO_ADDRESS, 3);
    char buffer[25];
    for (int i = 0; Wire.available(); i++)
    {
        buffer[i] = Wire.read();
    }
    return atof(buffer);
}

void lineFollowingLoop(){
  
  while(!reachedEndTile){
    float currentReadLine = getReadLine();
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
      motors.straight(-2);
      motors.wait();
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
  float newReadLine = getReadLine();
    
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
      leftSpeed = leftSpeedFactor * (1.0 - 24*currentLinePosition*currentLinePosition);
//      leftSpeed = leftSpeedFactor * (1.0 + 5*currentLinePosition);
      rightSpeed = rightSpeedFactor;
   }
   else
   { 
      leftSpeed = leftSpeedFactor;
      rightSpeed = rightSpeedFactor * (1.0 - 24 *currentLinePosition*currentLinePosition);
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

boolean leftDetectedGreen()
{
  Wire.requestFrom(COLOR_ARDUINO_ADDRESS, 1);
  if (Wire.available())
  {
      //boolean b = Wire.read() ? true : false;
      //Wire.read(); //Discard second byte
      //return b;
      return Wire.read() ? true : false;
  }
  return false;
}
    
boolean rightDetectedGreen() {
  Wire.requestFrom(COLOR_ARDUINO_ADDRESS, 2);
  if (Wire.available())
  {
      Wire.read(); //Discard 1st byte
      return Wire.read() ? true : false;
  }
  return false;
}
