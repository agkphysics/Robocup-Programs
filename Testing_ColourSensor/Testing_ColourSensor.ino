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

void loop()
{
  int redL, greenL, blueL;
  int redR, greenR, blueR;
  
  redL = left.getRed();
  delay(50);
  greenL = left.getGreen();
  delay(50);
  blueL = left.getBlue();
  delay(50);
  
  redR = right.getRed();
  delay(50);
  greenR = right.getGreen();
  delay(50);
  blueR = right.getBlue();
  delay(50);
  
  /*
  unsigned char *values = left.getRawValues();
  
  Serial.print("Values: (");
  for (int i = 0; i < 3; i++)
  {
    Serial.print(values[i]);
    Serial.print(", ");
  }
  Serial.print(")");
  */
  
  Serial.print("Left values: (");
  Serial.print(redL);
  Serial.print(", ");
  Serial.print(greenL);
  Serial.print(", ");
  Serial.print(blueL);
  Serial.print(")\t");
  
  Serial.print("Right values: (");
  Serial.print(redR);
  Serial.print(", ");
  Serial.print(greenR);
  Serial.print(", ");
  Serial.print(blueR);
  Serial.print(")");
  
  if (abs(redL - 15) < 7 && abs(greenL - 40) < 7 && abs(blueL - 20) < 7) 
  {
    digitalWrite(6, HIGH);
    digitalWrite(13, HIGH);
  }
  else
  {
    digitalWrite(6, LOW);
    digitalWrite(13, LOW);
  }
  
  if (abs(redR - 15) < 7 && abs(greenR - 40) < 7 && abs(blueR - 20) < 7)
  {
    digitalWrite(7, HIGH);
    digitalWrite(13, HIGH);
  }
  else
  {
    digitalWrite(7, LOW);
    digitalWrite(13, LOW);
  }
  
  Serial.println();
  delay(700);
}
