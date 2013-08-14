/* pinconsts.h - Pin constants for the robot */

/* IR LED Array */
#define lineFollowingPin_1 7
#define lineFollowingPin_2 6
#define lineFollowingPin_3 5
#define lineFollowingPin_4 4
#define lineFollowingPin_5 3
#define lineFollowingPin_6 2
#define lineFollowingPin_7 1
#define lineFollowingPin_8 0

/* Ultrasonic Sensor */
#define ultrasonicPinTrigger 12
#define ultrasonicPinEcho 13

/* Motors */
#define motorLeftDirPin 6
#define motorLeftStepPin 7
#define motorRightDirPin 4
#define motorRightStepPin 5

#define liftArmUpPin 2
#define liftArmClosePin 3

/* Switches */
//#define switchSuchAndSuch 1

//#include <Scheduler.h>


#include <AccelStepper.h>

AccelStepper leftMotor(AccelStepper::DRIVER, motorLeftStepPin, motorLeftDirPin);
AccelStepper rightMotor(AccelStepper::DRIVER, motorRightStepPin, motorRightDirPin);

#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1

void setupMotors()
{
	pinMode(motorLeftDirPin, OUTPUT);
	pinMode(motorLeftStepPin, OUTPUT);
	pinMode(motorRightDirPin, OUTPUT);
	pinMode(motorRightStepPin, OUTPUT);
        
        pinMode(liftArmUpPin, OUTPUT);
        pinMode(liftArmClosePin, OUTPUT);
}

double distanceToSteps(double dist)
{
  return (dist * 100) / (30.25 * 3.14159265358979);
}

/*void move(int motor, double dist)
{
  int steps = (int)distanceToSteps(dist);
  int pin = (motor == MOTOR_LEFT) ? motorLeftStepPin : motorRightStepPin;
  digitalWrite((motor == MOTOR_LEFT) ? motorLeftDirPin : motorRightDirPin, (dist < 0) ? LOW : HIGH);

  int i;
  for (i = 0; i < steps * 8; i++)
  {
    digitalWrite(pin, LOW);
    digitalWrite(pin, HIGH);
    delayMicroseconds(750);
  }
}
*/



#include <QTRSensors.h>

QTRSensorsAnalog lf((unsigned char[]){lineFollowingPin_1,lineFollowingPin_2,lineFollowingPin_3,lineFollowingPin_4,lineFollowingPin_5,lineFollowingPin_6,lineFollowingPin_7,lineFollowingPin_8}, 8);




void lineFollowing()
{
  
}


void setup()
{
  setupMotors();
  pinMode(13, OUTPUT); // For the led
  
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  leftMotor.setMaxSpeed(600);
  rightMotor.setMaxSpeed(600);
}

void loop()
{
  leftMotor.move(1000);
  rightMotor.move(1000);
  leftMotor.run();
  rightMotor.run();
  int leftSpeed = 500; //As would be calculated by linefollowing procedure
  int rightSpeed = 500; //As would be calculated by linefollowing procedure
  leftMotor.setSpeed(leftSpeed);
  leftMotor.setSpeed(rightSpeed);
  
}

