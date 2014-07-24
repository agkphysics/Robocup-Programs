/* To be uploaded to the Arduino controlling the color sensors. */

#include <ColorRecognition.h>
#include <ColorRecognitionTCS230PI.h>
#include <Wire.h>

#define COLOR_ARDUINO_ADDRESS 0x30

ColorRecognitionTCS230PI left(11, 5, 9);
ColorRecognitionTCS230PI right(10, 5, 9);

float redL, greenL;
float redR, greenR;
unsigned char lrgb[3], rrgb[3];

void calibrateSensors()
{
    Serial.println("Adjust left white color, show something white to the sensor and press y."); 
    //waitForY();
    delay(5000);
    Serial.println("Adjusting...");
    left.adjustWhiteBalance();  
  
    Serial.println("Adjust right white color, show something white to the sensor and press y."); 
    //waitForY();
    delay(5000);
    Serial.println("Adjusting...");
    right.adjustWhiteBalance();
  
    Serial.println("Adjust left black color, show something black to the sensor and press y."); 
    //waitForY();
    delay(5000);
    Serial.println("Adjusting...");
    left.adjustBlackBalance();


    Serial.println("Adjust right black color, show something black to the sensor and press y."); 
    //waitForY();
    delay(5000);
    Serial.println("Adjusting...");
    right.adjustBlackBalance();
  
    Serial.println();
    
    //printCalibrationValues();
}

void printCalibrationValues()
{
  Serial.println("//Max left frequency values: ");
  for (int i = 0; i < 3; i++)
  {
    Serial.print("left.maxFrequency[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.print(left.maxFrequency[i]);
    Serial.println(";");
  }
  
  Serial.println("//Max right frequency values: ");
  for (int i = 0; i < 3; i++)
  {
    Serial.print("right.maxFrequency[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.print(right.maxFrequency[i]);
    Serial.println(";");
  }


Serial.println("//Min left frequency values: ");
  for (int i = 0; i < 3; i++)
  {
    Serial.print("left.minFrequency[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.print(left.minFrequency[i]);
    Serial.println(";");
  }
    
    
  Serial.println("//Min right frequency values: ");
  for (int i = 0; i < 3; i++)
  {
    Serial.print("right.minFrequency[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.print(right.minFrequency[i]);
    Serial.println(";");
  }
}

void waitForY()
{
    while(!Serial.available() && Serial.read() != 'y'); //Wait for serial to begin
    Serial.read(); // just read the 'enter'
}

void setCalibrationValues()
{ 
    //Paste these in

    //Saint Kents Comp Day Values:
    //Max left frequency values: 
    left.maxFrequency[0] = 1000;
    left.maxFrequency[1] = 500000;
    left.maxFrequency[2] = 2000;
    
    //Max right frequency values: 
    right.maxFrequency[0] = 1000;
    right.maxFrequency[1] = 500000;
    right.maxFrequency[2] = 2000;
    
    //Min left frequency values: 
    left.minFrequency[0] = 0;
    left.minFrequency[1] = 15000;
    left.minFrequency[2] = 0;
    
    //Min right frequency values: 
    right.minFrequency[0] = 0;
    right.minFrequency[1] = 15000;
    right.minFrequency[2] = 0;
}

void requestedData()
{
    byte b[6];
    b[0] = lrgb[0];
    b[1] = lrgb[1];
    b[2] = lrgb[2];
    b[3] = rrgb[0];
    b[4] = rrgb[1];
    b[5] = rrgb[2];
    Wire.write(b, 6);
    return;
    
    int i = 0;
    ((greenL - redL) > 15.0) && (greenL/(greenL+redL) > 0.7) ? i |= 1 : i |= 0; //Green on left
    ((greenR - redR) > 15.0) && (greenR/(greenR+redR) > 0.5) ? i |= 2 : i |= 0; //Green on right
    Wire.write(i);
}

void receivedData(int numBytes)
{
    
}

void setup()
{
    Wire.begin(COLOR_ARDUINO_ADDRESS);
    Serial.begin(9600);
    pinMode(6, OUTPUT); //s0
    pinMode(3, OUTPUT); //s1
    digitalWrite(6, HIGH);
    digitalWrite(3, HIGH);
    
    setCalibrationValues();
    
    //calibrateSensors();
    Wire.onRequest(requestedData);
    Wire.onReceive(receivedData);
}

void loop()
{
    //Get left Sensor Values
    //redL = (float)left.getRed();
    //greenL = (float)left.getGreen();

    //Get right sensor Values
    //redR = (float)right.getRed();
    //greenR = (float)right.getGreen();
    
    left.fillRGB(lrgb);
    right.fillRGB(rrgb);
}
