/*
   AudioPlayerExample.cpp - Example on playing a MP3 or WAV files.
   Created by LazyGalaxy - Evangelos Papakonstantis, September 22, 2024.
   Released into the public domain.
*/

#include <LazyGalaxySystem.h>
#include <LazyGalaxyTimer.h>
#include <LazyGalaxyAudioPlayer.h>

MyAudioPlayer *audioPLayer = new MyAudioPlayer();

void playOffWav(unsigned long time)
{
    audioPLayer->play(1);
}

void setup()
{
    Serial.begin(115200);
    Debug.setDebugLevel(DBG_VERBOSE);

    System::add(audioPLayer);

    System::setup();

    audioPLayer->play(1);
    // schedule a task/function callback to play in the future
    Timer::schedule(500, playOffWav);
}

void loop()
{
    System::loop();
    Timer::loop();
}