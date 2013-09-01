void setup() {
  setupRobot(); //Includes calibrate line sensors
}

void loop(){
  setLineFollowingSpeeds();
    //  Serial.println(blackness());
  if(blackness()>1.1){
  //  Serial.print("   Intersection");
    navigateIntersection();
  }
  delay(2);
}


void runMotorLoop() {
  motors.run();
  yield();
}
