void navigateIntersection(boolean triggeredByLeft) {
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
