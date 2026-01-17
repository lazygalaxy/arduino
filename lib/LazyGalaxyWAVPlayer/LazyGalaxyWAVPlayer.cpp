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
  if (!LittleFS.begin())
    _statusOK = false;

  _out = new AudioOutputI2S(0, AudioOutputI2S::INTERNAL_DAC);
  _out->SetOutputModeMono(true);
  _out->SetGain(0.25);

  _wav = new AudioGeneratorWAV();
}

void MyWAVPlayer::reset()
{
  Component::reset();
  _hasPlayStarted = false;
  stop();
}

void MyWAVPlayer::play(const char *filename, finalCallbackPtr finalCallback)
{
  reset();

  _finalCallback = finalCallback;
  AudioFileSourceLittleFS *file = new AudioFileSourceLittleFS(filename);
  _wav->begin(file, _out);
  _hasPlayStarted = true;
  _triggerTime = update(millis());
}

bool MyWAVPlayer::isPlaying()
{
  return _wav->isRunning() || _wav->loop();
}

void MyWAVPlayer::stop()
{
  _wav->stop();
}

unsigned long MyWAVPlayer::update(unsigned long time)
{
  if (_hasPlayStarted && isPlaying())
    return time + 10;
  return 0;
}
