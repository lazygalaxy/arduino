/*
   LazyGalaxyAudioPlayer.cpp - Library for playing audio files.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 23, 2024.
   Released into the public domain.
 */

#include <LazyGalaxyAudioPlayer.h>

MyAudioPlayer::MyAudioPlayer(uint8_t volume) : PinComponent(255)
{
  _volume = volume;
}

void MyAudioPlayer::setup()
{
  _mySerial = new SoftwareSerial(10, 11); // RX, TX
  _mySerial->begin(9600);

  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  _player.begin(*_mySerial, /*isACK = */ true, /*doReset = */ true);
  Serial.println(F("DFPlayer Mini online."));

  _player.volume(_volume); // Set volume value. From 0 to 30
}

void MyAudioPlayer::reset()
{
  Serial.println("reset audio player");
  Component::reset();
}

void MyAudioPlayer::play(uint16_t index)
{
  Serial.println("play audio 1");
  _player.play(index);
  Serial.println("play audio 2");
}

void MyAudioPlayer::stop()
{
  _player.stop();
}

unsigned long MyAudioPlayer::update(unsigned long time)
{
  return 0;
}
