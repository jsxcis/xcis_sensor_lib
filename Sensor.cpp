#include "Arduino.h"
#include "Sensor.h"
Sensor::Sensor()
{
    #ifdef debug
    Serial.println("Sensor::Constructor");
    #endif
    initialised = "false";
    lastScanTime = 0;
}
void Sensor::displaySensor()
{
    #ifdef debug
    Serial.print("Sensor:");
    Serial.print(loraID + ",");
    Serial.print(deviceType + ",");
    Serial.print(deviceMode + ",");
    Serial.print(String(lastScanTime) + ",");
    Serial.print(initialised + ",");
    Serial.println(sensorData);
    #endif
}
String Sensor::outputSensor()
{
    String output;
    output = "Sensor:" + loraID + "," + deviceType + "," + deviceMode + "," +
    String(lastScanTime) + "," + initialised + "," + sensorData;
    return output;
}
