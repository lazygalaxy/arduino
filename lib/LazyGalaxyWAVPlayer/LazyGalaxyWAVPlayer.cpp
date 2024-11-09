/*
   LazyGalaxyWAVPlayer.cpp - Library for playing WAV audio files.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 5, 2024.
   Released into the public domain.
 */

#include <LazyGalaxyWAVPlayer.h>

MyWAVPlayer::MyWAVPlayer(uint8_t pin, uint8_t volume) : PinComponent(pin)
{
  _volume = volume;
}

void MyWAVPlayer::setup()
{
  _player.speakerPin = _pin;
  _player.setVolume(_volume);
}

void MyWAVPlayer::reset()
{
  Component::reset();

  _hasPlayStarted = false;
  _player.disable();
}

void MyWAVPlayer::play(const char *filename, finalCallbackPtr finalCallback)
{
  reset();

  _finalCallback = finalCallback;
  _player.play(filename);
  _hasPlayStarted = true;
  _triggerTime = update(millis());
}

bool MyWAVPlayer::isPlaying()
{
  return _player.isPlaying();
}

void MyWAVPlayer::stop()
{
  _player.stopPlayback();
}

unsigned long MyWAVPlayer::update(unsigned long time)
{
  if (_hasPlayStarted && isPlaying())
    return time + 10;
  return 0;
}
