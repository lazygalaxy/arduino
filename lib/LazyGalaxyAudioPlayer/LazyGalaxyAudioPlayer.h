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

class MyAudioPlayer : public Component
{
public:
  MyAudioPlayer(uint8_t rxPin, uint8_t txPin, uint8_t volume = 15);
  void setup() override;
  void reset() override;
  unsigned long update(unsigned long time) override;

  void play(uint8_t folderNum, uint8_t trackNum);
  void play(uint8_t folderNum);
  void playRandom(uint8_t folderNum);
  bool isPlaying();

  void stop();

private:
  uint8_t _rxPin;
  uint8_t _txPin;
  uint8_t _volume;
  SoftwareSerial *_mySerial; // RX, TX
  DFPlayerMini_Fast _player;
  int16_t *_tracksInFolder;
};

#endif
