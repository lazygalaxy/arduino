/*
   WallChristmasTree.cpp - Wall christmas tree implementation.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 1, 2020.
   Released into the public domain.
*/

#include <LazyGalaxyButton.h>
#include <LazyGalaxyLED.h>
#include <LazyGalaxyNeoPixel.h>
#include <LazyGalaxySpeaker.h>
#include <LazyGalaxyTimer.h>

Button button1(A2);
Button button2(A4);
Button button3(A6);
Button button4(D8);
NeoPixel strip(D10, 35);
Speaker speaker(D11);

Melody* santaClausMelody =
    new Melody((int[]){TG4, TE4, TF4, TG4, TG4, TG4, TA4, TB4, TC5, TC5,
                       TC5, TE4, TF4, TG4, TG4, TG4, TA4, TG4, TF4, TF4,
                       TE4, TG4, TC4, TE4, TD4, TF4, TB3, TC4, TEND},
               (int[]){2, 2, 2, 4, 4, 4, 2, 2, 4, 4, 4, 2, 2, 4,
                       4, 4, 2, 2, 4, 8, 4, 4, 4, 4, 4, 8, 4, 8},
               100);

Melody* jingleBellsMelody =
    new Melody((int[]){TE5, TE5, TE5, TE5, TE5, TE5, TE5, TG5, TC5,
                       TD5, TE5, TF5, TF5, TF5, TF5, TF5, TE5, TE5,
                       TE5, TE5, TE5, TD5, TD5, TE5, TD5, TG5, TEND},
               (int[]){2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 8, 2, 2,
                       2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 4, 4},
               100);

Melody* merryChristmasMelody =
    new Melody((int[]){TB3, TF4, TF4, TG4, TF4, TE4, TD4, TD4, TD4, TG4, TG4,
                       TA4, TG4, TF4, TE4, TE4, TE4, TA4, TA4, TB4, TA4, TG4,
                       TF4, TD4, TB3, TB3, TD4, TG4, TE4, TF4, TEND},
               (int[]){4, 4, 2, 2, 2, 2, 4, 4, 4, 4, 2, 2, 2, 2, 4,
                       4, 4, 4, 2, 2, 2, 2, 4, 4, 2, 2, 4, 4, 4, 8},
               100);

void setup() { strip.setup(); }

void loop() {
  // update all LazyGalaxy tasks
  Timer::updateTasks();

  int clicks1 = button1.getClicks();
  if (!button1.isOn() && clicks1 > 0) {
    button1.setOn(true);
    button2.setOn(false);
    button3.setOn(false);
    button4.setOn(false);
    speaker.playMelody(merryChristmasMelody);
  }

  int clicks2 = button2.getClicks();
  if (!button2.isOn() && clicks2 > 0) {
    button1.setOn(false);
    button2.setOn(true);
    button3.setOn(false);
    button4.setOn(false);
    speaker.playMelody(jingleBellsMelody);
  }

  int clicks3 = button3.getClicks();
  if (!button3.isOn() && clicks3 > 0) {
    button1.setOn(false);
    button2.setOn(false);
    button3.setOn(true);
    button4.setOn(false);
    speaker.playMelody(santaClausMelody);
  }

  int clicks4 = button4.getClicks();
  if (!button4.isOn() && clicks4 > 0) {
    speaker.stopMelody();
    button1.setOn(false);
    button2.setOn(false);
    button3.setOn(false);
    button4.setOn(true);
  }

  // if (button1.isOn() || button2.isOn() || button3.isOn()) {
  //   speaker.playMelody(playRandomCallback, stopCallback);
  // }
}

// void playRandomCallback(int counter) {
//   strip.noSequence(random(360), 1.0, 1.0, 0, 0.5);
// }

void stopCallback() {
  strip.off();
  button1.setOn(false);
  button2.setOn(false);
  button3.setOn(false);
  button4.setOn(false);
}