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

#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  9  // average 4 analog samples per sensor reading
#define EMITTER_PIN             QTR_NO_EMITTER_PIN  // emitter is controlled by digital pin 2

// sensors 0 through 7 are connected to analog inputs 7 through 0, respectively
QTRSensorsAnalog qtra((unsigned char[]) {7,6,5,4,3,2,1,0}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];


float leftSpeed = 500.0; //Initial Speed (for testing purposes)
float rightSpeed = 500.0; //Initial Speed (for testing purposes)

int leftSpeedFactor = 500; //As would be calculated by linefollowing procedure
int rightSpeedFactor = 500; //As would be calculated by linefollowing procedure

void setup() {

  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  
  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);

  Wire.begin();
  Scheduler.startLoop(runMotorLoop);
  motors.setup();
}

float linePosition()
{
  float lineReadScaled = (qtra.readLine(sensorValues)) / 3500; 
  return (lineReadScaled - 1);
}

void loop(){
  
  // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
  // To get raw sensor values, call:
  //  qtra.read(sensorValues); instead of unsigned int position = qtra.readLine(sensorValues);
  unsigned int position = qtra.readLine(sensorValues);
  
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  //Serial.println(); // uncomment this line if you are using raw values
  Serial.println(position); // comment this line out if you are using raw values
  
  float currentLinePosition = linePosition();
  
  if (currentLinePosition <= 0.0)
  {
    leftSpeed = (leftSpeedFactor * (1.0 + 2.0 * currentLinePosition));
    rightSpeed = (rightSpeedFactor);
  }
  else
  {
    leftSpeed = (leftSpeedFactor);
    rightSpeed = (rightSpeedFactor * (1.0 - 2.0 * currentLinePosition));
  }
  
  Serial.print(currentLinePosition);
  Serial.print ("  L: ");
  Serial.print(leftSpeed);
  Serial.print ("  R: ");
  Serial.print(rightSpeed);
  Serial.println(" ");

  //If this is working, just comment out motors.setActiveSpeeds and make the delay much shorter or take it out altogether
  //motors.setActiveSpeeds(leftSpeed, rightSpeed);
  delay(250); 
}

void runMotorLoop() {
  motors.run();
  yield();
}
