/*
   LEDExample.cpp - Example on the usage of the LazyGalaxyLED library
   Created by LazyGalaxy - Evangelos Papakonstantis, January 29, 2020.
   Released into the public domain.
 */

#include <LazyGalaxySystem.h>
#include <LazyGalaxyTimer.h>
#include <LazyGalaxyLED.h>

// any pin is ok for the LEDs, digital(with and without PWM) or analog
LED *led = new LED(D4);

void lightOff(unsigned long time)
{
  led->setLight(false);
}

void blinkOn(unsigned long time)
{
  led->setBlink(true);
}

void blinkOff(unsigned long time)
{
  led->setBlink(false);
}

void setup()
{
  Debug.setDebugLevel(DBG_VERBOSE);

  System::add(led);
  System::setup();

  // light LED on startup
  led->setLight(true);

  // schedule a task/function to switch the light off in 3 seconds
  Timer::schedule(3000, lightOff);
  // schedule a task/function to start the blink in 6 seconds
  Timer::schedule(6000, blinkOn);
  // schedule a task/function to stop the blink in 9 seconds
  Timer::schedule(9000, blinkOff);
}

void loop()
{
  System::loop();
  Timer::update();
}