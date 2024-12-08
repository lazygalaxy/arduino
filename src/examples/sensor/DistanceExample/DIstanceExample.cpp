#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor(7, 8);

void setup()
{
    Serial.begin(115200); // We initialize serial connection so that we could print values from sensor.
}

void loop()
{
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    Serial.println(distanceSensor.measureDistanceCm());
    delay(500);
}