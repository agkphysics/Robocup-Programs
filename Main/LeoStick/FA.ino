void setCalibrationValues() { //Paste these in

//ROOM 10 Values:
//Max left frequency values: 
left.maxFrequency[0] = 115686;
left.maxFrequency[1] = 117810;
left.maxFrequency[2] = 152567;
//Max right frequency values: 
right.maxFrequency[0] = 159756;
right.maxFrequency[1] = 148797;
right.maxFrequency[2] = 186600;
//Min left frequency values: 
left.minFrequency[0] = 17640;
left.minFrequency[1] = 16564;
left.minFrequency[2] = 22352;
//Min right frequency values: 
right.minFrequency[0] = 28287;
right.minFrequency[1] = 24739;
right.minFrequency[2] = 34032;


}

void checkForAndOutputGreen()
{
  float redL, greenL;
  float redR, greenR;
  
  //Get left Sensor Values
  redL = left.getRed();
  greenL = left.getGreen();
  
  //Get right sensor Values
  redR = right.getRed();
  greenR = right.getGreen();
    
  Serial.print("Left values,");
  Serial.print(redL);
  Serial.print(",");
  Serial.print(greenL);
  Serial.print(",");
  
  Serial.print("Right values,");
  Serial.print(redR);
  Serial.print(",");
  Serial.print(greenR);
  Serial.print(",");
  Serial.println();
  
  Serial.print("LEFT GREEN,");
  if (((greenL - redL) > 15) && (greenL/(greenL+redL) > 0.7)) {
    digitalWrite(6, HIGH);
    Serial.print("1,");
  }
  else {
    digitalWrite(6, LOW);
    Serial.print("0,");
  }
  
  Serial.print("RIGHT GREEN,");
  if (((greenR - redR) > 15) && (greenR/(greenR+redR) > 0.5)) {
    digitalWrite(7, HIGH);
     Serial.print("1,");
  }
  else {
    digitalWrite(7, LOW);
    Serial.print("0,");
  }
}
