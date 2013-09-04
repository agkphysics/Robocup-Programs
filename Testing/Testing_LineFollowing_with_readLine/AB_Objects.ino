Compass compass;
AccelStepper leftMotor(AccelStepper::DRIVER, 7, 6);
AccelStepper rightMotor(AccelStepper::DRIVER, 5, 4);
Motors motors(leftMotor, rightMotor);

CircularBuffer linePositionBuffer;

// sensors 0 through 7 are connected to analog inputs 7 through 0, respectively
QTRSensorsAnalog qtra((unsigned char[]) {7,6,5,4,3,2,1,0}, 8, 9, 8); //({Pins}, number of sensors, number of samples per reading to average, emitterpin)

