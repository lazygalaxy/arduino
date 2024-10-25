/*
   LazyGalaxyAudioPlayer.cpp - Library for playing audio files.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 23, 2024.
   Released into the public domain.
 */

#include <LazyGalaxyAudioPlayer.h>

MyAudioPlayer::MyAudioPlayer(uint8_t rxPin, uint8_t txPin, uint8_t volume) : Component()
{
  _rxPin = rxPin;
  _txPin = txPin;
  _volume = volume;
}

void MyAudioPlayer::setup()
{
  _mySerial = new SoftwareSerial(_rxPin, _txPin); // RX, TX
  _mySerial->begin(9600);

  _player.begin(*_mySerial, false, 1000);
  // set the volume twice, seems like a bug in the lib
  _player.volume(_volume);
  _player.volume(_volume);
  Serial.println(F("DFPlayer OK"));
  Serial.print("DFPlayer volume is ");
  Serial.println(_volume);
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
