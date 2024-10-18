/*
   PlayWAVExample.cpp - Example on playing a WAV file.
   Created by LazyGalaxy - Evangelos Papakonstantis, September 22, 2024.
   Released into the public domain.
*/

#include <LazyGalaxySystem.h>
#include <LazyGalaxySDCard.h>
#include <LazyGalaxySpeaker.h>

MySDCard *sdcard = new MySDCard(D10);
MySpeaker *speaker = new MySpeaker(D9);

void playWav2(unsigned long time)
{
    speaker->playWav("OFF.wav");
}

void setup()
{
    Debug.setDebugLevel(DBG_DEBUG);

    System::getInstance()->add(sdcard);
    System::getInstance()->add(speaker);

    System::getInstance()->setup();

    speaker->playWav("ON.wav");
    // schedule a task/function callback to play in the future
    Timer::scheduleTask(500, playWav2);
}

void loop()
{
    System::getInstance()->loop(millis());
    // update all LazyGalaxy tasks
    Timer::updateTasks();
}