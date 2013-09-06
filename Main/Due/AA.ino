//Includes-------------------------
#include <QTRSensors.h>
#include <Compass.h>
#include <Wire.h>
#include <Motors.h>
#include <AccelStepper.h>
#include <Scheduler.h>
#include <Servo.h>
#include <Ultrasonic.h>

//Definitions-----------------------
//Intersection Types for Map Array
#define ROUNDABOUT 1
#define SQUARE 2 //refers to squareDeadEnd, shortened to save time on the day
#define CIRCLE 3 //refers to circleDeadEnd, similarly shortened
#define GRIDLOCK 4
#define ENDTILE 5

//Directions
#define LEFT true
#define RIGHT false

//Pin Definitions:
#define PIN_LEFT_COLOUR 8
#define PIN_RIGHT_COLOUR 10
#define PIN_LEOSTICK_EXTRA 50
#define PIN_LIFT_MOTOR 9
#define PIN_TOWER_SWITCH 8
#define PIN_BOARD_LED 13
#define PIN_LEFT_STEP 7
#define PIN_LEFT_DIRECTION 6
#define PIN_RIGHT_STEP 5
#define PIN_RIGHT_DIRECTION 4

//Objects-----------------
Compass compass;
AccelStepper leftMotor(AccelStepper::DRIVER, PIN_LEFT_STEP, PIN_LEFT_DIRECTION);
AccelStepper rightMotor(AccelStepper::DRIVER, PIN_RIGHT_STEP, PIN_RIGHT_DIRECTION);
Motors motors(leftMotor, rightMotor);
Servo closeArm;
Ultrasonic ultrasonic(11, 12);
// sensors 0 through 7 are connected to analog inputs 7 through 0, respectively
QTRSensorsAnalog qtra((unsigned char[]) {7,6,5,4,3,2,1,0}, 8, 9, 8); //({Pins}, number of sensors, number of samples per reading to average, emitterpin)

