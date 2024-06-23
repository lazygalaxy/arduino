/*
   SpotMicro.cpp - Dog implementation.
   Created by LazyGalaxy - Evangelos Papakonstantis, June 6, 2024.
   Released into the public domain.
*/

#include <LazyGalaxyServoGroup.h>

uint8_t extend[] = {0, 1, 2};
uint8_t retract[] = {178, 179, 180};

ServoGroup rightFrontLeg(D8, D9, D10);

void setup()
{
   Serial.begin(9600);
   rightFrontLeg.setup();
}

void loop()
{
   rightFrontLeg.setAngles(extend);
   delay(2000);
   rightFrontLeg.setAngles(retract);
   delay(2000);
}