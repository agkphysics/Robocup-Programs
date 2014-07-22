//Some of these could become private

float leftSpeed = 300.0; //Initial Speed (for testing purposes)
float rightSpeed = 300.0; //Initial Speed (for testing purposes)

float leftSpeedFactor = 300.0; //Max Speed on straight for linefollowing
float rightSpeedFactor = 300.0; //Max Speed on straight for linefollowing

float maxSpeedManualSections = 4000.0;

boolean reachedEndTile = false;

int mapArray[] = {SQUARE};
int maxArrayIndex = (sizeof(mapArray)/sizeof(int)) - 1;

int initialHeading; //Is set in setupRobot();
