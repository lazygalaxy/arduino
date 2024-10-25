/*
   WallChristmasTree.cpp - Wall christmas tree implementation.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 1, 2020.
   Released into the public domain.
*/

#include <LazyGalaxyCircuit.h>
#include <LazyGalaxyButton.h>
#include <LazyGalaxyLED.h>
#include <LazyGalaxyNeoPixel.h>
#include <LazyGalaxyToneSpeaker.h>

static const unsigned int DELAY = 50;
static const float SAT = 1.0;
static const float VAL = 0.4;

Button *button1 = new Button(D2);
LED *led1 = new LED(D3);
Button *button2 = new Button(D4);
LED *led2 = new LED(D5);
Button *button3 = new Button(D6);
LED *led3 = new LED(D7);
Button *button4 = new Button(D8);
LED *led4 = new LED(D9);

NeoPixel *strip = new NeoPixel(D11, 123);
MyToneSpeaker *speaker = new MyToneSpeaker(D12, 5);

boolean reverse = false;

Melody *santaClausMelody =
    new Melody((int[]){TG4, TE4, TF4, TG4, TG4, TG4, TA4, TB4, TC5, TC5,
                       TC5, TE4, TF4, TG4, TG4, TG4, TA4, TG4, TF4, TF4,
                       TE4, TG4, TC4, TE4, TD4, TF4, TB3, TC4, TEND},
               (int[]){2, 2, 2, 4, 4, 4, 2, 2, 4, 4, 4, 2, 2, 4,
                       4, 4, 2, 2, 4, 8, 4, 4, 4, 4, 4, 8, 4, 8},
               100);

Melody *jingleBellsMelody =
    new Melody((int[]){TE5, TE5, TE5, TE5, TE5, TE5, TE5, TG5, TC5,
                       TD5, TE5, TF5, TF5, TF5, TF5, TF5, TE5, TE5,
                       TE5, TE5, TE5, TD5, TD5, TE5, TD5, TG5, TEND},
               (int[]){2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 8, 2, 2,
                       2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 4, 4},
               100);

Melody *merryChristmasMelody =
    new Melody((int[]){TB3, TF4, TF4, TG4, TF4, TE4, TD4, TD4, TD4, TG4, TG4,
                       TA4, TG4, TF4, TE4, TE4, TE4, TA4, TA4, TB4, TA4, TG4,
                       TF4, TD4, TB3, TB3, TD4, TG4, TE4, TF4, TEND},
               (int[]){4, 4, 2, 2, 2, 2, 4, 4, 4, 4, 2, 2, 2, 2, 4,
                       4, 4, 4, 2, 2, 2, 2, 4, 4, 2, 2, 4, 4, 4, 8},
               100);

void noteCallback(unsigned long time, int note)
{
  strip->setNoSequence(random(100) / 100.0f, SAT, VAL, 0.5);
}

void finalCallback(unsigned long time)
{
  strip->off();
  led1->setLight(true);
  led2->setLight(true);
  led3->setLight(true);
  led4->setLight(true);
}

void setup()
{
  pinMode(D10, OUTPUT);
  digitalWrite(D10, LOW);

  Circuit::add(strip);
  Circuit::add(button1);
  Circuit::add(led1);
  Circuit::add(button2);
  Circuit::add(led2);
  Circuit::add(button3);
  Circuit::add(led3);
  Circuit::add(button4);
  Circuit::add(led4);
  Circuit::add(speaker);
  Circuit::setup();

  finalCallback(0);
}

void loop()
{
  Circuit::loop();

  // if (!speaker->isActive() && button1->getClicks() > 0)
  // {
  //   strip->off();
  //   button1->setOn(true);
  //   button2->setOn(false);
  //   button3->setOn(false);
  //   button4->setOn(false);
  //   speaker->playMelody(merryChristmasMelody, noteCallback, finalCallback);
  // }

  // if (!speaker->isActive() && button2->getClicks() > 0)
  // {
  //   strip->off();
  //   button1->setOn(false);
  //   button2->setOn(true);
  //   button3->setOn(false);
  //   button4->setOn(false);
  //   speaker->playMelody(jingleBellsMelody, noteCallback, finalCallback);
  // }

  // if (!speaker->isActive() && button3->getClicks() > 0)
  // {
  //   strip->off();
  //   button1->setOn(false);
  //   button2->setOn(false);
  //   button3->setOn(true);
  //   button4->setOn(false);
  //   speaker->playMelody(santaClausMelody, noteCallback, finalCallback);
  // }

  // if (!speaker->isActive() && button4->getClicks() > 0)
  // {
  //   strip->off();
  //   button1->setOn(false);
  //   button2->setOn(false);
  //   button3->setOn(false);
  //   button4->setOn(true);
  //   speaker->reset();

  //   float prob = random(100) / 100.0f;
  //   float hue = random(100) / 100.0f;

  //   if (0.5 >= prob)
  //   {
  //     strip->setChaseSequence(hue, SAT, VAL, DELAY, 100, 3, finalCallback);
  //   }
  //   else
  //   {
  //     strip->setWipeSequence(hue, SAT, VAL, DELAY, reverse, finalCallback);
  //     reverse = !reverse;
  //   }
  // }
}