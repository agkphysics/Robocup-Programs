const int ledBarGraphPins[8] = {23,25,27,29,31,33,35,37};

void setupLEDBarGraph()
{
  for (int i = 0; i < 8; i++)
  {
    pinMode(ledBarGraphPins[i], OUTPUT);
  }
}

void turnOnLED(int led, boolean exclusive)
{
  digitalWrite(ledBarGraphPins[led], HIGH);
  if (exclusive)
  {
    for (int i = 0; i < 8 && i != led; i++)
    {
      digitalWrite(ledBarGraphPins[i], LOW);
    }
  }
}

void turnOffLED(int led)
{
  digitalWrite(ledBarGraphPins[led], LOW);
}

void writeBinary(unsigned int i)
{
  if (i > (1 << 8) - 1) return;
  for (int j = 0; j < 8; j++) 
  {
    digitalWrite(ledBarGraphPins[j], LOW);
    if ((1 << j) & i) digitalWrite(ledBarGraphPins[j], HIGH);
  }
}

void setup()
{
  setupLEDBarGraph();
}

void loop()
{
  /*
  for (int i = 0; i < 8; i++)
  {
    turnOnLED(i, true);
    delay(250);
  }
  turnOffLED(6);
  
  for (int i = 0; i < 8; i++)
  {
    turnOnLED(i, false);
    delay(250);
  }
  */
  for (int i = 0; i < 8; i++)
  {
    turnOffLED(i);
    delay(250);
  }
  
  for (unsigned int i = 0; i <= 255; i++)
  {
    writeBinary(i);
    delay(50);
  }
}

