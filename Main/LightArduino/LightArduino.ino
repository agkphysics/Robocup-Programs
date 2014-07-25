/* To be uploaded to the Arduino controlling the light sensors and ultrasonic sensor. */

#include <QTRSensors.h>
#include <Ultrasonic.h>
#include <Wire.h>

#define LIGHT_ARDUINO_ADDRESS 0x07
#define PIN_TRIG 11
#define PIN_ECHO 10

Ultrasonic ultrasonic(PIN_TRIG, PIN_ECHO);
float lastDistance = 0.0;

QTRSensorsAnalog qtra((unsigned char[]) {6, 3, 7, 0, 1, 2}, 6, 9, QTR_NO_EMITTER_PIN); //({Pins}, number of sensors, number of samples per reading to average, emitterpin)

unsigned int currentSensorValues[6];
unsigned int lastReadLine = 2500;

boolean distMode = false;
boolean returnAverage = false;

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
    qtra.calibratedMinimumOn[0] = 26;
    qtra.calibratedMinimumOn[1] = 27;
    qtra.calibratedMinimumOn[2] = 26;
    qtra.calibratedMinimumOn[3] = 24;
    qtra.calibratedMinimumOn[4] = 28;
    qtra.calibratedMinimumOn[5] = 30;
    
    qtra.calibratedMaximumOn[0] = 124;
    qtra.calibratedMaximumOn[1] = 146;
    qtra.calibratedMaximumOn[2] = 65;
    qtra.calibratedMaximumOn[3] = 37;
    qtra.calibratedMaximumOn[4] = 213;
    qtra.calibratedMaximumOn[5] = 375;
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
    
    if (returnAverage)
    {
        float sum = 0.0;
        for (int i = 0; i < 6; i++) sum += currentSensorValues[i];
        u.fval = sum / 6.0;
        Wire.write(u.b, 4);
        returnAverage = false;
        return;
    }
    
    if (!distMode) u.fval = (float)lastReadLine;
    else u.fval = lastDistance;
    
    Wire.write(u.b, 4);
}

void receivedData(int numBytes)
{
    int a = Wire.read();
    if (a == 1) distMode = true;
    else if (a == 2) returnAverage = true;
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
    //Serial.print(lastReadLine);
    //Serial.print(" : ");
    //float sum = 0.0;
    //for (int i = 0; i < 6; i++) sum += currentSensorValues[i];
    //Serial.println(sum / 6.0);
    //Serial.println(lastDistance);
}
