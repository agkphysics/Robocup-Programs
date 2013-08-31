
void setup() {
  setupRobot(); //Includes calibrate line sensors
  
  while(!reachedEndTile()){
    setLineFollowingSpeeds();
    delay(1);
  }
}

void loop(){
}

void runMotorLoop() {
  motors.run();
  yield();
}
