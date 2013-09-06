//Map related:
int mapArray[] = {SQUARE};
boolean canSide = LEFT;
boolean reachedEndTile = false;
int maxArrayIndex = (sizeof(mapArray)/sizeof(int)) - 1;


//Speeds:
float leftSpeedFactor = 600.0; //Max Speed on straight for linefollowing
float rightSpeedFactor = 600.0; //Max Speed on straight for linefollowing

float maxSpeedManualSections = 4000.0;

float leftSpeed = 600.0; //Initial Speed (for testing purposes)
float rightSpeed = 600.0; //Initial Speed (for testing purposes)

//Compass related:
int initialHeading; //Is set in setupRobot();

//Line array related:
unsigned int currentSensorValues[8];
