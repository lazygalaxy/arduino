/*
   AudioPlayerExample.cpp - Example on playing a MP3 or WAV files.
   Created by LazyGalaxy - Evangelos Papakonstantis, September 22, 2024.
   Released into the public domain.
*/

// #include <LazyGalaxySystem.h>
//   #include <LazyGalaxyTimer.h>
#include <LazyGalaxyAudioPlayer.h>

#if !defined(UBRR1H)
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
#endif

DFPlayerMini_Fast myMP3;

void setup()
{
    Serial.begin(115200);

    Serial.println("begin");
#if !defined(UBRR1H)
    mySerial.begin(9600);
    myMP3.begin(mySerial, true);
#else
    Serial1.begin(9600);
    myMP3.begin(Serial1, true);
#endif
    Serial.println("begin end");

    Serial.println("reset");
    myMP3.reset();
    Serial.println("Setting volume to max");
    myMP3.volume(20);
    Serial.println("reset end");

    Serial.println("play");
    Serial.println("Looping track 1");
    myMP3.play(1);
    Serial.println("play end");
}

void loop()
{
    // do nothing
}