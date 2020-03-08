/*
   LEDExample.cpp - Example on the usage of the LazyGalaxyLED library
   Created by LazyGalaxy - Evangelos Papakonstantis, January 29, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyLED.h>
#include <LazyGalaxyTimer.h>

LED led1(D3);
LED led2(D7);
LED led3(A3);

void lightOff(unsigned long time) {
  led1.setLight(false);
  led2.setLight(false);
  led3.setLight(false);
}

void blinkOn(unsigned long time) {
  led1.setBlink(true);
  led2.setBlink(true);
  led3.setBlink(true);
}

void blinkOff(unsigned long time) {
  led1.setBlink(false);
  led2.setBlink(false);
  led3.setBlink(false);
}

void setup() {
  // light all 3 LEDS on startup
  led1.setLight(true);
  led2.setLight(true);
  led3.setLight(true);

  // schedule a task/function to switch the lights of all LEDs in 3 seconds
  Timer::scheduleTask(3000, lightOff);
  // schedule a task/function to start the blink of all LEDs in 6 seconds
  Timer::scheduleTask(6000, blinkOn);
  // schedule a task/function to stop the blink of all LEDs in 9 seconds
  Timer::scheduleTask(9000, blinkOff);
}

void loop() {
  // update all LazyGalaxy tasks
  Timer::updateTasks();
}