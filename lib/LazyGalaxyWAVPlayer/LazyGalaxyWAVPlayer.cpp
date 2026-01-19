/*
   LazyGalaxyWAVPlayer.cpp - Library for playing WAV audio files.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 5, 2024.
   Released into the public domain.
 */

#include <LazyGalaxyWAVPlayer.h>

MyWAVPlayer::MyWAVPlayer(uint8_t volume) : PinComponent(DAC1)
{
  _volume = volume;
}

void MyWAVPlayer::setup()
{
  if (!LittleFS.begin())
    _statusOK = false;
  else
  {
    // if all good we can initialize audio objects
    _out = new AudioOutputI2S(0, AudioOutputI2S::INTERNAL_DAC);
    _out->SetGain(_volume / 100.0f);
    _wav = new AudioGeneratorWAV();
  }
}

void MyWAVPlayer::reset()
{
  Component::reset();
  stop();
}

void MyWAVPlayer::play(const char *filename, finalCallbackPtr finalCallback)
{
  reset();

  _finalCallback = finalCallback;
  AudioFileSourceLittleFS *file = new AudioFileSourceLittleFS(filename);
  _wav->begin(file, _out);
  _triggerTime = update(millis());
}

bool MyWAVPlayer::isPlaying()
{
  return _wav->isRunning() && _wav->loop();
}

void MyWAVPlayer::stop()
{
  _wav->stop();
}

unsigned long MyWAVPlayer::update(unsigned long time)
{
  if (isPlaying())
    return time + 10;
  return 0;
}
