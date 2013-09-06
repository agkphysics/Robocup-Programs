void moveWaterTower(){ //TODO
  
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
  motors.straight(1.5);
  motors.wait(); //could put while(motors.running() && !reachedEndTile()) motors.run(); here instead if gridlock is right by endtile.
  
  motors.setMaxSpeeds(leftSpeedFactor, rightSpeedFactor);
}
