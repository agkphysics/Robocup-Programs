void setup() {
  setupRobot(); //Includes calibrate line sensors

}

void loop(){

  
  setLineFollowingSpeeds();
  delay(2);
}

void runMotorLoop() {
  motors.run();
  yield();
}


/*

  */
  
     /* 
      if (reachedIntersection()){
        digitalWrite(13, HIGH);
        Serial.println("Reached intersection");
        //motors.rotate(90);
        //motors.wait();
        navigateIntersection();
        motors.straight(-1.0);
        delay(500);
        qtra.readCalibrated(currentSensorValues);
        delay(500);
        qtra.readCalibrated(currentSensorValues);
      }
      else {
        digitalWrite(13, LOW);
      }*/
