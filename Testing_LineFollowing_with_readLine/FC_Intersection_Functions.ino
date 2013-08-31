boolean reachedIntersection(){ //TODO
  float currentBlackness = blackness();
  Serial.println(currentBlackness);
  if (currentBlackness>0.625){
    return true;
  }
  else return false;
}

void navigateIntersection(){//TODO
  
}
