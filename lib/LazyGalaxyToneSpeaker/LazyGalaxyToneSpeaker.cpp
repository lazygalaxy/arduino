/*
   LazyGalaxyToneSpeaker.cpp - Library for playing tones on a speaker.
   Created by LazyGalaxy - Evangelos Papakonstantis, August 23, 2018.
   Released into the public domain.
 */

#include <LazyGalaxyToneSpeaker.h>

MyToneSpeaker::MyToneSpeaker(uint8_t pin, uint8_t volume) : SinglePinComponent(pin)
{
  _volume = volume * 2.55; // convert 0-100 to 0-255
}

void MyToneSpeaker::setup()
{
  // 8 bits means the duty cycle has 2⁸ = 256 steps
  ledcSetup(PWM_CHANNEL, 1000, 8); // initial freq
  ledcAttachPin(_pin, PWM_CHANNEL);
}

void MyToneSpeaker::reset()
{
  Component::reset();
  // note
  _melody = nullptr;
  _noteIndex = -1;
  _noteCallback = nullptr;
  stopTone();
}

void MyToneSpeaker::playTone(int frequency)
{
  _isTonePlaying = true;
  ledcWrite(PWM_CHANNEL, _volume);
  ledcWriteTone(PWM_CHANNEL, frequency);
}

void MyToneSpeaker::stopTone()
{
  ledcWrite(PWM_CHANNEL, 0);
  _isTonePlaying = false;
}

void MyToneSpeaker::playMelody(Melody *melody, noteCallbackPtr noteCallback, finalCallbackPtr finalCallback)
{
  reset();

  _melody = melody;
  _noteCallback = noteCallback;
  _noteIndex = 0;

  _finalCallback = finalCallback;
  _triggerTime = update(millis());
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
