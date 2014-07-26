/* To be uploaded to the Arduino controlling the color sensors. */

#include <ColorRecognition.h>
#include <ColorRecognitionTCS230PI.h>
#include <Wire.h>

#define COLOR_ARDUINO_ADDRESS 0x30

ColorRecognitionTCS230PI left(11, 5, 9);
ColorRecognitionTCS230PI right(10, 5, 9);

float redL, greenL;
float redR, greenR;
float leftFreq = 0.0;
float rightFreq = 0.0;
unsigned char lrgb[3], rrgb[3];

void calibrateSensors()
{
    Serial.println("Adjust left white color, show something white to the sensor and press y."); 
    waitForY();
    //delay(5000);
    Serial.println("Adjusting...");
    left.adjustWhiteBalance();  
  
    Serial.println("Adjust right white color, show something white to the sensor and press y."); 
    waitForY();
    //delay(5000);
    Serial.println("Adjusting...");
    right.adjustWhiteBalance();
  
    Serial.println("Adjust left black color, show something black to the sensor and press y."); 
    waitForY();
    //delay(5000);
    Serial.println("Adjusting...");
    left.adjustBlackBalance();


    Serial.println("Adjust right black color, show something black to the sensor and press y."); 
    waitForY();
    //delay(5000);
    Serial.println("Adjusting...");
    right.adjustBlackBalance();
  
    Serial.println();
    
    printCalibrationValues();
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
    left.maxFrequency[0] = 100;
    left.maxFrequency[1] = 100000;
    left.maxFrequency[2] = 4000;
    
    //Max right frequency values: 
    right.maxFrequency[0] = 100;
    right.maxFrequency[1] = 100000;
    right.maxFrequency[2] = 4000;
    
    //Min left frequency values: 
    left.minFrequency[0] = 0;
    left.minFrequency[1] = 15000;
    left.minFrequency[2] = 2000;
    
    //Min right frequency values: 
    right.minFrequency[0] = 0;
    right.minFrequency[1] = 15000;
    right.minFrequency[2] = 2000;
}

void requestedData()
{    
    int i = 0;
    (leftFreq >= 3000.0 && leftFreq <= 5200.0) ? i |= 1 : i |= 0; //Green on left
    (rightFreq >= 4500.0 && rightFreq <= 7500.0) ? i |= 2 : i |= 0; //Green on right
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
    
    //setCalibrationValues();
    
    //calibrateSensors();
    Wire.onRequest(requestedData);
    Wire.onReceive(receivedData);
}

void loop()
{
    
    digitalWrite(5, HIGH);
    digitalWrite(9, LOW);
    
    leftFreq = left.getFrequency(120);
    rightFreq = right.getFrequency(120);
    
    //*
    Serial.print(leftFreq);
    Serial.print(",");
    Serial.print(rightFreq);
    Serial.print(" : ");
    
    digitalWrite(5, HIGH);
    digitalWrite(9, HIGH);
    
    leftFreq = left.getFrequency(120);
    rightFreq = right.getFrequency(120);
    
    Serial.print(leftFreq);
    Serial.print(",");
    Serial.print(rightFreq);
    Serial.print(" : ");
    
    int i = 0;
    (leftFreq >= 3000.0 && leftFreq <= 6500.0) ? i |= 1 : i |= 0; //Green on left
    (rightFreq >= 4500.0 && rightFreq <= 9000.0) ? i |= 2 : i |= 0; //Green on right
    Serial.println(i);
    //*/
    
    //*/
    //delay(100);
    /*
    //Get left Sensor Values
    redL = (float)left.getRed();
    greenL = (float)left.getGreen();
    float blueL = (float)left.getBlue();

    //Get right sensor Values
    redR = (float)right.getRed();
    greenR = (float)right.getGreen();
    float blueR = (float)right.getBlue();
    
    Serial.print("RL, GL, RR, GR: ");
    Serial.print(redL);
    Serial.print(", ");
    Serial.print(greenL);
    Serial.print(", ");
    Serial.print(blueL);
    Serial.print(" ;; ");
    Serial.print(redR);
    Serial.print(", ");
    Serial.print(greenR);
    Serial.print(",");
    Serial.print(blueR);
    Serial.println(",");
    
    //left.fillRGB(lrgb);
    //right.fillRGB(rrgb);
    */
}
