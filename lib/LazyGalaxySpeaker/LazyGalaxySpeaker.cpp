/*
   LazyGalaxySpeaker.cpp - Library for Piezo Buzzer speaker.
   Created by LazyGalaxy - Evangelos Papakonstantis, August 23, 2018.
   Released into the public domain.
 */

#include <LazyGalaxySpeaker.h>

MySpeaker::MySpeaker(uint8_t pin, char volume) : PinComponent(pin)
{
  _volume = volume;
}

void MySpeaker::setup()
{
  pinMode(_pin, OUTPUT);
  // tmrpcm.speakerPin = _pin;
  // tmrpcm.setVolume(_volume);
  // tmrpcm.quality(1);
}

void MySpeaker::reset()
{
  DEBUG_DEBUG("reset speaker");
  Component::reset();
  // note
  _melody = nullptr;
  _noteIndex = -1;
  _noteCallback = nullptr;
  stopNote();
  // wav
  _isWavPlaing = false;
  // tmrpcm.disable();
}

void MySpeaker::playNote(int note)
{
  _isNotePlaying = true;
  toneAC(note, _volume);
}

void MySpeaker::stopNote()
{
  noToneAC();
  _isNotePlaying = false;
}

void MySpeaker::playMelody(Melody *melody, noteCallbackPtr noteCallback, finalCallbackPtr finalCallback)
{
  reset();

  _melody = melody;
  _noteCallback = noteCallback;
  _noteIndex = 0;

  _triggerTime = update(millis());
  _finalCallback = finalCallback;
}

void MySpeaker::playWav(const char *filename, finalCallbackPtr finalCallback)
{
  reset();

  DEBUG_INFO("play wav %s", filename);
  // tmrpcm.play(filename);
  _isWavPlaing = true;

  _triggerTime = update(millis());
  _finalCallback = finalCallback;
}

unsigned long MySpeaker::update(unsigned long time)
{
  // isWavPlayed indicates we need to play a wav file
  if (_isWavPlaing)
  {
    // if (tmrpcm.isPlaying())
    //   return time + 50;
  }
  // a positive index indicates we have a melody to play
  else if (_noteIndex >= 0)
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
        _noteCallback(time, _melody->notes[_noteIndex]);

      return time + (_melody->beats[_noteIndex++] * _melody->tempo);
    }
  }
  return 0;
}
