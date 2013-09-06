void setCalibrationValues() { //Paste these in


//Saint Kents Comp Day Values:
//Max left frequency values: 

left.maxFrequency[0] = 105555;

left.maxFrequency[1] = 107189;

left.maxFrequency[2] = 141012;

//Max right frequency values: 

right.maxFrequency[0] = 151586;

right.maxFrequency[1] = 134803;

right.maxFrequency[2] = 174182;

//Min left frequency values: 

left.minFrequency[0] = 15986;

left.minFrequency[1] = 15626;

left.minFrequency[2] = 21060;

//Min right frequency values: 

right.minFrequency[0] = 23347;

right.minFrequency[1] = 20656;

right.minFrequency[2] = 27791;





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
