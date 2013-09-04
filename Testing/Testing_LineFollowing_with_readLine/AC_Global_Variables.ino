//Some of these could become private

unsigned int currentSensorValues[8];

float leftSpeed = 600.0; //Initial Speed (for testing purposes)
float rightSpeed = 600.0; //Initial Speed (for testing purposes)


float leftSpeedFactor = 600.0; //Max Speed on straight for linefollowing
float rightSpeedFactor = 600.0; //Max Speed on straight for linefollowing

int gridlockIntersection = 1;

boolean reachedEndTile = false;

int mapArray[] = {ROUNDABOUT, ENDTILE};
int mapArraySize = (sizeof(mapArray)/sizeof(int)) - 1;
