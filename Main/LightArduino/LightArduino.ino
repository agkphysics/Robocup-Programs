/* To be uploaded to the Arduino controlling the light sensors and ultrasonic sensor. */

#include <QTRSensors.h>
#include <Ultrasonic.h>
#include <Wire.h>

#define LIGHT_ARDUINO_ADDRESS 0x07
#define PIN_TRIG 11
#define PIN_ECHO 10

Ultrasonic ultrasonic(PIN_TRIG, PIN_ECHO);
float lastDistance = 0.0;

QTRSensorsAnalog qtra((unsigned char[]) {2, 1, 0, 7, 6, 3}, 6, 9, QTR_NO_EMITTER_PIN); //({Pins}, number of sensors, number of samples per reading to average, emitterpin)

unsigned int currentSensorValues[6];
unsigned int lastReadLine = 2500;

boolean distMode = false;

void setupLineArray() {
    
    Serial.println("Calibrating...");
    
    /*
    int i;
    for (i = 0; i < 250; i++)  // make the calibration take about 5 seconds
    {
        qtra.calibrate();
        delay(20);
    }
    */

    qtra.calibrate();
    //Competition Day Values:
    qtra.calibratedMinimumOn[0] = 37;
    qtra.calibratedMinimumOn[1] = 35;
    qtra.calibratedMinimumOn[2] = 36;
    qtra.calibratedMinimumOn[3] = 37;
    qtra.calibratedMinimumOn[4] = 35;
    qtra.calibratedMinimumOn[5] = 32;
    
    qtra.calibratedMaximumOn[0] = 70;
    qtra.calibratedMaximumOn[1] = 54;
    qtra.calibratedMaximumOn[2] = 59;
    qtra.calibratedMaximumOn[3] = 66;
    qtra.calibratedMaximumOn[4] = 56;
    qtra.calibratedMaximumOn[5] = 48;
    
    Serial.println("Finished calibrating");
}

void requestedData()
{
    Serial.println("Got a request for data");
    //char buffer[25];
    union u_tag
    {
        byte b[4];
        float fval;
    } u;
    
    if (!distMode)
    {
        //char *f_rl = dtostrf(lastReadLine, 3, 1, buffer);
        //Wire.write(f_rl);>> 8)
        //Wire.write((lastReadLine >> 8) & 0x000F);
        //Wire.write(lastReadLine & 0x000F);
        //Serial.print("Wrote '");
        //Serial.print(f_rl);
        //Serial.println("'");
        u.fval = (float)lastReadLine;
    }
    else
    {
        u.fval = lastDistance;
    }
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
