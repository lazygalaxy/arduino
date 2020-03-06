/*
   LEDExample.cpp - Example on the usage of the LazyGalaxyLED library
   Created by LazyGalaxy - Evangelos Papakonstantis, January 29, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyLED.h>
#include <LazyGalaxyTimer.h>

LazyGalaxyLED led1(D3);
LazyGalaxyLED led2(D7);
LazyGalaxyLED led3(A3);

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
  Serial.begin(9600);

  // light all 3 LEDS on startup
  led1.setLight(true);
  led2.setLight(true);
  led3.setLight(true);

  // schedule a task to switch the lights of all LEDs in 3 seconds
  LazyGalaxyTimer::scheduleTask(3000, lightOff);

  // schedule a task to start the blink of all LEDs in 6 seconds
  LazyGalaxyTimer::scheduleTask(6000, blinkOn);

  // schedule a task to stop the blink of all LEDs in 9 seconds
  LazyGalaxyTimer::scheduleTask(9000, blinkOff);
}

void loop() {
  // update the LazyGalaxy tasks
  LazyGalaxyTimer::updateTasks();
}