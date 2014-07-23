#include <Wire.h>
#include <MotorDriver.h>

#define MOTOR_ARDUINO_ADDRESS 0x20
MotorDriver motors(MOTOR_ARDUINO_ADDRESS);

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    Serial.println("Starting program...");
    
    
    /*
    motors.setMaxSpeeds(150.0, 150.0);
    motors.rotate(30.0);
    delay(5000);
    //motors.wait();
    motors.rotate(-60.0);
    delay(8000);
    //motors.wait();
    motors.rotate(30.0);
    delay(5000);
    //motors.wait();
    
    //*/
    
    
    //delay(7000);
}

void loop()
{
    //*
    //*/
    motors.setMaxSpeeds(1000.0, 1000.0);
    motors.rotate(360.0);
    //motors.straight(20.0);
    motors.wait();
    delay(1000);

    /*
    union u_tag
    {
        byte b[4];
        float fval;
    } u;
    // /
    
    for (int j = 0; j < 100; j++)
    {
        Wire.requestFrom(0x07, 4);
        for (int i = 0; Wire.available(); i++) u.b[i] = Wire.read();
        Serial.println(u.fval);
        delay(40);
    }
    //*/
}
