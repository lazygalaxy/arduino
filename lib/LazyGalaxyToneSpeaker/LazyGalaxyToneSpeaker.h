/*
   LazyGalaxyToneSpeaker.h - Library for playing tones on a speaker.
   Created by LazyGalaxy - Evangelos Papakonstantis, August 23, 2018.
   Released into the public domain.
 */

#ifndef LAZYGALAXYTONESPEAKER_H
#define LAZYGALAXYTONESPEAKER_H

#include <LazyGalaxyCommon.h>

#define PWM_CHANNEL 0

// Tones for easy reference
#define TEND 0 // tone end
#define TB0 31
#define TC1 33
#define TCS1 35
#define TD1 37
#define TDS1 39
#define TE1 41
#define TF1 44
#define TFS1 46
#define TG1 49
#define TGS1 52
#define TA1 55
#define TAS1 58
#define TB1 62
#define TC2 65
#define TCS2 69
#define TD2 73
#define TDS2 78
#define TE2 82
#define TF2 87
#define TFS2 93
#define TG2 98
#define TGS2 104
#define TA2 110
#define TAS2 117
#define TB2 123
#define TC3 131
#define TCS3 139
#define TD3 147
#define TDS3 156
#define TE3 165
#define TF3 175
#define TFS3 185
#define TG3 196
#define TGS3 208
#define TA3 220
#define TAS3 233
#define TB3 247
#define TC4 262
#define TCS4 277
#define TD4 294
#define TDS4 311
#define TE4 330
#define TF4 349
#define TFS4 370
#define TG4 392
#define TGS4 415
#define TA4 440
#define TAS4 466
#define TB4 494
#define TC5 523
#define TCS5 554
#define TD5 587
#define TDS5 622
#define TE5 659
#define TF5 698
#define TFS5 740
#define TG5 784
#define TGS5 831
#define TA5 880
#define TAS5 932
#define TB5 988
#define TC6 1047
#define TCS6 1109
#define TD6 1175
#define TDS6 1245
#define TE6 1319
#define TF6 1397
#define TFS6 1480
#define TG6 1568
#define TGS6 1661
#define TA6 1760
#define TAS6 1865
#define TB6 1976
#define TC7 2093
#define TCS7 2217
#define TD7 2349
#define TDS7 2489
#define TE7 2637
#define TF7 2794
#define TFS7 2960
#define TG7 3136
#define TGS7 3322
#define TA7 3520
#define TAS7 3729
#define TB7 3951
#define TC8 4186
#define TCS8 4435
#define TD8 4699
#define TDS8 4978

typedef void (*noteCallbackPtr)(unsigned long time, int note);

struct Melody
{
  Melody(int notes[], int beats[], int tempo)
  {
    this->notes = notes;
    this->beats = beats;
    this->tempo = tempo;
  }

  int *notes;
  int *beats;
  int tempo;
};

class MyToneSpeaker : public SinglePinComponent
{
public:
  // volume is 0 (min) to 100 (max)
  MyToneSpeaker(uint8_t pin, uint8_t volume = 50);
  void setup() override;
  void reset() override;
  unsigned long update(unsigned long time) override;

  void playTone(int frequency);
  void stopTone();
  void playMelody(Melody *melody, noteCallbackPtr noteCallback = nullptr, finalCallbackPtr finalCallback = nullptr);

private:
  // general
  uint32_t _volume;

  // note
  Melody *_melody;
  bool _isTonePlaying;
  int _noteIndex;
  noteCallbackPtr _noteCallback;
};

#endif
