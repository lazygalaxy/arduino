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
  _finalCallback = nullptr;
  _noteIndex = -1;
  if (_taskId > 0)
    Timer::getInstance()->unschedule(_taskId);
  _taskId = 0;
  stopNote();
}

void MySpeaker::playMelody(Melody *melody, noteCallbackPtr noteCallback,
                           finalCallbackPtr finalCallback)
{
  silence();
  _melody = melody;
  _noteCallback = noteCallback;
  _finalCallback = finalCallback;
  _noteIndex = 0;
  _taskId = Timer::getInstance()->schedule(update(millis()), this, "playmelody");
}

void MySpeaker::playWav(char *filename, finalCallbackPtr finalCallback)
{
  silence();
  _finalCallback = finalCallback;
  debugPrintln(_debug, 32, "playing wav %s", 1, filename);
  tmrpcm.play(filename);
  _isWavPlaing = true;
  _taskId = Timer::getInstance()->schedule(update(millis()), this, "playwav");
}

bool MySpeaker::isMelodyPlaying() { return _noteIndex >= 0; }

bool MySpeaker::isWavPlaying() { return _isWavPlaing; }

bool MySpeaker::isSpeakerPlaying() { return isMelodyPlaying() || isWavPlaying(); }

unsigned long MySpeaker::update(unsigned long time)
{
  // isWavPlayed indicates we need to play a wav file
  if (isWavPlaying())
  {
    if (!tmrpcm.isPlaying())
    {
      debugPrintln(_debug, 32, "wav playing ended %d", 1, time);
      if (_finalCallback != nullptr)
        _finalCallback(time);
      if (!isSpeakerPlaying())
        silence();
    }
    else
      return time + 50;
  }
  // a positive index indicates we have a melody to play
  else if (isMelodyPlaying())
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
    {
      if (_finalCallback != nullptr)
        _finalCallback(time);
      if (!isSpeakerPlaying())
        silence();
    }
  }
  return time;
}
