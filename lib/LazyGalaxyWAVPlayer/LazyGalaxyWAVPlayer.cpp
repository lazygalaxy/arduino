/*
   LazyGalaxyWAVPlayer.cpp - Library for playing WAV audio files.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 5, 2024.
   Released into the public domain.
 */

#include <LazyGalaxyWAVPlayer.h>

MyWAVPlayer::MyWAVPlayer(uint8_t volume) : Component()
{
  _volume = volume / 100.0f;
}

void MyWAVPlayer::setup()
{
  if (!LittleFS.begin())
    _statusOK = false;
  else
  {
    // if all good we can initialize audio objects
    _out = new AudioOutputI2S(0, AudioOutputI2S::INTERNAL_DAC);
    _out->SetGain(_volume);
    _wav = new AudioGeneratorWAV();
  }
}

void MyWAVPlayer::reset()
{
  Component::reset();

  _wav->stop();
  if (_file != nullptr)
  {
    delete _file;
    _file = nullptr;
  }
}

void MyWAVPlayer::play(const char *filename, finalCallbackPtr finalCallback)
{
  reset();

  _finalCallback = finalCallback;
  _file = new AudioFileSourceLittleFS(filename);
  _wav->begin(_file, _out);
  _triggerTime = 1; // start asap
}

bool MyWAVPlayer::isPlaying()
{
  return _wav->isRunning() && _wav->loop();
}

unsigned long MyWAVPlayer::update(unsigned long time)
{
  if (isPlaying())
    return time + 10;
  return 0;
}
