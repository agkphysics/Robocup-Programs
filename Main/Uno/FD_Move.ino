void moveSquiggles() {
    motors.setMaxSpeeds(maxSpeedManualSections - 1000, maxSpeedManualSections - 1000);
    motors.straight(30);
    motors.wait();
    motors.rotate(90);
    motors.wait();
    motors.straight(10);
    motors.wait();
    motors.swingWithRight(180);
    motors.wait();
    motors.straight(22);
    motors.wait();
    motors.swingWithLeft(180);
    motors.wait();
    motors.straight(12);
    motors.wait();
    motors.rotate(-90);
    motors.wait();
    motors.setMaxSpeeds(leftSpeedFactor, rightSpeedFactor);
}

void moveWaterTower()
{
  motors.setMaxSpeeds(maxSpeedManualSections, maxSpeedManualSections);
  motors.straight(-3.0);
  motors.wait();
  motors.rotate(90.0);
  motors.wait();
  motors.straight(20.0);
  motors.wait();
  motors.rotate(-90.0);
  motors.wait();
  motors.straight(42.0);
  motors.wait();
  motors.rotate(-90.0);
  motors.wait();
  motors.straight(20.0);
  motors.wait();
  motors.rotate(90.0);
  motors.wait();
  motors.setMaxSpeeds(leftSpeedFactor, rightSpeedFactor);
}

void moveRoundabout(boolean triggeredByLeft) {
  motors.setMaxSpeeds(maxSpeedManualSections, maxSpeedManualSections);
  if(triggeredByLeft) {
    motors.straight(8.0);
    motors.wait();
    motors.rotate(-45.0);
    motors.wait();
    motors.straight(28.0);
    motors.wait();
    motors.rotate(-45.0);
    motors.wait();
    motors.straight(3.0);
    motors.wait();
  }
  else {
    motors.straight(8.0);
    motors.wait();
    motors.rotate(45.0);
    motors.wait();
    motors.straight(28.0);
    motors.wait();
    motors.rotate(45.0);
    motors.wait();
    motors.straight(3.0);
    motors.wait();
  }
  
  motors.setMaxSpeeds(leftSpeedFactor, rightSpeedFactor);
}

void moveSquareDeadEnd(boolean triggeredByLeft) {
  motors.setMaxSpeeds(maxSpeedManualSections, maxSpeedManualSections);
  if(triggeredByLeft) {
    motors.straight(8.0);
    motors.wait();
    motors.rotate(-90.0);
    motors.wait();
    motors.straight(12.0);
    motors.wait();
    motors.swingWithLeft(90.0);
    motors.wait();
    motors.straight(22.0);
    motors.wait();
    motors.swingWithLeft(90.0);
    motors.wait();
    motors.straight(12.0);
    motors.wait();
    motors.rotate(-90.0);
    motors.wait();
    motors.straight(3.0);
    motors.wait();
  }
  else {
    motors.straight(8.0);
    motors.wait();
    motors.rotate(90.0);
    motors.wait();
    motors.straight(12.0);
    motors.wait();
    motors.swingWithRight(90.0);
    motors.wait();
    motors.straight(22.0);
    motors.wait();
    motors.swingWithRight(90.0);
    motors.wait();
    motors.straight(12.0);
    motors.wait();
    motors.rotate(90.0);
    motors.wait();
    motors.straight(3.0);
    motors.wait();
  }
  motors.setMaxSpeeds(leftSpeedFactor, rightSpeedFactor);
}

void moveCircleDeadEnd(boolean triggeredByLeft) {
  motors.setMaxSpeeds(maxSpeedManualSections, maxSpeedManualSections);
  if(triggeredByLeft) {
    motors.straight(8.0);
    motors.wait();
    motors.rotate(-45.0);
    motors.wait();
    motors.straight(28.0);
    motors.wait();
    motors.rotate(90.0);
    motors.wait();
    motors.straight(28.0);
    motors.wait();
    motors.rotate(90.0);
    motors.wait();
    motors.straight(28.0);
    motors.wait();
    motors.rotate(-45.0);
    motors.wait();
    motors.straight(3.0);
    motors.wait();
  }
  else {
    motors.straight(8.0);
    motors.wait();
    motors.rotate(45.0);
    motors.wait();
    motors.straight(28.0);
    motors.wait();
    motors.rotate(-90.0);
    motors.wait();
    motors.straight(28.0);
    motors.wait();
    motors.rotate(-90.0);
    motors.wait();
    motors.straight(28.0);
    motors.wait();
    motors.rotate(45.0);
    motors.wait();
    motors.straight(3.0);
    motors.wait();
  }
  motors.setMaxSpeeds(leftSpeedFactor, rightSpeedFactor);
}


void moveGridlock(){
  motors.setMaxSpeeds(1500, 1500);
  motors.swingWithLeft(45.0);
  motors.wait();
  motors.straight(17.0);
  motors.wait();
  motors.rotate(-90.0);
  motors.wait();
  motors.straight(40.0);
  motors.wait();
  motors.rotate(90.0);
  motors.wait();
  motors.swingWithLeft(45.0);
  motors.wait();
  motors.straight(2.5);
  motors.wait();
  motors.swingWithRight(90.0);
  motors.wait();
  motors.straight(4.5);
  motors.wait(); //could put while(motors.running() && !reachedEndTile()) motors.run(); here instead if gridlock is right by endtile.
  
  motors.setMaxSpeeds(leftSpeedFactor, rightSpeedFactor);
}
