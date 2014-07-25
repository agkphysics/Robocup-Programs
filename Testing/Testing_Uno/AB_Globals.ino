//Map related:
int mapArray[] = {ROUNDABOUT, SQUARE}; //{ROUNDABOUT, SQUARE, CIRCLE, GRIDLOCK};
boolean intersections[] = {LEFT, LEFT};
boolean canSide = RIGHT;
boolean reachedEndTile = false;
#define INITIAL_HEADING 90.0;
int maxArrayIndex = (sizeof(mapArray)/sizeof(int)) - 1;
int intersectionCount = 0;

boolean reachedIntersection = false;

boolean reachedIntersectionLeft = false;
boolean reachedIntersectionRight = false;


//Speeds:
float leftSpeedFactor = 800.0; //Max Speed on straight for linefollowing
float rightSpeedFactor = 800.0; //Max Speed on straight for linefollowing

float maxSpeedManualSections = 4000.0;

float leftSpeed = 600.0; //Initial Speed (for testing purposes)
float rightSpeed = 600.0; //Initial Speed (for testing purposes)

//Compass related:
int initialHeading; //Is set in setupRobot();

