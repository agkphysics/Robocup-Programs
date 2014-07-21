int getDistance()
{
    union u_tag
    {
        byte b[4];
        float fval;
    } u;
    
    Wire.requestFrom(LIGHT_ARDUINO_ADDRESS, 4);
    for (int i = 0; Wire.available(); i++) u.b[i] =  Wire.read();
    return u.fval;
}

void endTile(boolean left)
{
  motors.straight(5.0);
  motors.wait();
  float endTileInitialHeading = compass.heading();
  
  Wire.beginTransmission(LIGHT_ARDUINO_ADDRESS);
  Wire.write(1);
  Wire.endTransmission();
  
  motors.setMaxSpeeds(2500, 2500);
  motors.straight(0.0);
  
  if (left) motors.rotate(-90.0);
  motors.wait();
  
  motors.setMaxSpeeds(150, 150);
  
  motors.rotate(90.0);
  float dist = 120;
  float headingToCan = 0.0;
  while (true)
  {
    /* Search for can */
    while (motors.running())
    {
      float currentDist = getDistance();
      if (currentDist < dist)
      {
        headingToCan = compass.heading();
        dist = currentDist;
      }
    }
    if (dist <= 100.0) break;
    else
    {
      dist = 120.0;
      headingToCan = 0.0;
      
      motors.setMaxSpeeds(2000, 2000);
      motors.rotate(-90);
      motors.wait();
      delay(2000);
      motors.setMaxSpeeds(150, 150);
      motors.rotate(90.0);
    }
  }
  float finishHeading = compass.heading();
  
  motors.setMaxSpeeds(750, 750);

  //motors.rotate(degreesToRotateToTargetCompassDirection(headingToCan));
  //*
  while (abs(compass.heading() - headingToCan) > 2.0)
  {
    motors.rotate(-1.0);
    motors.wait();
  }
  //*/
  
  /* An extra few degrees just in case... */
  if (dist >= 40.0) motors.rotate(0.0);
  else motors.rotate(-8.0);
  motors.wait();
  
  int distToCan = dist;
  motors.straight(distToCan);
  motors.wait();
  
  /* Swing to the right in case the can is too far right */
  if (dist >= 40) motors.swingWithLeft(45);
  else motors.swingWithLeft(45.0);
  motors.wait();
  delay(250);
  
  Wire.beginTransmission(SERVO_ARDUINO_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  delay(750);
  
  motors.setMaxSpeeds(2500, 2500);
  if (dist >= 40) motors.swingWithLeft(-45);
  else motors.swingWithLeft(-45.0);
  motors.wait();
  
  motors.straight(0.0);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  
  /* Lift arm */
  digitalWrite(PIN_LIFT_MOTOR, HIGH);
  delayMicroseconds(4000000);
  digitalWrite(PIN_LIFT_MOTOR, LOW);

  motors.straight((float)-distToCan);
  motors.wait();
  
  if (left) motors.rotate(-10.0);
  else motors.rotate(10.0);
  
  //motors.rotate(degreesToRotateToTargetCompassDirection(endTileInitialHeading));
  //*
  if (left)
  {
    while (abs(compass.heading() - endTileInitialHeading) > 2.0)
    {
      motors.rotate(1.0);
      motors.wait();
    }
  }
  else
  {
    while (abs(compass.heading() - endTileInitialHeading) > 2.0)
    {
      motors.rotate(-1.0);
      motors.wait();
    }
  }
  //*/
  
  motors.straight(50.0);//Added 3cm to original distance
  motors.wait();
  
  /* Drop can etc... */
  Wire.beginTransmission(SERVO_ARDUINO_ADDRESS);
  Wire.write(1);
  Wire.endTransmission();
  
  delay(400);
  motors.swingWithLeft(-20.0);
  motors.wait();
  
  motors.straight(-15.0);
  motors.wait();
  
  digitalWrite(PIN_BOARD_LED, HIGH);
}
