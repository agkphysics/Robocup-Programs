#include <Servo.h>
#include <Wire.h>

#define PIN_LIFT_MOTOR 9
#define SERVO_ARDUINO_ADDRESS 0x17

Servo closeArm;

void receivedData(int numBytes)
{
    int a = Wire.read();
    if(a == 0)
    {
        closeArm.write(0);
        delay(500);
    }
    else if(a == 1)
    {
        closeArm.write(60);
        delay(500);
    }
}

void setup()
{
    //pinMode(PIN_LIFT_MOTOR, OUTPUT);
    //digitalWrite(PIN_LIFT_MOTOR, LOW);
    Wire.begin(SERVO_ARDUINO_ADDRESS);
    closeArm.attach(10);
    closeArm.write(60);
    delay(500);
    digitalWrite(10, LOW);
    Wire.onReceive(receivedData);
}

void loop()
{
    
}
