/*
   SpotMicro.cpp - Dog implementation.
   Created by LazyGalaxy - Evangelos Papakonstantis, June 6, 2024.
   Released into the public domain.
*/

#include <LazyGalaxyServoGroup.h>

uint8_t rest[] = {90, 90, 90};
uint8_t stand[] = {180, 180, 180};

// ServoGroup rightFrontLeg(3, (uint8_t[]){D2, D3, D4});
// ServoGroup leftFrontLeg(3, (uint8_t[]){D5, D6, D7});
ServoGroup rightBackLeg(3, (uint8_t[]){D8, D9, D10}, rest);
// ServoGroup leftBackLeg(3, (uint8_t[]){D11, D12, D13});

void setup()
{
   Serial.begin(9600);

   // rightFrontLeg.setup();
   // leftFrontLeg.setup();
   rightBackLeg.setup();
   // leftBackLeg.setup();
}

void loop()
{
   Serial.println("loop");
   delay(2000);
   // rightFrontLeg.setAngles(stand);
   // leftFrontLeg.setAngles(stand);
   rightBackLeg.setAngles(stand);
   // leftBackLeg.setAngles(stand);
   delay(2000);
   // rightFrontLeg.setAngles(rest);
   // leftFrontLeg.setAngles(rest);
   rightBackLeg.setAngles(rest);
   // leftBackLeg.setAngles(rest);
}