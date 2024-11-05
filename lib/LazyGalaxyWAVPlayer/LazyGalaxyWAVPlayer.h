/*
   LazyGalaxyWAVPlayer.h - Library for playing WAV audio files.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 5, 2024.
   Released into the public domain.
 */

#ifndef LAZYGALAXYWAVPLAYER_H
#define LAZYGALAXYWAVPLAYER_H

#include <LazyGalaxyCommon.h>
#include <TMRpcm.h>

class MyWAVPlayer : public PinComponent
{
public:
  MyWAVPlayer(uint8_t pin, char volume = 15);
  void setup() override;
  void reset() override;
  unsigned long update(unsigned long time) override;

  void play(const char *filename, finalCallbackPtr finalCallback = nullptr);
  bool isPlaying();

  void stop();

private:
  char _volume;
  TMRpcm _player;
  bool _hasPlayStarted;
};

#endif
