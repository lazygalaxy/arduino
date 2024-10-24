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
  SoftwareSerial mySerial(10, 11); // RX, TX
  _player.begin(mySerial, true);
  _player.volume(_volume);
}

void MyAudioPlayer::reset()
{
  Serial.println("reset audio player");
  Component::reset();
  _player.reset();
}

void MyAudioPlayer::play(uint16_t index)
{
  Serial.println("play audio 1");
  _player.loop(index);
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
