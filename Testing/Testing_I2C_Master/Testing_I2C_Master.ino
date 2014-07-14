#include <Wire.h>
#include <MotorDriver.h>

MotorDriver motors(0x33);

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
    delay(40);
    motors.straight(20.0);
    //motors.wait();
    delay(5000);
    motors.rotate(90.0);
    motors.wait();
    motors.straight(10.0);
    motors.wait();
    motors.rotate(-60.0);
    motors.wait();
    //*/
    
    int e;
    Wire.beginTransmission(0x33);
    Wire.write(1);
    Wire.write("20.0");
    Serial.print("Wrote straight 20.0 ");
    e = Wire.endTransmission();
    Serial.println(e);
    delay(40);
    
    delay(5000);
    
    Wire.beginTransmission(0x33);
    Wire.write(2);
    Wire.write("90.0");
    Serial.print("Wrote rotate 90.0 ");
    e = Wire.endTransmission();
    Serial.println(e);
    delay(40);
    
    delay(5000);
    
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
