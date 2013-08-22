const int ledBarGraphPins[10] = {};

void setupLEDBarGraph()
{
  for (int i = 0; i < 10; i++)
  {
    pinMode(ledBarGraphPins[i], OUTPUT);
  }
}

void turnOnLed(int led, boolean exclusive)
{
  digitalWrite(ledBarGraphPins[led], HIGH);
  if (exclusive)
  {
    for (int i = 0; i < 10 && i += led; i++)
    {
      digitalWrite(ledBarGraphPins[i], LOW);
    }
  }
}

void turnOffLed(int led)
{
  digitalWrite(ledBarGraphPins[led], LOW);
}
