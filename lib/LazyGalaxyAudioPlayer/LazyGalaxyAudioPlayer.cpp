/*
   LazyGalaxyAudioPlayer.cpp - Library for playing audio files.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 23, 2024.
   Released into the public domain.
 */

#include <LazyGalaxyAudioPlayer.h>

MyAudioPlayer::MyAudioPlayer(uint8_t volume) : PinComponent(255)
{
  _volume = volume;
}

void MyAudioPlayer::setup()
{
  SoftwareSerial secondarySerial(10, 11); // RX, TX
  _player = new DfMp3(secondarySerial);

  _player->begin();

  uint16_t version = _player->getSoftwareVersion();
  Serial.print("version ");
  Serial.println(version);

  _player->setVolume(_volume);
  uint16_t volume = _player->getVolume();
  Serial.print("volume ");
  Serial.println(volume);

  uint16_t count = _player->getTotalTrackCount(DfMp3_PlaySource_Sd);
  Serial.print("files ");
  Serial.println(count);

  Serial.println("starting...");
}

void MyAudioPlayer::reset()
{
  DEBUG_DEBUG("reset audio player");
  Component::reset();
  _player->reset();
}

void MyAudioPlayer::play(uint16_t index)
{
  DEBUG_DEBUG("play audio 1");
  _player->playMp3FolderTrack(index);
  DEBUG_DEBUG("play audio 2");
}

void MyAudioPlayer::stop()
{
  _player->stop();
}

unsigned long MyAudioPlayer::update(unsigned long time)
{
  return 0;
}
