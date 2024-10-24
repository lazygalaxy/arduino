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
  MyAudioPlayer(uint8_t rxPin = D10, uint8_t txPin = D11, uint8_t volume = 15);
  void setup() override;
  void reset() override;
  unsigned long update(unsigned long time) override;

  void play(uint8_t folderNum, uint8_t trackNum);
  int16_t getNumTracks(uint8_t folderNum);

  void stop();

private:
  uint8_t _rxPin;
  uint8_t _txPin;
  uint8_t _volume;
  SoftwareSerial *_mySerial; // RX, TX
  DFPlayerMini_Fast _player;
};

#endif
