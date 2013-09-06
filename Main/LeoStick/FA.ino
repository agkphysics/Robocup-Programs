void setCalibrationValues() { //Paste these in

//Dan's House Values:
//Max left frequency values: 
left.maxFrequency[0] = 121241;
left.maxFrequency[1] = 117810;
left.maxFrequency[2] = 154773;

//Max right frequency values: 
right.maxFrequency[0] = 163398;
right.maxFrequency[1] = 151470;
right.maxFrequency[2] = 189868;

//Min left frequency values: 
left.minFrequency[0] = 20356;
left.minFrequency[1] = 18295;
left.minFrequency[2] = 24658;

//Min right frequency values: 
right.minFrequency[0] = 30860;
right.minFrequency[1] = 25161;
right.minFrequency[2] = 34289;




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
