const int ledBarGraphPins[7] = {31,33,35,37,39,41,43};

void setupLEDBarGraph()
{
  for (int i = 0; i < 7; i++)
  {
    pinMode(ledBarGraphPins[i], OUTPUT);
  }
}

void turnOnLED(int led, boolean exclusive)
{
  digitalWrite(ledBarGraphPins[led], HIGH);
  if (exclusive)
  {
    for (int i = 0; i < 7 && i != led; i++)
    {
      digitalWrite(ledBarGraphPins[i], LOW);
    }
  }
}

void turnOffLED(int led)
{
  digitalWrite(ledBarGraphPins[led], LOW);
}

void setup()
{
  setupLEDBarGraph();
}

void loop()
{
  for (int i = 0; i < 7; i++)
  {
    turnOnLED(i, true);
    delay(250);
  }
  turnOffLED(6);
  
  for (int i = 0; i < 7; i++)
  {
    turnOnLED(i, false);
    delay(250);
  }
  for (int i = 0; i < 7; i++)
  {
    turnOffLED(i);
    delay(250);
  }
}

