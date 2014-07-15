/* To be uploaded to the Arduino controlling the two motors */

#include <AccelStepper.h>
#include <Wire.h>
#include <Motors.h>

#define MOTOR_ARDUINO_ADDRESS 0x20
#define PIN_LEFT_STEP 10
#define PIN_LEFT_DIRECTION 12
#define PIN_RIGHT_STEP 11
#define PIN_RIGHT_DIRECTION 13

AccelStepper leftMotor(AccelStepper::DRIVER, PIN_LEFT_STEP, PIN_LEFT_DIRECTION);
AccelStepper rightMotor(AccelStepper::DRIVER, PIN_RIGHT_STEP, PIN_RIGHT_DIRECTION);

Motors motors(leftMotor, rightMotor);

void recievedData(int numBytes)
{
    int code = 0;
    char buffer1[4];
    char buffer2[4];
    float arg1, arg2;
    arg1 = 0.0;
    arg2 = 0.0;
    Serial.print("Received data: ");
    code = Wire.read();
    Serial.print(code);
    
    //*
    for (int i = 0; Wire.available(); i++)
    {
        buffer1[i] = Wire.read();
    }
    union u_tag
    {
        byte b[4];
        float fval;
    } u;
    u.b[0] = buffer1[0];
    u.b[1] = buffer1[1];
    u.b[2] = buffer1[2];
    u.b[3] = buffer1[3];
    arg1 = u.fval;
    
    for (int j = 0; Wire.available(); j++)
    {
        buffer2[j] = Wire.read();
    }
    union t_tag
    {
        byte c[4];
        float fval;
    } t;
    t.c[0] = buffer2[0];
    t.c[1] = buffer2[1];
    t.c[2] = buffer2[2];
    t.c[3] = buffer2[3];
    arg2 = t.fval;
    //*/

    /*
    for (int i = 0; Wire.available(); i++)
    {
        char c = (char)Wire.read();
        if (c == ',') break;
        buffer1[i] = c;
    }
    for (int j = 0; Wire.available(); j++)
    {
        char c = (char)Wire.read();
        buffer2[j] = c;
    }
    //*/

    if (1 <= code && code <= 4)
    {
        //arg1 = atof(buffer1);    
        Serial.print(", ");
        Serial.println(arg1);
        processData(code, arg1, 0.0);
    }
    else if (5 <= code && code <= 8)
    {
        //arg2 = atof(buffer2);
        Serial.print(", ");
        Serial.print(arg1);
        Serial.print(", ");
        Serial.println(arg2);
        processData(code, arg1, arg2);
    }
}

void requestedData()
{
    Serial.println("Got a request for buffer1");
    Wire.write(motors.running() ? 1 : 0);
}

void processData(int code, float arg1, float arg2)
{
    switch(code)
    {
    case 1:
        motors.straight(arg1);
        //Could wait here.
        break;
    case 2:
        motors.rotate(arg1);
        break;
    case 3:
        motors.swingWithRight(arg1);
        break;
    case 4:
        motors.swingWithLeft(arg1);
        break;
    case 5:
        motors.setActiveSpeeds(arg1, arg2);
        break;
    case 6:
        motors.setSpeeds(arg1, arg2);   
        break;
    case 7:
        motors.setMaxSpeeds(arg1, arg2);
        break;
    case 8:
        motors.setAccelerations(arg1, arg2);
        break;
    }
}

void setup()
{
    Wire.begin(MOTOR_ARDUINO_ADDRESS);
    Serial.begin(9600);
    motors.setup();
    Wire.onReceive(recievedData);
    Wire.onRequest(requestedData);
}

void loop()
{
    //Serial.println("Loop");
    motors.run();
}
