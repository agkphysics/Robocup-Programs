#include <QTRSensors.h>
#include <Compass.h>
#include <Wire.h>
#include <Motors.h>
#include <AccelStepper.h>
#include <Scheduler.h>
#include <CircularBuffer.h>

//#defines
#define TRIGGERED_BY_LEFT true
#define TRIGGERED_BY_RIGHT false

#define ROUNDABOUT 1
#define SQUARE 2 //refers to squareDeadEnd, shortened to save time on the day
#define CIRCLE 3 //refers to circleDeadEnd, similarly shortened
#define GRIDLOCK 4
#define ENDTILE 5

