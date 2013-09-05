void align() {
  float degreesToRotate = degreesToNearest90();
  Serial.print(degreesToRotate);
  motors.rotate(degreesToRotate);
  motors.wait();
}

float degreesToNearest90() {
    int currentHeading = (int)(compass.heading());
	
    int currentRelativeHeading = currentHeading - initialHeading;
    if (currentRelativeHeading < 0) {
      currentRelativeHeading = currentRelativeHeading + 360;
    }
	
    int closest90 = ((currentRelativeHeading + 45)/90)*90;
    return (float)(closest90 - currentRelativeHeading);
}
