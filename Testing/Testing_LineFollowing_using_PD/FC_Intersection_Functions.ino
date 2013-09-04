boolean reachedIntersection(){ //TODO
  float currentBlackness = blackness();
  Serial.println(currentBlackness);
  if (currentBlackness>0.8){
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
