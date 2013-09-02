boolean reachedIntersectionLeft() {
  if (digitalRead(53) == HIGH) { //53 is pin for if Left colour sensor is on green (from the Leostick)
    return true;
  }
  else return false;
}

boolean reachedIntersectionRight() {
  if (digitalRead(51) == HIGH) { //51 is pin for if Right colour sensor is on green (from the Leostick)
    return true;
  }
  else return false;
}


void navigateIntersection(){//TODO
  turnLeft();
  intersectionCount++;
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
