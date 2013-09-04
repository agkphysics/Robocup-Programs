int lastError = 0;

void setLineFollowingSpeeds() {
// get calibrated sensor values returned in the sensors array, along with the line position
// position will range from 0 to 2000, with 1000 corresponding to the line over the middle sensor
int position = qtra.readLine(currentSensorValues);
// compute our "error" from the line position. We will make it so that the error is zero when
// the middle sensor is over the line, because this is our goal. Error will range from
// -1000 to +1000. If we have sensor 0 on the left and sensor 2 on the right, a reading of -1000
// means that we see the line on the left and a reading of +1000 means we see the line on
// the right.
int error = position - 4000;
// set the motor speed based on proportional and derivative PID terms
// KP is the a floating-point proportional constant (maybe start with a value around 0.1)
// KD is the floating-point derivative constant (maybe start with a value around 5)
// note that when doing PID, it's very important you get your signs right, or else the
// control loop will be unstable
  int motorSpeed = 0.2 * error + 5 * (error - lastError); //KP then KD
lastError = error;
// M1 and M2 are base motor speeds. That is to say, they are the speeds the motors should
// spin at if you are perfectly on the line with no error. If your motors are well matched,
// M1 and M2 will be equal. When you start testing your PID loop, it might help to start with
// small values for M1 and M2. You can then increase the speed as you fine-tune your
// PID constants KP and KD.
float m1Speed = 400 + motorSpeed;
float m2Speed = 400 - motorSpeed;
// it might help to keep the speeds positive (this is optional)
// note that you might want to add a similiar line to keep the speeds from exceeding
// any maximum allowed value
/*if (m1Speed < 0)
m1Speed = 0;
if (m2Speed < 0)
m2Speed = 0;*/
// set motor speeds using the two motor speed variables above
/*
Serial.print(m1Speed);
Serial.print(" , ");
Serial.println(m2Speed);
*/
motors.setActiveSpeeds(m1Speed, m2Speed);

}


float linePosition()
{
  float lineReadScaled = (float)qtra.readLine(currentSensorValues) / 3500.0; 
  return (lineReadScaled - 1.0);
}

boolean reachedEndTile() { //TODO
  return false;
}


float blackness() { //0 to 8000
  //Must have just called this in LineFollowingSetSpeeds: qtra.readCalibrated(currentSensorValues);
  unsigned int sum = 0;
  for (int i=0; i<8; i++) {
    sum += currentSensorValues[i];
  }
  return (float)sum/8000.0;  
}
