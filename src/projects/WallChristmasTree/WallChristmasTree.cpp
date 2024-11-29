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
#include <LazyGalaxyAudioPlayer.h>

static const unsigned int DELAY = 50;
static const int8_t SAT = 255;
static const int8_t VAL = 128;

MyButton button1(D2);
MyLED led1(A2);
MyButton button2(D3);
MyLED led2(A3);
MyButton button3(D4);
MyLED led3(A4);
MyButton button4(D5);
MyLED led4(A5);
MyNeoPixel strip(D6, 123);
MyToneSpeaker toneSpeaker(D9, 10);
MyAudioPlayer audioPlayer(D10, D11, 25);

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
        strip.setNoSequence(random(255), SAT, VAL, 50);
}

void reverseLights(unsigned long time)
{
        strip.setWipeSequence(0, 0, 0, true, DELAY);
}

void finalCallback(unsigned long time)
{
        strip.off();
        audioPlayer.pause();
        led1.setLight(true);
        led2.setLight(true);
        led3.setLight(true);
        led4.setLight(true);
}

void buttonPress1(unsigned long time, uint8_t clicks)
{
        if (!led1.isLight() && led4.isLight())
                audioPlayer.prev();
        else if (!toneSpeaker.isActive())
        {
                audioPlayer.pause();
                led1.setLight(true);
                led2.setLight(false);
                led3.setLight(false);
                led4.setLight(false);
                toneSpeaker.playMelody(merryChristmasMelody, noteCallback, finalCallback);
        }
}

void buttonPress2(unsigned long time, uint8_t clicks)
{
        if (!led2.isLight() && led4.isLight())
                finalCallback(millis());
        else if (!toneSpeaker.isActive())
        {
                audioPlayer.pause();
                led1.setLight(false);
                led2.setLight(true);
                led3.setLight(false);
                led4.setLight(false);
                toneSpeaker.playMelody(jingleBellsMelody, noteCallback, finalCallback);
        }
}

void buttonPress3(unsigned long time, uint8_t clicks)
{
        if (!led3.isLight() && led4.isLight())
                audioPlayer.next();
        else if (!toneSpeaker.isActive())
        {
                audioPlayer.pause();
                led1.setLight(false);
                led2.setLight(false);
                led3.setLight(true);
                led4.setLight(false);
                toneSpeaker.playMelody(santaClausMelody, noteCallback, finalCallback);
        }
}

void buttonPress4(unsigned long time, uint8_t clicks)
{
        if (!toneSpeaker.isActive())
        {
                led1.setLight(false);
                led2.setLight(false);
                led3.setLight(false);
                led4.setLight(true);
                audioPlayer.resume();
                uint8_t hue = random(255);
                strip.setWipeSequence(hue, SAT, VAL, false, DELAY, reverseLights);
        }
}

void setup()
{
        // Serial.begin(115200);
        //    System setup
        Circuit::add(&strip);
        Circuit::add(&button1);
        Circuit::add(&led1);
        Circuit::add(&button2);
        Circuit::add(&led2);
        Circuit::add(&button3);
        Circuit::add(&led3);
        Circuit::add(&button4);
        Circuit::add(&led4);
        Circuit::add(&toneSpeaker);
        Circuit::add(&audioPlayer);
        Circuit::setup();
        audioPlayer.play(1, 1);
        delay(1500);
        buttonPress4(millis(), 1);

        button1.startClicksCallback(buttonPress1);
        button2.startClicksCallback(buttonPress2);
        button3.startClicksCallback(buttonPress3);
        button4.startClicksCallback(buttonPress4);
}

void loop()
{
        Circuit::loop();
}