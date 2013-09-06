void setup() {
  setupRobot(); //Includes calibrate line sensors
  delay(5000); //To wait for leo-stick to boot up if we don't need to calibrate sensors
  
  printArrayCalibrationValues();
  
  motors.setMaxSpeeds(leftSpeedFactor, rightSpeedFactor);
  lineFollowingLoop(); //Blocks until end tile

}

void loop(){
}

void runMotorLoop() {
  motors.run();
  yield();
}

