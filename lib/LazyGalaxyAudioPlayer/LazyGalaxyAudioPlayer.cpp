/*
   LazyGalaxyAudioPlayer.cpp - Library for playing audio files.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 23, 2024.
   Released into the public domain.
 */

#include <LazyGalaxyAudioPlayer.h>

MyAudioPlayer::MyAudioPlayer(char volume) : PinComponent(255)
{
  _volume = volume;
}

void MyAudioPlayer::setup()
{
  _softwareSerial = new SoftwareSerial(RX_PIN, TX_PIN);
  _softwareSerial->begin(9600);

  DEBUG_DEBUG("Initializing AudioPlayer ...");
  if (_player.begin(*_softwareSerial, true, false))
  {
    DEBUG_INFO("AudioPlayer OK");
    _player.volume(_volume);
  }
  else
    DEBUG_ERROR("Audio Player failed");
}

void MyAudioPlayer::reset()
{
  DEBUG_DEBUG("reset audio player");
  Component::reset();
}

void MyAudioPlayer::play(int index)
{
  _player.play(index);
}

void MyAudioPlayer::stop()
{
  _player.stop();
}

unsigned long MyAudioPlayer::update(unsigned long time)
{
  return 0;
}
