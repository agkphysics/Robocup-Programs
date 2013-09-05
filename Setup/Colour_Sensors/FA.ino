void calibrateSensors(){
  Serial.println("Adjust left white color, show something white to the sensor and press y."); 
  waitForY();
  Serial.println("Adjusting...");
  left.adjustWhiteBalance();  
  
  Serial.println("Adjust right white color, show something white to the sensor and press y."); 
  waitForY();
  Serial.println("Adjusting...");
  right.adjustWhiteBalance();
  
  Serial.println("Adjust left black color, show something black to the sensor and press y."); 
  waitForY();
  Serial.println("Adjusting...");
  left.adjustBlackBalance();
  
  
  Serial.println("Adjust right black color, show something black to the sensor and press y."); 
  waitForY();
  Serial.println("Adjusting...");
  right.adjustBlackBalance();
  
  Serial.println();
}


void printCalibrationValues(){
  Serial.println("//Max left frequency values: ");
  for (int i = 0; i < 3; i++)
  {
    Serial.print("left.maxFrequency[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.print(left.maxFrequency[i]);
    Serial.print(";");
    Serial.println();
  }
  Serial.println();
  
  Serial.println("//Max right frequency values: ");
  for (int i = 0; i < 3; i++)
  {
    Serial.print("right.maxFrequency[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.print(right.maxFrequency[i]);
    Serial.print(";");
    Serial.println();
  }
  Serial.println();


Serial.println("//Min left frequency values: ");
  for (int i = 0; i < 3; i++)
  {
    Serial.print("left.minFrequency[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.print(left.minFrequency[i]);
    Serial.print(";");
    Serial.println();
  }
  Serial.println();
    
    
  Serial.println("//Min right frequency values: ");
  for (int i = 0; i < 3; i++)
  {
    Serial.print("right.minFrequency[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.print(right.minFrequency[i]);
    Serial.print(";");
    Serial.println();
  }
  Serial.println();
}


void waitForY(){
  while(!Serial.available() && Serial.read() != 'y'); //Wait for serial to begin
  Serial.read(); // just read the 'enter'
}
