/* To be uploaded to the Arduino controlling the color sensors. */

#include <ColorRecognition.h>
#include <ColorRecognitionTCS230PI.h>
#include <Wire.h>

#define COLOR_ARDUINO_ADDRESS 0x17
#define PIN_LEFT_COLOUR 8
#define PIN_RIGHT_COLOUR 10

ColorRecognitionTCS230PI left(0, 2, 5);
ColorRecognitionTCS230PI right(1, 2, 5);

float redL, greenL;
float redR, greenR;

void setCalibrationValues()
{ 
    //Paste these in

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

void requestedData()
{
    ((greenL - redL) > 15) && (greenL/(greenL+redL) > 0.7) ? Wire.write(1) : Wire.write(0);
    ((greenR - redR) > 15) && (greenR/(greenR+redR) > 0.5) ? Wire.write(1) : Wire.write(0);
}

void setup()
{
    Wire.begin(COLOR_ARDUINO_ADDRESS);
    setCalibrationValues();
    Wire.onRequest(requestedData);
}

void loop()
{
    //Get left Sensor Values
    redL = left.getRed();
    greenL = left.getGreen();

    //Get right sensor Values
    redR = right.getRed();
    greenR = right.getGreen();
}
