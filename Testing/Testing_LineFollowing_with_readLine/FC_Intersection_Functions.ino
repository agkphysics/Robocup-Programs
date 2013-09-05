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
  if(triggeredByLeft) {
    //TODO
  }
  else {
    //TODO
  }
}

void moveSquareDeadEnd(boolean triggeredByLeft) {
  if(triggeredByLeft) {
    motors.setMaxSpeeds(maxSpeedManualSections, maxSpeedManualSections);
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
    motors.setMaxSpeeds(leftSpeedFactor, rightSpeedFactor);
  }
  else {
    motors.setMaxSpeeds(maxSpeedManualSections, maxSpeedManualSections);
    motors.straight(8.0);
    motors.wait();
    motors.rotate(90.0);
    motors.wait();
    motors.straight(12.0);
    motors.wait();
    motors.swingWithRight(-90.0);
    motors.wait();
    motors.straight(22.0);
    motors.wait();
    motors.swingWithRight(-90.0);
    motors.wait();
    motors.straight(12.0);
    motors.wait();
    motors.rotate(90.0);
    motors.wait();
    motors.straight(3.0);
    motors.wait();
    motors.setMaxSpeeds(leftSpeedFactor, rightSpeedFactor);
  }
}

void moveCircleDeadEnd(boolean triggeredByLeft) {
  if(triggeredByLeft) {
    //TODO
  }
  else {
    //TODO
  }
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
  if (digitalRead(53) == HIGH) { //53 is pin for if Left colour sensor is on green (from the Leostick)
    return true;
  }
  else return false;
}

boolean reachedIntersectionRight() {
  if (digitalRead(49) == HIGH) { //51 is pin for if Right colour sensor is on green (from the Leostick)
    return true;
  }
  else return false;
}
