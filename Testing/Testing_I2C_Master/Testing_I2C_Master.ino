#include <Wire.h>
#include <MotorDriver.h>

#define MOTOR_ARDUINO_ADDRESS 0x20
MotorDriver motors(MOTOR_ARDUINO_ADDRESS);

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
    //*
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
    
    /*
    union u_tag
    {
        byte b[4];
        float fval;
    } u;
    //*/
    
    /*
    u.fval = 0.0;
    Serial.print("Wrote runnning ");
    Wire.requestFrom(MOTOR_ARDUINO_ADDRESS, 1);
    Serial.println(Wire.read());
    delay(30);
    //*/
    
    /*
    char buffer[25];
    unsigned char b1, b2;
    Wire.requestFrom(0x10, 6);
    //Wire,requestFrom(0x10, 2);
    for (int i = 0; Wire.available(); i++)
    {
        buffer[i] = Wire.read();
        //b1 = buffer.read
    }
    float currentReadLine = atof(buffer);
    Serial.println(currentReadLine);
    delay(40);
    */
}
