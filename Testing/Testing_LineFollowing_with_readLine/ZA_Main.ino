void setup() {
  setupRobot(); //Includes calibrate line sensors
  //delay(1000); //To wait for leo-stick to boot up if we don't need to calibrate sensors
  printArrayCalibrationValues();
  
  motors.setMaxSpeeds(leftSpeedFactor, rightSpeedFactor);
  
  int intersectionCount = 0;
  while(!reachedEndTile){
    
    setLineFollowingSpeeds();
    
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
}

void loop(){
}

void runMotorLoop() {
  motors.run();
  yield();
}

