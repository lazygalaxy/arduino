/*
   LazyGalaxyAudioPlayerExample.cpp - Example of how to play MP3 or WAV files.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 23, 2024.
   Released into the public domain.
 */

#include <LazyGalaxyCircuit.h>
#include <LazyGalaxyTimer.h>
#include <LazyGalaxyAudioPlayer.h>

MyAudioPlayer audioPlayer(D10, D11, 15);

void step2(unsigned long time)
{
    audioPlayer.play(1, 2); // Play the second audio
}

void setup()
{
    Circuit::add(&audioPlayer);
    Circuit::setup();

    audioPlayer.play(1, 1); // Play the first audio
    Timer::schedule(2000, step2);
}

void loop()
{
    Circuit::loop();
    Timer::loop();
}
