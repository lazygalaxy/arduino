/*
   LazyGalaxySpeaker.cpp - Library for Piezo Buzzer speaker.
   Created by LazyGalaxy - Evangelos Papakonstantis, August 23, 2018.
   Released into the public domain.
 */

#include <LazyGalaxySpeaker.h>

MySpeaker::MySpeaker(uint8_t pin) : PinComponent(pin)
{
  pinMode(_pin, OUTPUT);
  stopMelody();
}

void MySpeaker::playNote(int note)
{
  tone(_pin, note);
  _isNotePlaying = true;
}

void MySpeaker::stopNote()
{
  noTone(_pin);
  _isNotePlaying = false;
}

void MySpeaker::stopMelody()
{
  _melody = nullptr;
  _noteCallback = nullptr;
  _finalCallback = nullptr;
  _noteIndex = -1;
  if (_melodyTaskId > 0)
  {
    Timer::getInstance()->unschedule(_melodyTaskId);
  }
  _melodyTaskId = 0;
  stopNote();
}

void MySpeaker::playMelody(Melody *melody, noteCallbackPtr noteCallback,
                           taskCallbackPtr finalCallback)
{
  stopMelody();
  _melody = melody;
  _noteCallback = noteCallback;
  _finalCallback = finalCallback;
  _noteIndex = 0;
  _melodyTaskId = Timer::getInstance()->schedule(update(millis()), this);
}

bool MySpeaker::isPlaying() { return _noteIndex != -1; }

unsigned long MySpeaker::update(unsigned long time)
{
  // a positive index indicates we have a melody to play
  if (_noteIndex >= 0)
  {
    if (_melody->notes[_noteIndex])
    {
      // if the previous note we are playing is identical to the next one
      if (_isNotePlaying &&
          (_melody->notes[_noteIndex - 1] == _melody->notes[_noteIndex]))
      {
        // stop the note for 50 millis
        stopNote();
        return time + 50;
      }
      playNote(_melody->notes[_noteIndex]);
      if (_noteCallback != nullptr)
      {
        _noteCallback(time, _melody->notes[_noteIndex]);
      }
      return time + (_melody->beats[_noteIndex++] * _melody->tempo);
    }
    else
    {
      taskCallbackPtr tempFinalCallback = _finalCallback;
      stopMelody();
      if (tempFinalCallback != nullptr)
      {
        tempFinalCallback(time);
      }
    }
  }
  return time;
}
