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
    Serial.println("Adjust left white color, show something white to the sensor and press y."); 
    //waitForY();
    delay(5000);
    Serial.println("Adjusting...");
  
    Serial.println("Adjust right white color, show something white to the sensor and press y."); 
    //waitForY();
    delay(5000);
    Serial.println("Adjusting...");
  
    Serial.println("Adjust left black color, show something black to the sensor and press y."); 
    //waitForY();
    delay(5000);
    Serial.println("Adjusting...");


    Serial.println("Adjust right black color, show something black to the sensor and press y."); 
    //waitForY();
    delay(5000);
    Serial.println("Adjusting...");
  
    Serial.println();
    */
    delay(1000);
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
    
    //*
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
