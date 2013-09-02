void setup() {
  setupRobot(); //Includes calibrate line sensors
  //delay(1000); //To wait for leo-stick to boot up if we don't need to calibrate sensors
  while(!reachedEndTile()){
    
    setLineFollowingSpeeds();
    
    if(reachedIntersectionRight()){
      turnRight();
    }
    
    if(reachedIntersectionLeft()){
      turnLeft();
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

