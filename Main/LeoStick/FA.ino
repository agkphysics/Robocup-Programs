void setCalibrationValues() { //Paste these in

//ROOM 10 Values DARK:
//Max left frequency values: 

left.maxFrequency[0] = 121323;

left.maxFrequency[1] = 114052;

left.maxFrequency[2] = 160246;

//Max right frequency values: 

right.maxFrequency[0] = 161273;

right.maxFrequency[1] = 150979;

right.maxFrequency[2] = 200326;

//Min left frequency values: 

left.minFrequency[0] = 16825;

left.minFrequency[1] = 16161;

left.minFrequency[2] = 22143;

//Min right frequency values: 

right.minFrequency[0] = 25582;

right.minFrequency[1] = 22094;

right.minFrequency[2] = 31066;



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
