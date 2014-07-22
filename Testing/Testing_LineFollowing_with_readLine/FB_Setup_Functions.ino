void setupRobot(){
  Wire.begin();
  Serial.begin(9600);
  
  delay(500); //To let compass sensor protocol get ready
  //initialHeading = (int)compass.correctedHeading();
}
