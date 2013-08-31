void setup() {
  setupRobot(); //Includes calibrate line sensors

}
boolean ledOn = false;
void loop(){
  /*
     if (reachedIntersection()){
        digitalWrite(13, HIGH);
        Serial.println("Reached intersection");
        //motors.rotate(90);
        //motors.wait();
  //      navigateIntersection();
  //      motors.straight(-1.0);
        delay(500);
        qtra.readCalibrated(currentSensorValues);
        delay(500);
        qtra.readCalibrated(currentSensorValues);
      }
      else {
        digitalWrite(13, LOW);
      }*/
 
  
  setLineFollowingSpeeds();
  delay(2);
}

void runMotorLoop() {
  while (!motors.runSpeed());
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
