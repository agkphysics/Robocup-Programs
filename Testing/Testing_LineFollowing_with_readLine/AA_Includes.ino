#include <Compass.h>
#include <Wire.h>
#include <MotorDriver.h>

#define MOTOR_ARDUINO_ADDRESS 0x20
#define LIGHT_ARDUINO_ADDRESS 0x07

//#defines
#define TRIGGERED_BY_LEFT true
#define TRIGGERED_BY_RIGHT false

#define LEFT TRIGGERED_BY_LEFT
#define RIGHT TRIGGERED_BY_RIGHT

#define ROUNDABOUT 1
#define SQUARE 2 //refers to squareDeadEnd, shortened to save time on the day
#define CIRCLE 3 //refers to circleDeadEnd, similarly shortened
#define GRIDLOCK 4
#define ENDTILE 5

#define PIN_BOARD_LED 13
