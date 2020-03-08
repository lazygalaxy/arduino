/*
   LazyGalaxySpeaker.h - Library for Piezo Buzzer speaker.
   Created by LazyGalaxy - Evangelos Papakonstantis, August 23, 2018.
   Released into the public domain.
 */

#ifndef LAZYGALAXYSPEAKER_h
#define LAZYGALAXYSPEAKER_h

#include <LazyGalaxyCommon.h>
#include <LazyGalaxyMelody.h>
#include <LazyGalaxyTimer.h>

typedef void (*noteCallbackPtr)(unsigned long time, int note);

class LazyGalaxySpeaker : public LazyGalaxyComponent {
 public:
  LazyGalaxySpeaker(uint8_t pin);
  void playMelody(LazyGalaxyMelody* melody,
                  noteCallbackPtr noteCallback = nullptr,
                  taskCallbackPtr finalCallback = nullptr);
  void stopMelody();
  unsigned long update(unsigned long time) override;

 private:
  bool _isNotePlaying = false;
  LazyGalaxyMelody* _melody = nullptr;
  int _noteIndex;
  unsigned long _melodyTaskId = 0;
  noteCallbackPtr _noteCallback;
  taskCallbackPtr _finalCallback;

  void playNote(int note);
  void stopNote();
};

#endif
