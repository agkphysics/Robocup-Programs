#include <Wire.h>
#include <MotorDriver.h>

#define MOTOR_ARDUINO_ADDRESS 0x20
//MotorDriver motors(MOTOR_ARDUINO_ADDRESS);

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    Serial.println("Starting program...");
    //Serial.setTimeout(100);
    delay(500);
}

void loop()
{
    /*
    motors.setSpeeds(500.0, 500.0);
    motors.straight(20.0);
    motors.wait();
    motors.rotate(90.0);
    motors.wait();
    motors.straight(10.0);
    motors.wait();
    motors.rotate(-60.0);
    motors.wait();
    //*/
    
    //*
    union u_tag
    {
        byte b[4];
        float fval;
    } u;
    //*/
    
    for (int j = 0; j < 20; j++)
    {
        Wire.requestFrom(0x07, 4);
        for (int i = 0; Wire.available(); i++) u.b[i] = Wire.read();
        Serial.println(u.fval);
        delay(40);
    }
    
    Wire.beginTransmission(0x07);
    Wire.write(1);
    int e = Wire.endTransmission();
    delay(40);
}
