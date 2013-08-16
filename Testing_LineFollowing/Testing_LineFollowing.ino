#include <Scheduler.h>

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



#include <AccelStepper.h>

AccelStepper leftMotor(AccelStepper::DRIVER, motorLeftStepPin, motorLeftDirPin);
AccelStepper rightMotor(AccelStepper::DRIVER, motorRightStepPin, motorRightDirPin);

int leftSpeedFactor = 500; //As would be calculated by linefollowing procedure
int rightSpeedFactor = 500; //As would be calculated by linefollowing procedure

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
  /* dist in in cm */
  return (dist * 100) / (3.025 * 3.14159265358979);
}




#include <QTRSensors.h>

QTRSensorsAnalog lf((unsigned char[]){lineFollowingPin_1,lineFollowingPin_2,lineFollowingPin_3,lineFollowingPin_4,lineFollowingPin_5,lineFollowingPin_6,lineFollowingPin_7,lineFollowingPin_8}, 8);
unsigned int currentlfValues[8];
unsigned int lfOffset[8] = {0,0,0,0,0,0,0,0};
const unsigned int linePositionFactor[8] = {-1.0, -5.0/7.0, -3.0/7.0, -1.0/7.0, 1.0/7.0, 3.0/7.0, 5.0/7.0, 1.0};
unsigned int currentMaxSensorValue = 0;

/* The following function does the bulk of the work processing all the sensor info */
void readLineFollowing()
{
  lf.read(currentlfValues);
  for (int i = 0; i < 8; i++)
  {
    currentlfValues[i] = currentlfValues[i] - lfOffset[i];
    if (currentlfValues[i] > currentMaxSensorValue) currentMaxSensorValue = currentlfValues[i];
  }
}

/* linePosition() returns a real number between -1 and 1 representing where the line is */
float linePosition()
{
  readLineFollowing();
  float pos;
  for (int i = 0; i < 8; i ++)
  {
    pos += (currentlfValues[i] / currentMaxSensorValue) * linePositionFactor[i];
  }
  return pos;
}

void lineFollowing()
{
  float linePos = linePosition();
  if (linePos <= 0.0)
  {
    leftMotor.setSpeed(leftSpeedFactor * (1.0 + 2.0 * linePos));
    rightMotor.setSpeed(rightSpeedFactor);
  }
  else
  {
    leftMotor.setSpeed(leftSpeedFactor);
    rightMotor.setSpeed(rightSpeedFactor * (1.0 - 2.0 * linePos));
  }
  yield();
}

void calibrateLineFollowing()
{
  unsigned int calibration[8];
  
  /* First stage is to place robot with IR LED array centred on black line. May not be needed */
  /* TODO: Finish */
  /*
  lf.read(calibration);
  unsigned int total;
  for (int i = 0; i < 8; i++)
  {
    total += calibration[i];
  }
  */
  
  delay(3000);
  
  /* Second stage is to place IR array on white so all sensors detect white */
  lf.read(calibration);
  for (int i = 0; i < 8; i++)
  {
    lfOffset[i] = calibration[i];
  }
  
  delay(3000);
}




void setup()
{
  pinMode(13, OUTPUT); // For the led
  setupMotors();
  calibrateLineFollowing();

  leftMotor.setMaxSpeed(600);
  rightMotor.setMaxSpeed(600);
  leftMotor.setAcceleration(10000);
  rightMotor.setAcceleration(10000);

  leftMotor.setSpeed(leftSpeedFactor);
  rightMotor.setSpeed(rightSpeedFactor);

  /* THis just indicates that the program is about to run */
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  
  leftMotor.move(5000000);
  rightMotor.move(-5000000);
 
  Scheduler.startLoop(motorLoop);
}

boolean useLeftMotor = true;
boolean useRightMotor = true;

void loop()
{
  lineFollowing();
  delay(50);
}

void motorLoop() {
  leftMotor.run();
  rightMotor.run();
  yield();
}
