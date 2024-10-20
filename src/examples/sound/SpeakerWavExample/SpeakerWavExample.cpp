/*
   PlayWAVExample.cpp - Example on playing a WAV file.
   Created by LazyGalaxy - Evangelos Papakonstantis, September 22, 2024.
   Released into the public domain.
*/

#include <LazyGalaxySystem.h>
#include <LazyGalaxyTimer.h>
#include <LazyGalaxySDCard.h>
#include <LazyGalaxySpeaker.h>

MySpeaker *speaker = new MySpeaker(D9);

void playOffWav(unsigned long time)
{
    speaker->playWav("OFF.wav");
}

void setup()
{
    Serial.begin(9600);
    Debug.setDebugLevel(DBG_VERBOSE);

    System::add(new MySDCard(D10));
    System::add(speaker);

    System::setup();

    speaker->playWav("ON.wav");
    // schedule a task/function callback to play in the future
    Timer::schedule(500, playOffWav);
}

void loop()
{
    System::loop();
    Timer::loop();
}