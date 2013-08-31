#include <ColorRecognition.h>
#include <ColorRecognitionTCS230PI.h>

ColorRecognitionTCS230PI tcs230(8, 7, 6);


void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  Serial.begin(9600);
  
  tcs230.setup();
  
  /*
  Serial.println("Adjust white color, show something white to the sensor and press y."); 
  while(!Serial.available() && Serial.read() != 'y');
  Serial.read(); // just read the 'enter'
  Serial.println("Adjusting...");
  tcs230.adjustWhiteBalance();
  
  Serial.println("Adjust black color, show something black to the sensor and press y."); 
  while(!Serial.available() && Serial.read() != 'y');
  Serial.read(); // just read the 'enter'
  Serial.println("Adjusting...");
  tcs230.adjustBlackBalance();
  */
}

void loop()
{
  int red = tcs230.getRed();
  int green = tcs230.getGreen();
  int blue = tcs230.getBlue();
  
  Serial.print("R ");
  Serial.print(red);
  
  Serial.print(";G ");
  Serial.print(green);
  if (tcs230.isOnGreen()) digitalWrite(9, HIGH);
  else digitalWrite(9, LOW);
  
  Serial.print(";B ");
  Serial.print(blue);
  
  Serial.println();
  delay(1000);
}
