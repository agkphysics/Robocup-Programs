#include <ColorRecognition.h>
#include <ColorRecognitionTCS230PI.h>

ColorRecognitionTCS230PI left(0, 2, 5);
ColorRecognitionTCS230PI right(1, 2, 5);

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  Serial.begin(9600);
  //calibrateSensors();
  
  left.maxFrequency[0] = 124346;
  left.maxFrequency[1] = 105406;
  left.maxFrequency[2] = 150162;

  right.maxFrequency[0] = 157795;
  right.maxFrequency[1] = 135947;
  right.maxFrequency[2] = 168626;
  
  
  left.minFrequency[0] = 18505;
  left.minFrequency[1] = 17639;
  left.minFrequency[2] = 23533;
  

  right.minFrequency[0] = 26273;
  right.minFrequency[1] = 22238;
  right.minFrequency[2] = 31290;
  
}

void loop()
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

void calibrateSensors(){
  while(!Serial.available() && Serial.read() != 'y');
  Serial.read(); // just read the 'enter'  
  Serial.println("Adjust left white color, show something white to the sensor and press y."); 
  while(!Serial.available() && Serial.read() != 'y');
  Serial.read(); // just read the 'enter'
  Serial.println("Adjusting...");
  left.adjustWhiteBalance();  
  Serial.print("Max left frequency values: ");
  for (int i = 0; i < 3; i++)
  {
    Serial.print(left.maxFrequency[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.println("Adjust right white color, show something white to the sensor and press y."); 
  while(!Serial.available() && Serial.read() != 'y');
  Serial.read(); // just read the 'enter'
  Serial.println("Adjusting...");
  right.adjustWhiteBalance();
  Serial.print("Max right frequency values: ");
  for (int i = 0; i < 3; i++)
  {
    Serial.print(right.maxFrequency[i]);
    Serial.print(" ");
  }
  Serial.println();
  
  Serial.println("Adjust left black color, show something black to the sensor and press y."); 
  while(!Serial.available() && Serial.read() != 'y');
  Serial.read(); // just read the 'enter'
  Serial.println("Adjusting...");
  left.adjustBlackBalance();
  Serial.print("Min left frequency values: ");
  for (int i = 0; i < 3; i++)
  {
    Serial.print(left.minFrequency[i]);
    Serial.print(" ");
  }
  Serial.println();
  
  Serial.println("Adjust right black color, show something black to the sensor and press y."); 
  while(!Serial.available() && Serial.read() != 'y');
  Serial.read(); // just read the 'enter'
  Serial.println("Adjusting...");
  right.adjustBlackBalance();
  Serial.print("Min right frequency values: ");
  for (int i = 0; i < 3; i++)
  {
    Serial.print(right.minFrequency[i]);
    Serial.print(" ");
  }
  Serial.println();
}
