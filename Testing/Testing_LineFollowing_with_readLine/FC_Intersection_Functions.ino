void navigateIntersection(boolean triggeredByLeft, int intersectionCount) {
  int currentIntersection;
  if(intersectionCount > maxArrayIndex) currentIntersection = ENDTILE;
  else currentIntersection = mapArray[intersectionCount];
  
  switch(currentIntersection) {
    case ROUNDABOUT:
      align();
      moveRoundabout(triggeredByLeft);
      align();
      break;
    case SQUARE:
      align();
      moveSquareDeadEnd(triggeredByLeft);
      align();
      break;
    case CIRCLE:
      align();
      moveCircleDeadEnd(triggeredByLeft);
      align();
      break;
    case GRIDLOCK:
      align();
      moveGridlock();
      align();
      break;
    case ENDTILE:
      reachedEndTile = true;
      align();
      break;
    default:
      align();
      turn(triggeredByLeft);
      align();
  }
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

void turn(boolean triggeredByLeft) {
  if (triggeredByLeft) turnLeft();
  else turnRight();
}


void turnRight() {
  motors.straight(10);
  motors.wait();
  motors.rotate(90);
  motors.wait();
}


void turnLeft() {
  motors.straight(10);
  motors.wait();
  motors.rotate(-90);
  motors.wait();
}
  
boolean reachedIntersectionLeft() {
  if (digitalRead(PIN_LEFT_COLOUR) == HIGH) { 
    return true;
  }
  else return false;
}

boolean reachedIntersectionRight() {
  if (digitalRead(PIN_RIGHT_COLOUR) == HIGH) {
    return true;
  }
  else return false;
}
