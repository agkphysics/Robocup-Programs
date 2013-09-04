void setup() {
  
  
  setupRobot(); //Includes calibrate line sensors
  //delay(1000); //To wait for leo-stick to boot up if we don't need to calibrate sensors
  
  
  for (int i = 0; i < 8; i++)
  {
    Serial.print(qtra.calibratedMinimumOn[i]);
    Serial.print(" ");
  }
  Serial.println();
  for (int i = 0; i < 8; i++)
  {
    Serial.print(qtra.calibratedMaximumOn[i]);
    Serial.print(" ");
  }
  Serial.println();
  
  motors.setMaxSpeeds(leftSpeedFactor, rightSpeedFactor);
  
  while(!reachedEndTile()){
    
    setLineFollowingSpeeds();
    
    if(reachedIntersectionRight()){
      intersectionCount++;
      if (intersectionCount == gridlockIntersection){
        navigateGridlock();
      }
      else turnRight();

    }
    
    if(reachedIntersectionLeft()){
      intersectionCount++;
      if (intersectionCount == gridlockIntersection){
        navigateGridlock();
      }
      else turnLeft();
    }
    
    if(reachedWaterTower()){
      navigateWaterTower();
    }
    delay(2);
  }
}

void loop(){
}

void runMotorLoop() {
  motors.run();
  yield();
}

