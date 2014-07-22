void setup() {
  setupRobot(); //Includes calibrate line sensors
  delay(1000);
  motors.setMaxSpeeds(leftSpeedFactor, rightSpeedFactor);
  delay(50);
  lineFollowingLoop(); //Blocks until end tile
}

void loop() {}

