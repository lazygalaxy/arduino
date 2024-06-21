/*
   SpotMicro.cpp - Dog implementation.
   Created by LazyGalaxy - Evangelos Papakonstantis, June 6, 2024.
   Released into the public domain.
*/

#include <LazyGalaxyServo.h>

MyServo fr1Servo(D8);
MyServo fr2Servo(D9);
MyServo fr3Servo(D10);

MyServo fl1Servo(D11);
MyServo fl2Servo(D12);
MyServo fl3Servo(D13);

void setup()
{
   fr1Servo.setup();
   fr2Servo.setup();
   fr3Servo.setup();

   fl1Servo.setup();
   fl2Servo.setup();
   fl3Servo.setup();

   delay(1000);
}

void loop()
{
   while (fr2Servo.getLastAngle() < 180)
   {
      fr2Servo.addAngle(90);
   }

   while (fr2Servo.getLastAngle() > 0)
   {
      fr2Servo.addAngle(-90);
   }
}