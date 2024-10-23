/*
   LazyGalaxyAudioPlayer.h - Library for playing audio files.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 23, 2024.
   Released into the public domain.
 */

#ifndef LAZYGALAXYAUDIOPLAYER_H
#define LAZYGALAXYAUDIOPLAYER_H

#include <LazyGalaxyCommon.h>
#include <DFPlayerMini_Fast.h>
#include <SoftwareSerial.h>

class MyAudioPlayer : public PinComponent
{
public:
  MyAudioPlayer(uint8_t volume = 15);
  void setup() override;
  void reset() override;
  unsigned long update(unsigned long time) override;

  void play(uint16_t index);
  void stop();

private:
  uint8_t _volume;
  DFPlayerMini_Fast _player;
};

#endif
