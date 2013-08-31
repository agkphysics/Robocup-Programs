boolean reachedIntersection(){ //TODO
  qtra.readCalibrated(currentSensorValues);
  unsigned int sum = 0;
  for (int i=0; i<8; i++) {
    sum += currentSensorValues[i];
  }
  
  Serial.println(sum);
  if (sum>5000){
    return true;
  }
  else return false;
}

void navigateIntersection(){//TODO
  
}
