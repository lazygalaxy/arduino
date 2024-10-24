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
  _mySerial = new SoftwareSerial(10, 11); // RX, TX
  _mySerial->begin(9600);

  _player.begin(*_mySerial);
  Serial.println(F("DFPlayer OK"));

  Serial.print("DFPlayer volume is ");
  Serial.println(_volume);
  _player.volume(_volume);
}

void MyAudioPlayer::reset()
{
  Component::reset();
}

void MyAudioPlayer::play(uint8_t folderNum, uint8_t trackNum)
{
  _player.playFolder(folderNum, trackNum);
}

int16_t MyAudioPlayer::getNumTracks(uint8_t folderNum)
{
  return _player.numTracksInFolder(folderNum);
}

void MyAudioPlayer::stop()
{
  _player.stop();
}

unsigned long MyAudioPlayer::update(unsigned long time)
{
  return 0;
}
