void setup() {
  setupRobot(); //Includes calibrate line sensors
  /*while(true) {
    setLineFollowingSpeeds();
    if (reachedIntersection()){
      digitalWrite(13, HIGH);
      Serial.println("Reached intersection");
    }
    else {
      digitalWrite(13, LOW);
    }
    delay(1);
  }
  */
}

void loop(){
  setLineFollowingSpeeds();
  yield();
}

void runMotorLoop() {
  motors.run();
  yield();
}

