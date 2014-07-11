/* To be uploaded to the Arduino controlling the light sensors and ultrasonic sensor. */

#include <QTRSensors.h>
#include <Ultrasonic.h>
#include <Wire.h>

#define LIGHT_ARDUINO_ADDRESS 0x10
#define PIN_TRIG 11
#define PIN_ECHO 12

Ultrasonic ultrasonic(PIN_TRIG, PIN_ECHO);
int lastDistance = 0;

QTRSensorsAnalog qtra((unsigned char[]) {7,6,5,4,3,2,1,0}, 8, 9, 8); //({Pins}, number of sensors, number of samples per reading to average, emitterpin)

unsigned int currentSensorValues[8];
float lastReadLine = 3500.0;

boolean distMode = false;

void setupLineArray() {
    qtra.calibrate();

    //Competition Day Values:
    qtra.calibratedMinimumOn[0] = 37;
    qtra.calibratedMinimumOn[1] = 35;
    qtra.calibratedMinimumOn[2] = 36;
    qtra.calibratedMinimumOn[3] = 37;
    qtra.calibratedMinimumOn[4] = 35;
    qtra.calibratedMinimumOn[5] = 32;
    qtra.calibratedMinimumOn[6] = 36;
    qtra.calibratedMinimumOn[7] = 39;
    
    qtra.calibratedMaximumOn[0] = 70;
    qtra.calibratedMaximumOn[1] = 54;
    qtra.calibratedMaximumOn[2] = 59;
    qtra.calibratedMaximumOn[3] = 66;
    qtra.calibratedMaximumOn[4] = 56;
    qtra.calibratedMaximumOn[5] = 48;
    qtra.calibratedMaximumOn[6] = 59;
    qtra.calibratedMaximumOn[7] = 169;
}

void requestedData()
{
    char buffer[25];
    if (!distMode)
    {
        char *f_rl = dtostrf(lastReadLine, 3, 1, buffer);
        Wire.write(f_rl);
    }
    else
    {
        Wire.write(lastDistance);
    }
}

void receivedData(int numBytes)
{
    if (Wire.read() == 1) distMode = true;
}

void setup()
{
    Wire.begin(LIGHT_ARDUINO_ADDRESS);
    setupLineArray();
    Wire.onRequest(requestedData);
    Wire.onReceive(receivedData);
}

void loop()
{
    if (!distMode) lastReadLine = (float)qtra.readLine(currentSensorValues);
    else lastDistance = (int)ultrasonic.distance();
}
