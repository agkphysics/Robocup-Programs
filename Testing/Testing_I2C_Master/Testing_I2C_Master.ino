#include <Wire.h>
#include <MotorDriver.h>

MotorDriver motors(0x01);

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    Serial.println("Starting program...");
    Serial.setTimeout(100);
    delay(500);
}

void loop()
{
    motors.setSpeeds(500.0, 500.0);
    motors.straight(20.0);
    //motors.wait();
    motors.rotate(90.0);
    motors.wait();
    motors.straight(10.0);
    motors.wait();
    motors.rotate(-60.0);
    motors.wait();
}
