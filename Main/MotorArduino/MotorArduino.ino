/* To be uploaded to the Arduino controlling the two motors */

#include <AccelStepper.h>
#include <Wire.h>

#define MOTOR_ARDUINO_ADDRESS 0x01
#define PIN_LEFT_STEP 7
#define PIN_LEFT_DIRECTION 6
#define PIN_RIGHT_STEP 5
#define PIN_RIGHT_DIRECTION 4

AccelStepper leftMotor(AccelStepper::DRIVER, PIN_LEFT_STEP, PIN_LEFT_DIRECTION);
AccelStepper rightMotor(AccelStepper::DRIVER, PIN_RIGHT_STEP, PIN_RIGHT_DIRECTION);

void recievedData(int numBytes)
{
    byte code;
    char buffer1[25];
    char buffer2[25];
    float arg1, arg2;
    if (Wire.available()) code = Wire.read();
    
    for (int i = 0; Wire.available(); i++)
    {
        char c = Wire.read();
        if (c == ' ') continue;
        else if (c == ',')
        {
            i = 0;
            break;
        }
        buffer1[i] = Wire.read();
    }
    for (int i = 0; Wire.available(); i++)
    {
        char c = Wire.read();
        buffer2[i] = Wire.read();
    }

    if (code == 9) /* Running? */ (leftMotor.distanceToGo() != 0 || rightMotor.distanceToGo() != 0) ? Wire.write(1) : Wire.write(0);
    else if (1 <= code && code <= 4)
    {
        arg1 = atof(buffer1);
        processData(code, arg1, 0.0);
    }
    else if (5 <= code && code <= 8)
    {
        arg2 = atof(buffer2);
        processData(code, arg1, arg2);
    }
}

/*
long cmToSteps(float cm)
{
    return ((long)((cm * 1600.0)/(6.46 * 3.14159265358979)));
}
*/

#define cmToSteps(x) ((long)(((x) * 1600.0)/(6.46 * 3.14159265358979)))

void processData(byte code, float arg1, float arg2)
{
    switch(code)
    {
    case 1:
        leftMotor.move(cmToSteps(arg1));
        rightMotor.move(-cmToSteps(arg1));
        break;
    case 2:
        leftMotor.move(cmToSteps((arg1/360.0)*3.14159265358979*13.75)); //Note that 13.75 is the diameter that gives the most accurate movement for a 360 rotate
        rightMotor.move(cmToSteps((arg1/360.0)*3.14159265358979*13.75));
        break;
    case 3:
        leftMotor.move(0);
        rightMotor.move(-cmToSteps((arg1/360.0)*3.14159265358979*13.75*2));
        break;
    case 4:
        rightMotor.move(0);
        leftMotor.move(cmToSteps((arg1/360.0)*3.14159265358979*13.75*2));
        break;
    case 5:
        if (arg1 > 0)
        {
    	    leftMotor.move(1000000);
    	    leftMotor.setSpeed(arg1);
        }
        else if (arg1 < 0)
        {
    	    leftMotor.move(-1000000);
    	    leftMotor.setSpeed(arg1);
        }
        else
        {
    	    leftMotor.move(0);
    	    leftMotor.setSpeed(0);
        }
      
        if (arg1 > 0)
        {
    	    rightMotor.move(-1000000);
    	    rightMotor.setSpeed(-arg1);
        }
        else if (arg1 < 0)
        {
    	    rightMotor.move(1000000);
    	    rightMotor.setSpeed(-arg1);
        }
        else
        {
    	    rightMotor.move(0);
    	    rightMotor.setSpeed(0);
        }
        break;
    case 6:
        leftMotor.setSpeed(arg1);
        rightMotor.setSpeed(arg2);    
        break;
    case 7:
        leftMotor.setMaxSpeed(arg1);
        rightMotor.setMaxSpeed(arg2);
        break;
    case 8:
        leftMotor.setAcceleration(arg1);
        rightMotor.setAcceleration(arg2);
        break;
    }
}

void setup()
{
    Wire.begin(MOTOR_ARDUINO_ADDRESS);
    
    leftMotor.setMaxSpeed(900);
    rightMotor.setMaxSpeed(900);
    leftMotor.setAcceleration(10000);
    rightMotor.setAcceleration(10000);
    leftMotor.setSpeed(500); //Must be set once to allow movement, setSpeed(float, float) should be called after moveTo, not needed to be called after move()
    rightMotor.setSpeed(500); //Must be set once to allow movement
    
    Wire.onReceive(recievedData);
}

void loop()
{
    leftMotor.run();
    rightMotor.run();
}
