//Some of these could become private

unsigned int currentSensorValues[8];

float leftSpeed = 600.0; //Initial Speed (for testing purposes)
float rightSpeed = 600.0; //Initial Speed (for testing purposes)


float leftSpeedFactor = 600.0; //Max Speed on straight for linefollowing
float rightSpeedFactor = 600.0; //Max Speed on straight for linefollowing


float maxSpeedManualSections = 4000.0;

int gridlockIntersection = 1;

boolean reachedEndTile = false;

int mapArray[] = {SQUARE};
int maxArrayIndex = (sizeof(mapArray)/sizeof(int)) - 1;

int initialHeading; //Is set in setupRobot();
