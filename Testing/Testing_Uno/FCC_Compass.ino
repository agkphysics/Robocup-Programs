void align() {
    return;
  float degreesToRotate = degreesToNearest90();
  Serial.print(degreesToRotate);
  motors.rotate(degreesToRotate);
  motors.wait();
}

	 
float degreesToNearest90() {
    int currentHeading = (int)(compass.correctedHeading());
	
    int currentRelativeHeading = currentHeading - initialHeading;
    if (currentRelativeHeading < 0) {
      currentRelativeHeading = currentRelativeHeading + 360;
    }
    Serial.print("CurrentRelativeHeading: ");
    Serial.println(currentRelativeHeading);
    int closest90 = ((currentRelativeHeading + 45)/90)*90;
    Serial.print("closest90: ");
    Serial.println(closest90);
    return (float)(closest90 - currentRelativeHeading);
}
