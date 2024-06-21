/*
   LazyGalaxyMotorDriver.cpp - Library for a L298N dual motor driver.
   Created by LazyGalaxy - Evangelos Papakonstantis, May 5th, 2023.
   Released into the public domain.
 */

#include <LazyGalaxyMotorDriver.h>

MotorDriver::MotorDriver(uint8_t enA, uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t enB) : Component()
{
  _enA = new PinComponent(enA);
  _in1 = new PinComponent(in1);
  _in2 = new PinComponent(in2);
  _in3 = new PinComponent(in3);
  _in4 = new PinComponent(in4);
  _enB = new PinComponent(enB);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
}

void MotorDriver::setSpeed(int speed)
{
  analogWrite(_enA->getPin(), speed);
  analogWrite(_enB->getPin(), speed);
}

void MotorDriver::setForward()
{
  digitalWrite(_in1->getPin(), HIGH);
  digitalWrite(_in2->getPin(), LOW);
  digitalWrite(_in3->getPin(), HIGH);
  digitalWrite(_in4->getPin(), LOW);
}
