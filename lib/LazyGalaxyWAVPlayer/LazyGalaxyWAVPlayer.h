/*
   LazyGalaxyWAVPlayer.h - Library for playing WAV audio files.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 5, 2024.
   Released into the public domain.
 */

#ifndef LAZYGALAXYWAVPLAYER_H
#define LAZYGALAXYWAVPLAYER_H

#include <LazyGalaxyCommon.h>
#include <unordered_map>
#include <LittleFS.h>
#include <AudioFileSourceLittleFS.h>
#include <AudioGeneratorWAV.h>
#include <AudioOutputI2S.h>

class MyWAVPlayer : public PinComponent
{
public:
  // volume is 0 (min) to 100 (max)
  MyWAVPlayer(uint8_t volume = 50);
  void setup() override;
  void reset() override;
  unsigned long update(unsigned long time) override;

  void play(const char *filename, finalCallbackPtr finalCallback = nullptr);
  bool isPlaying();

private:
  uint8_t _volume;

  // Audio objects
  AudioGeneratorWAV *_wav;
  AudioOutputI2S *_out;
  AudioFileSourceLittleFS *_file;
};

#endif
