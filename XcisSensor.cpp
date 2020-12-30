#include "Arduino.h"
#include "XcisSensor.h"
XcisSensor::XcisSensor()
{
  // Constructor
  #ifdef debug
  Serial.println("XcisSensor::Constructor");
  #endif
  nextSensor = 0;
}
int XcisSensor::scanNextSensor()
{
    //Serial.println("XcisSensor::scanNextSensor");
    if (nextSensor == numberOfSensors)
        nextSensor = 0;
    int sensorToScan = nextSensor;
    if (sensors[sensorToScan].initialised == "false")
    {
        nextSensor = 0;
        return -1;
    }
    nextSensor++;
    return sensorToScan;
}
String XcisSensor::getSensorLoraID(int scanNumber)
{
    return sensors[scanNumber].loraID;
}
String XcisSensor::getSensorData(int scanNumber)
{
    return sensors[scanNumber].sensorData;
}
String XcisSensor::getSensorData(String loraID)
{
    String sensorData = "NOT FOUND";
    for (int i =0; i< numberOfSensors; i++)
    {
        if (sensors[i].loraID.toInt() == loraID.toInt())
        {
            #ifdef debug
            Serial.print("Found sensor Data:" + String(i)+ ":");
            sensors[i].displaySensor();
            #endif
            //sensorData = sensors[i].loraID + ":" + sensors[i].sensorData;
            sensorData = sensors[i].sensorData;
            break;
        }
    }
    return sensorData;
}
int XcisSensor::getSensorScanNumber(String loraID)
{
    int counter = 0;
    for (int i =0; i< numberOfSensors; i++)
    {
        counter = i;
        if (sensors[i].loraID.toInt() == loraID.toInt())
        {
            #ifdef debug
            Serial.print("Found sensor:" + String(i)+ ":");
            #endif
            sensors[i].displaySensor();
            break;
        }
        
    }
    return counter;
}
String XcisSensor::listSensors(bool serial)
{
    //Serial.println("XcisSensor::listSensors");
    String output;
    for (int i =0; i< numberOfSensors; i++)
    {
        if (serial == false)
        {
            sensors[i].displaySensor();
        }
        else
        {
            output += sensors[i].outputSensor();
            output +="\n";
        }
        
    }
    return output;
}
void XcisSensor::checkSensorsOnline()
{
    //Serial.println("XcisSensor::checkSensorsOnline");
    for (int i =0; i< numberOfSensors; i++)
    {
        sensors[i].displaySensor();
        if (sensors[i].lastScanTime < (millis() - 60000))
        {
            //Serial.println("Sensor offline");
            setDeviceMode(i, "OFFLINE", millis());
            sensors[i].displaySensor();

        }
    }
}
void XcisSensor::displaySensor(int scanNumber)
{
    sensors[scanNumber].displaySensor();
}
void XcisSensor::streamSensor(int scanNumber)
{
    sensors[scanNumber].outputSensor();
}
void XcisSensor::addSensor(int scanNumber, String loraID, String deviceType)
{
    //Serial.println("XcisSensor::addSensor");
    sensors[scanNumber].setLoraID(loraID);
    sensors[scanNumber].setdeviceType(deviceType);
    sensors[scanNumber].setdeviceMode("UNKNOWN");
    sensors[scanNumber].setsensorData("NODATA,");
    sensors[scanNumber].setInit("true");
}
void XcisSensor::deleteSensor()
{
    //Serial.println("XcisSensor::deleteSensor");

}
void XcisSensor::setSensorData(int scanNumber, String data)
{
    //Serial.println("XcisSensor::setSensorData");
    sensors[scanNumber].setsensorData(data);
}
void XcisSensor::setDeviceMode(int scanNumber, String state, unsigned long timeStamp)
{
    //Serial.println("XcisSensor::setdeviceMode");
    sensors[scanNumber].setdeviceMode(state);
    sensors[scanNumber].setLastScanTime(timeStamp);
}
String XcisSensor::getDeviceMode(String loraID)
{
    //Serial.println("XcisSensor::getDeviceMode");
    return sensors[getSensorScanNumber(loraID)].deviceMode;
}