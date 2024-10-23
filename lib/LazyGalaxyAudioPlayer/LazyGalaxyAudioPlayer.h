/*
   LazyGalaxyAudioPlayer.h - Library for playing audio files.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 23, 2024.
   Released into the public domain.
 */

#ifndef LAZYGALAXYAUDIOPLAYER_H
#define LAZYGALAXYAUDIOPLAYER_H

#include <LazyGalaxyCommon.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define RX_PIN 10
#define TX_PIN 11

class MyAudioPlayer : public PinComponent
{
public:
  MyAudioPlayer(char volume = 15);
  void setup() override;
  void reset() override;
  unsigned long update(unsigned long time) override;

  void play(int index);
  void stop();

private:
  char _volume;
  DFRobotDFPlayerMini _player;
  SoftwareSerial *_softwareSerial;
};

#endif
