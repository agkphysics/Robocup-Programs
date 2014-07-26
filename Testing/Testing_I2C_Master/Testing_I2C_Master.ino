#include <Wire.h>
#include <MotorDriver.h>
#include <Compass.h>

#define MOTOR_ARDUINO_ADDRESS 0x20
MotorDriver motors(MOTOR_ARDUINO_ADDRESS);

Compass compass;

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    Serial.println("Starting program...");
    delay(1000);
    
    Wire.beginTransmission(0x07);
    Wire.write(1);
    Wire.endTransmission();
    delay(100);
}

void loop()
{
    /*
    motors.setMaxSpeeds(1000.0, 1000.0);
    motors.rotate(360.0);
    //motors.straight(20.0);
    motors.wait();
    delay(1000);
    //*/
    
    union u_tag
    {
        byte b[4];
        float fval;
    } u;
    
    Wire.requestFrom(0x07, 4);
    for (int i = 0; Wire.available(); i++) u.b[i] =  Wire.read();
    Serial.println(u.fval);
    delay(40);
    /*
    Wire.requestFrom(0x30, 6);
    for (int i = 0; i < 3 && Wire.available(); i++)
    {
        Serial.print(Wire.read());
        Serial.print(", ");
    }
    Serial.print("    ");
    for (int i = 0; i < 3 && Wire.available(); i++)
    {
        Serial.print(Wire.read());
        Serial.print(", ");
    }
    Serial.println();
    delay(1000);
    //*/
    
    /*
    int b = -1;
    Wire.requestFrom(0x30, 1);
    if (Wire.available()) b = Wire.read();
    Serial.print("Received: ");
    Serial.println(b);
    delay(40);
    //*/
    

    /*
    
    for (int j = 0; j < 100; j++)
    {
        Wire.requestFrom(0x07, 4);
        for (int i = 0; Wire.available(); i++) u.b[i] = Wire.read();
        Serial.println(u.fval);
        delay(40);
    }
    //*/
}
