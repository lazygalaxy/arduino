/*
   LazyGalaxyAudioPlayerExample.cpp - Example of how to play MP3 or WAV files.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 23, 2024.
   Released into the public domain.
 */

#include <LazyGalaxySystem.h>
#include <LazyGalaxyTimer.h>
#include <LazyGalaxyAudioPlayer.h>

MyAudioPlayer *audioPlayer = new MyAudioPlayer(15);

void step2(unsigned long time)
{
    audioPlayer->play(2); // Play the second audio
}

void setup()
{
    Serial.begin(115200);
    System::add(audioPlayer);
    System::setup();

    audioPlayer->play(1); // Play the first audio
    Timer::schedule(500, step2);
}

void loop()
{
    System::loop();
    Timer::loop();
}
