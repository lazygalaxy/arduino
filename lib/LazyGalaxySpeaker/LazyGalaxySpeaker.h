/*
   LazyGalaxySpeaker.h - Library for Piezo Buzzer speaker.
   Created by LazyGalaxy - Evangelos Papakonstantis, August 23, 2018.
   Released into the public domain.
 */

#ifndef LAZYGALAXYSPEAKER_h
#define LAZYGALAXYSPEAKER_h

#include <LazyGalaxyCommon.h>
#include <LazyGalaxyTimer.h>
#include <Melody.h>

class LazyGalaxySpeaker : public LazyGalaxyComponent {
 public:
  LazyGalaxySpeaker(uint8_t pin);
  void playMelody(Melody* melody);
  void stopMelody();
  unsigned long update(unsigned long time) override;

 private:
  bool _isNotePlaying = false;
  Melody* _melody = nullptr;
  int _noteIndex;
  unsigned long _melodyTaskId = 0;

  void playNote(int note);
  void stopNote();
};

#endif
