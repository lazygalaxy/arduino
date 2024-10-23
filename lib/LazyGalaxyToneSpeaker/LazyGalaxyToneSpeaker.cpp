/*
   LazyGalaxySpeaker.cpp - Library for Piezo Buzzer speaker.
   Created by LazyGalaxy - Evangelos Papakonstantis, August 23, 2018.
   Released into the public domain.
 */

#include <LazyGalaxyToneSpeaker.h>

MyToneSpeaker::MyToneSpeaker(uint8_t pin, char volume) : PinComponent(pin)
{
  _volume = volume;
}

void MyToneSpeaker::setup()
{
  pinMode(_pin, OUTPUT);
}

void MyToneSpeaker::reset()
{
  DEBUG_DEBUG("reset speaker");
  Component::reset();
  // note
  _melody = nullptr;
  _noteIndex = -1;
  _noteCallback = nullptr;
  stopTone();
}

void MyToneSpeaker::playTone(int tone)
{
  _isTonePlaying = true;
  toneAC(tone, _volume);
}

void MyToneSpeaker::stopTone()
{
  noToneAC();
  _isTonePlaying = false;
}

void MyToneSpeaker::playMelody(Melody *melody, noteCallbackPtr noteCallback, finalCallbackPtr finalCallback)
{
  reset();

  _melody = melody;
  _noteCallback = noteCallback;
  _noteIndex = 0;

  _triggerTime = update(millis());
  _finalCallback = finalCallback;
}

unsigned long MyToneSpeaker::update(unsigned long time)
{
  // a positive index indicates we have a melody to play
  if (_noteIndex >= 0)
  {
    if (_melody->notes[_noteIndex])
    {
      // if the previous note we are playing is identical to the next one
      if (_isTonePlaying &&
          (_melody->notes[_noteIndex - 1] == _melody->notes[_noteIndex]))
      {
        // stop the note for 50 millis
        stopTone();
        return time + 50;
      }
      playTone(_melody->notes[_noteIndex]);
      if (_noteCallback != nullptr)
        _noteCallback(time, _melody->notes[_noteIndex]);

      return time + (_melody->beats[_noteIndex++] * _melody->tempo);
    }
  }
  return 0;
}
