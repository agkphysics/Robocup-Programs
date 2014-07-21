//Includes-------------------------
#include <Compass.h>
#include <Wire.h>
#include <MotorDriver.h>

//Definitions-----------------------
//Intersection Types for Map Array
#define ROUNDABOUT 1
#define SQUARE 2 //refers to squareDeadEnd, shortened to save time on the day
#define CIRCLE 3 //refers to circleDeadEnd, similarly shortened
#define GRIDLOCK 4
#define ENDTILE 5

#define MOTOR_ARDUINO_ADDRESS 0x20
#define LIGHT_ARDUINO_ADDRESS 0x07
#define COLOR_ARDUINO_ADDRESS 0x30
#define SERVO_ARDUINO_ADDRESS 0x17

//Directions
#define LEFT true
#define RIGHT false

//Pin Definitions:
#define PIN_LIFT_MOTOR 9
#define PIN_TOWER_SWITCH 8
#define PIN_BOARD_LED 13

//Objects-----------------
Compass compass;
MotorDriver motors(MOTOR_ARDUINO_ADDRESS);
