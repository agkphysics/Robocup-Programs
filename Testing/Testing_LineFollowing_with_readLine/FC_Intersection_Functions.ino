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


void navigateGridlock(){//TODO
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
