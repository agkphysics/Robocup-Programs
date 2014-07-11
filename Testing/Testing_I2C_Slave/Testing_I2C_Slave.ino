#include <Wire.h>

char lastRecievedData[32];

void requestedData()
{
    Wire.write("Last recieved data was: ");
    Wire.write(lastRecievedData);
}

void receivedData(int numBytes)
{
    int i;
    Wire.write("Recieved data. Data was: ");
    for(i = 0; Wire.available(); i++)
    {
        lastRecievedData[i] = Wire.read();
    }
}

void setup()
{
    Wire.begin(0x11);
    Wire.onRequest(requestedData);
    Wire.onReceive(receivedData);
}

void loop()
{
    
}

