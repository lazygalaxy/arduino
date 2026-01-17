/*
   LazyGalaxyWAVPlayer.h - Library for playing WAV audio files.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 5, 2024.
   Released into the public domain.
 */

#ifndef LAZYGALAXYWAVPLAYER_H
#define LAZYGALAXYWAVPLAYER_H

#define SDFAT

#include <LazyGalaxyCommon.h>

#include <LittleFS.h>

#include <AudioFileSourceLittleFS.h>
#include <AudioGeneratorWAV.h>
#include <AudioOutputI2S.h>

class MyWAVPlayer : public PinComponent
{
public:
  // volume is 0 (min) to 10 (max)
  MyWAVPlayer(uint8_t pin, uint8_t volume = 5);
  void setup() override;
  void reset() override;
  unsigned long update(unsigned long time) override;

  void play(const char *filename, finalCallbackPtr finalCallback = nullptr);
  bool isPlaying();

  void stop();

private:
  // Audio objects
  AudioGeneratorWAV *_wav;
  AudioOutputI2S *_out;

  uint8_t _volume;
  bool _hasPlayStarted;
};

#endif
