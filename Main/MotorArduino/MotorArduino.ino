/* To be uploaded to the Arduino controlling the two motors */

#include <AccelStepper.h>
#include <Wire.h>
#include <Motors.h>

#define MOTOR_ARDUINO_ADDRESS 0x33
#define PIN_LEFT_STEP 10
#define PIN_LEFT_DIRECTION 12
#define PIN_RIGHT_STEP 11
#define PIN_RIGHT_DIRECTION 13

AccelStepper leftMotor(AccelStepper::DRIVER, PIN_LEFT_STEP, PIN_LEFT_DIRECTION);
AccelStepper rightMotor(AccelStepper::DRIVER, PIN_RIGHT_STEP, PIN_RIGHT_DIRECTION);

Motors motors(leftMotor, rightMotor);

boolean running = false;

void recievedData(int numBytes)
{
    int code;
    char buffer1[25];
    char buffer2[25];
    float arg1, arg2;
    arg1 = 0.0;
    arg2 = 0.0;
    Serial.println("Received data: ");
    code = Wire.read();
    if (Wire.available()) arg1 = Wire.readBytesUntil(',', buffer1, 7);
    if (Wire.available()) arg2 = Wire.readBytes(buffer2, 7);
    Serial.print(code);
    Serial.print(", ");
    Serial.print(arg1);
    Serial.print(", ");
    Serial.println(arg2);

    /*
    for (int i = 0; Wire.available(); i++)
    {
        char c = Wire.read();
        if (c == ' ') 
        {
            i--;
            continue;
        }
        else if (c == ',') break;
        
        buffer1[i] = Wire.read();
    }
    for (int j = 0; Wire.available(); j++)
    {
        char c = Wire.read();
        buffer2[j] = Wire.read();
    }
    */

    if (1 <= code && code <= 4)
    {
        //arg1 = atof(buffer1);
        processData(code, arg1, 0.0);
    }
    else if (5 <= code && code <= 8)
    {
        //arg2 = atof(buffer2);
        processData(code, arg1, arg2);
    }
}

void requestedData()
{
    Serial.println("Got a request for data");
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
    /*
    motors.straight(20.0);
    while(motors.running()) motors.run();
    motors.rotate(90.0);
    while(motors.running()) motors.run();
    motors.straight(10.0);
    while(motors.running()) motors.run();
    motors.rotate(-60.0);
    while(motors.running()) motors.run();
    */
    motors.run();
}
