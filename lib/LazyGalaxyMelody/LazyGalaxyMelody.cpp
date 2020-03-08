/*
LazyGalaxyMelody.cpp - Library to represent a melody.
Created by LazyGalaxy - Evangelos Papakonstantis, November 20, 2018.
Released into the public domain.
 */

#include <LazyGalaxyMelody.h>

LazyGalaxyMelody::LazyGalaxyMelody(int *notes, int *beats, int tempo) {
  _notes = notes;
  _beats = beats;
  _tempo = tempo;
}

int *LazyGalaxyMelody::getNotes() { return _notes; }

int *LazyGalaxyMelody::getBeats() { return _beats; }

int LazyGalaxyMelody::getTempo() { return _tempo; }
