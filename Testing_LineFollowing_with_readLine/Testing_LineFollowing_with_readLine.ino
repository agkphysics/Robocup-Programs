#include <QTRSensors.h>
#include <Compass.h>
#include <Wire.h>
#include <Motors.h>
#include <AccelStepper.h>
#include <Scheduler.h>

Compass compass;
AccelStepper leftMotor(AccelStepper::DRIVER, 7, 6);
AccelStepper rightMotor(AccelStepper::DRIVER, 5, 4);
Motors motors(leftMotor, rightMotor);

#define SAMPLES  9  // average 9 analog samples per sensor reading

// sensors 0 through 7 are connected to analog inputs 7 through 0, respectively
QTRSensorsAnalog qtra((unsigned char[]) {7,6,5,4,3,2,1,0}, 8, SAMPLES, QTR_NO_EMITTER_PIN);
unsigned int currentSensorValues[8];

float leftSpeed = 500.0; //Initial Speed (for testing purposes)
float rightSpeed = 500.0; //Initial Speed (for testing purposes)

float leftSpeedFactor = 500.0; //As would be calculated by linefollowing procedure
float rightSpeedFactor = 500.0; //As would be calculated by linefollowing procedure

void calibrateLineFollowing()
{
  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration
}

float linePosition()
{
  return (float)qtra.readLine(currentSensorValues) / 3500.0 - 1.0;
}

void lineFollowing()
{
  float currentLinePosition = linePosition();
  
  if (currentLinePosition <= 0.0)
  {
    leftSpeed = leftSpeedFactor * (1.0 + 5.0 * currentLinePosition);
    rightSpeed = rightSpeedFactor;
  }
  else
  {
    leftSpeed = leftSpeedFactor;
    rightSpeed = rightSpeedFactor * (1.0 - 5.0 * currentLinePosition);
  }

  motors.setActiveSpeeds(leftSpeed, rightSpeed);
}

void setup() {
  calibrateLineFollowing();

  Wire.begin();
  Scheduler.startLoop(runMotorLoop);
  motors.setup();
}

void loop(){
  lineFollowing();
  delay(1);
}

void runMotorLoop() {
  motors.run();
  yield();
}
