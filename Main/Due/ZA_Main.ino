void setup(){
  setupAll();
  digitalWrite(PIN_BOARD_LED, LOW);
  delay(5000);
  digitalWrite(PIN_BOARD_LED, HIGH);
  while(digitalRead(PIN_TOWER_SWITCH) == LOW);
  digitalWrite(PIN_BOARD_LED, LOW);
  delay(1100); //So we press the switch on 3, 2, "1" then it will go on GO
  digitalWrite(PIN_BOARD_LED, HIGH);
  motors.setMaxSpeeds(leftSpeedFactor, rightSpeedFactor);
  lineFollowingLoop(); //Blocks until end tile
  endTile(canSide);
  while (true) {} // End of program, no need to do ANYTHING :)
}

void loop() {
}


void runMotorLoop() {
  motors.run();
  yield();
}

