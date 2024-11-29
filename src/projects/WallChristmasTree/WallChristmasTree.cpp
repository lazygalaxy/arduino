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
// #include <LazyGalaxyAudioPlayer.h>

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
MyToneSpeaker speaker(D9, 5);
// MyAudioPlayer audioPlayer(D10, D11, 15);

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
        strip.setNoSequence(random(255), SAT, VAL, 0.5);
}

void finalCallback(unsigned long time)
{
        strip.off();
        // audioPlayer.stop();
        led1.setLight(true);
        led2.setLight(true);
        led3.setLight(true);
        led4.setLight(true);
}

void playMelody1(unsigned long time, uint8_t clicks)
{
        if (!speaker.isActive() && clicks > 0)
        {
                strip.off();
                // audioPlayer.stop();
                led1.setLight(true);
                led2.setLight(false);
                led3.setLight(false);
                led4.setLight(false);
                speaker.playMelody(merryChristmasMelody, noteCallback, finalCallback);
        }
}

void playMelody2(unsigned long time, uint8_t clicks)
{
        if (!speaker.isActive() && clicks > 0)
        {
                strip.off();
                // audioPlayer.stop();
                led1.setLight(false);
                led2.setLight(true);
                led3.setLight(false);
                led4.setLight(false);
                speaker.playMelody(jingleBellsMelody, noteCallback, finalCallback);
        }
}

void playMelody3(unsigned long time, uint8_t clicks)
{
        if (!speaker.isActive() && clicks > 0)
        {
                strip.off();
                // audioPlayer.stop();
                led1.setLight(false);
                led2.setLight(false);
                led3.setLight(true);
                led4.setLight(false);
                speaker.playMelody(santaClausMelody, noteCallback, finalCallback);
        }
}

void playMP3(unsigned long time, uint8_t clicks)
{
        if (clicks > 0)
        {
                strip.off();
                led1.setLight(false);
                led2.setLight(false);
                led3.setLight(false);
                led4.setLight(true);
                // audioPlayer.play(1);
        }
}

void setup()
{
        Serial.begin(115200);
        //   System setup
        Circuit::add(&strip);
        Circuit::add(&button1);
        Circuit::add(&led1);
        Circuit::add(&button2);
        Circuit::add(&led2);
        Circuit::add(&button3);
        Circuit::add(&led3);
        Circuit::add(&button4);
        Circuit::add(&led4);
        Circuit::add(&speaker);
        // Circuit::add(&audioPlayer);
        Circuit::setup();

        finalCallback(0);

        button1.startClicksCallback(playMelody1);
        button2.startClicksCallback(playMelody2);
        button3.startClicksCallback(playMelody3);
        button4.startClicksCallback(playMP3);
}

void loop()
{
        Circuit::loop();
        button4.startClicksCallback(playMP3);
        // if (!speaker.isActive() && button4.getClicks() > 0)
        // {
        //         strip.off();
        //         button1.setOn(false);
        //         button2.setOn(false);
        //         button3.setOn(false);
        //         button4.setOn(true);
        //         speaker.reset();

        //         float prob = random(100) / 100.0f;
        //         float hue = random(100) / 100.0f;

        //         if (0.5 >= prob)
        //         {
        //                 strip.setChaseSequence(hue, SAT, VAL, DELAY, 100, 3, finalCallback);
        //         }
        //         else
        //         {
        //                 strip.setWipeSequence(hue, SAT, VAL, DELAY, reverse, finalCallback);
        //                 reverse = !reverse;
        //         }
        // }
}