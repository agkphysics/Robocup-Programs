/* To be uploaded to the Arduino controlling the light sensors and ultrasonic sensor. */

#include <QTRSensors.h>
#include <Ultrasonic.h>
#include <Wire.h>

#define LIGHT_ARDUINO_ADDRESS 0x07
#define PIN_TRIG 11
#define PIN_ECHO 10

Ultrasonic ultrasonic(PIN_TRIG, PIN_ECHO);
float lastDistance = 0.0;

QTRSensorsAnalog qtra((unsigned char[]) {3, 6, 7, 0, 1, 2}, 6, 9, QTR_NO_EMITTER_PIN); //({Pins}, number of sensors, number of samples per reading to average, emitterpin)

unsigned int currentSensorValues[6];
unsigned int lastReadLine = 2500;

boolean distMode = false;

void calibrateManually()
{
    int i;
    for (i = 0; i < 250; i++)  // make the calibration take about 5 seconds
    {
        qtra.calibrate();
        delay(15);
    }
}

void setupLineArray()
{
    
    Serial.println("Calibrating...");

    //*
    qtra.calibrate();
    //Aaron's House (Scary Mansion) Values:
    qtra.calibratedMinimumOn[0] = 25;
    qtra.calibratedMinimumOn[1] = 24;
    qtra.calibratedMinimumOn[2] = 24;
    qtra.calibratedMinimumOn[3] = 22;
    qtra.calibratedMinimumOn[4] = 26;
    qtra.calibratedMinimumOn[5] = 28;
    
    qtra.calibratedMaximumOn[0] = 589;
    qtra.calibratedMaximumOn[1] = 602;
    qtra.calibratedMaximumOn[2] = 533;
    qtra.calibratedMaximumOn[3] = 380;
    qtra.calibratedMaximumOn[4] = 589;
    qtra.calibratedMaximumOn[5] = 700;
    //*/
    
    //calibrateManually();
    
    Serial.println("Min values");
    for (int i = 0; i < 6; i++) Serial.println(qtra.calibratedMinimumOn[i]);
    Serial.println();
    Serial.println("Max values");
    for (int i = 0; i < 6; i++) Serial.println(qtra.calibratedMaximumOn[i]);
    
    Serial.println("Finished calibrating");
}

void requestedData()
{
    union u_tag
    {
        byte b[4];
        float fval;
    } u;
    
    if (!distMode) u.fval = (float)lastReadLine;
    else u.fval = lastDistance;
    
    Wire.write(u.b, 4);
}

void receivedData(int numBytes)
{
    if (Wire.read() == 1) distMode = true;
}

void setup()
{
    Wire.begin(LIGHT_ARDUINO_ADDRESS);
    Serial.begin(9600);
    setupLineArray();
    Wire.onRequest(requestedData);
    Wire.onReceive(receivedData);
}

void loop()
{
    if (!distMode) lastReadLine = qtra.readLine(currentSensorValues);
    else lastDistance = ultrasonic.distance();
    //Serial.println(lastReadLine);
    //Serial.println(lastDistance);
}
