#include <Compass.h>
#include <Wire.h>

Compass compass;


void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop(){
  Serial.print(compass.heading());
  Serial.println(" heading");
  delay(100);
}
