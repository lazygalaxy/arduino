/*
   PlayWAVExample.cpp - Example on playing a WAV file.
   Created by LazyGalaxy - Evangelos Papakonstantis, September 22, 2024.
   Released into the public domain.
*/

#include <LazyGalaxySDCard.h>
#include <LazyGalaxySpeaker.h>

MySDCard sdcard(D10);
MySpeaker speaker(D9);

void playWav2(unsigned long time)
{
    speaker.playWav("OFF.wav");
}

void setup()
{
    Serial.begin(9600);
    Debug.setDebugLevel(DBG_VERBOSE);

    sdcard.setup();

    speaker.playWav("ON.wav");
    // schedule a task/function callback to play in the future
    Timer::scheduleTask(500, playWav2);
}

void loop()
{
    // update all LazyGalaxy tasks
    Timer::updateTasks();
}