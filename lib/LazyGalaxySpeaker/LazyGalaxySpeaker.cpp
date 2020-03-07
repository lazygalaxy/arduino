/*
   LazyGalaxySpeaker.cpp - Library for Piezo Buzzer speaker.
   Created by LazyGalaxy - Evangelos Papakonstantis, August 23, 2018.
   Released into the public domain.
 */

#include <LazyGalaxySpeaker.h>

LazyGalaxySpeaker::LazyGalaxySpeaker(uint8_t pin) : LazyGalaxyComponent(pin) {
  pinMode(_pin, OUTPUT);
  stopMelody();
}

void LazyGalaxySpeaker::playNote(int note) {
  tone(_pin, note);
  _isNotePlaying = true;
}

void LazyGalaxySpeaker::stopNote() {
  noTone(_pin);
  _isNotePlaying = false;
}

void LazyGalaxySpeaker::stopMelody() {
  _melody = nullptr;
  _noteIndex = -1;
  if (_melodyTaskId > 0) {
    LazyGalaxyTimer::getInstance()->unschedule(_melodyTaskId);
  }
  _melodyTaskId = 0;
  stopNote();
}

void LazyGalaxySpeaker::playMelody(Melody* melody) {
  stopMelody();

  _melody = melody;
  _noteIndex = 0;
  _melodyTaskId =
      LazyGalaxyTimer::getInstance()->schedule(update(millis()), this);
}

unsigned long LazyGalaxySpeaker::update(unsigned long time) {
  // a positive index indicates we have a melody to play
  if (_noteIndex >= 0) {
    if (_melody->getNotes()[_noteIndex]) {
      // if the previous note we are playing is  identical to the next one
      if (_isNotePlaying && (_melody->getNotes()[_noteIndex - 1] ==
                             _melody->getNotes()[_noteIndex])) {
        // stop the note for 50 millis
        stopNote();
        return time + 50;
      }
      playNote(_melody->getNotes()[_noteIndex]);
      return time + (_melody->getBeats()[_noteIndex++] * _melody->getTempo());
    } else {
      stopMelody();
    }
  }
  return time;
}
