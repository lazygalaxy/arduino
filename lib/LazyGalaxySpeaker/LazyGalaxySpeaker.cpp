/*
   LazyGalaxySpeaker.cpp - Library for Piezo Buzzer speaker.
   Created by LazyGalaxy - Evangelos Papakonstantis, August 23, 2018.
   Released into the public domain.
 */

#include <LazyGalaxySpeaker.h>

MySpeaker::MySpeaker(uint8_t pin, char volume) : PinComponent(pin)
{
  pinMode(_pin, OUTPUT);
  silence();
  tmrpcm.speakerPin = _pin;
  tmrpcm.setVolume(volume);
  tmrpcm.quality(1);
}

void MySpeaker::playNote(int note)
{
  _isNotePlaying = true;
  toneAC(note);
}

void MySpeaker::stopNote()
{
  noToneAC();
  _isNotePlaying = false;
}

void MySpeaker::silence()
{
  _isWavPlaing = false;
  tmrpcm.disable();

  _melody = nullptr;
  _noteCallback = nullptr;
  _noteIndex = -1;
  if (_taskId > 0)
    Timer::getInstance()->unschedule(_taskId);
  _taskId = 0;
  stopNote();
}

void MySpeaker::playMelody(Melody *melody, noteCallbackPtr noteCallback, finalCallbackPtr finalCallback)
{
  silence();
  _melody = melody;
  _noteCallback = noteCallback;
  _noteIndex = 0;
  _taskId = Timer::getInstance()->schedule(update(millis()), this, finalCallback);
}

void MySpeaker::playWav(const char *filename, finalCallbackPtr finalCallback)
{
  silence();
  printf("playing wav %s\n", filename);
  tmrpcm.play(filename);
  _isWavPlaing = true;
  _taskId = Timer::getInstance()->schedule(update(millis()), this, finalCallback);
}

unsigned long MySpeaker::update(unsigned long time)
{
  // isWavPlayed indicates we need to play a wav file
  if (_isWavPlaing)
  {
    if (tmrpcm.isPlaying())
      return time + 50;
    else
    {
      printf("wav playing ended %lu\n", time);
      silence();
    }
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
    else
      silence();
  }
  return time;
}
