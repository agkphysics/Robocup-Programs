#include <Servo.h>
#include <Wire.h>

#define PIN_LIFT_MOTOR_UP 3
#define PIN_LIN_MOTOR_DOWN 5
#define SERVO_ARDUINO_ADDRESS 0x17

Servo closeArm;

void receivedData(int numBytes)
{
    int a = Wire.read();
    switch (a)
    {
    case 0:
        closeArm.write(0);
        delay(500);
        break;
    case 1:
        closeArm.write(60);
        delay(500);
        break;
    case 2:
        digitalWrite(PIN_LIFT_MOTOR_UP, HIGH);
        delay(4000);
        digitalWrite(PIN_LIFT_MOTOR_UP, LOW);
        break;
    case 3:
        digitalWrite(PIN_LIFT_MOTOR_DOWN, HIGH);
        delay(4000);
        digitalWrite(PIN_LIFT_MOTOR_DOWN, LOW);
        break;
    }
}

void setup()
{
    pinMode(PIN_LIFT_MOTOR_UP, OUTPUT);
    pinMode(PIN_LIFT_MOTOR_DOWN, OUTPUT);
    digitalWrite(PIN_LIFT_MOTOR_UP, LOW);
    digitalWrite(PIN_LIFT_MOTOR_DOWN, LOW);
    Wire.begin(SERVO_ARDUINO_ADDRESS);
    closeArm.attach(10);
    closeArm.write(60);
    delay(500);
    digitalWrite(10, LOW);
    Wire.onReceive(receivedData);
}

void loop() {}

