/* To be uploaded to the Arduino controlling the Ultrasonic sensor */

#include <Ultrasonic.h>
#include <Wire.h>

#define ULTRASONIC_ARDUINO_ADDRESS 0x07
#define PIN_TRIG 11
#define PIN_ECHO 12

Ultrasonic ultrasonic(PIN_TRIG, PIN_ECHO);
int lastDistance = 0;

void requestedData()
{
    Wire.write(lastDistance);
}

void setup()
{
    Wire.begin(ULTRASONIC_ARDUINO_ADDRESS);
    Wire.onRequest(requestedData);
}

void loop()
{
    lastDistance = (int)ultrasonic.distance();
}
