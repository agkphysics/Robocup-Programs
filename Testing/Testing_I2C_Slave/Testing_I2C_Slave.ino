#include <Wire.h>

char lastRecievedData[32];

void requestedData()
{
    Wire.write(0);
    Serial.println("Got a request for data");
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(13, HIGH);
        delay(100);
        digitalWrite(13, LOW);
        delay(200);
    }
}

void receivedData(int numBytes)
{
    Serial.println("Recieved data. Data was: ");
    if (Wire.read() == 1) digitalWrite(13, HIGH);
    else digitalWrite(13, LOW);
}

void setup()
{
    Wire.begin(0x33);
    Serial.begin(9600);
    Wire.onRequest(requestedData);
    Wire.onReceive(receivedData);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
}

void loop()
{
    
}

