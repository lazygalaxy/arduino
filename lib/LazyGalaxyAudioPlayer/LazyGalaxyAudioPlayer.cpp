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

  _player.begin(*_mySerial);

  // not sure why, need to call _player functions twice and tehy then work here...
  _player.volume(_volume);
  _player.volume(_volume);
  Serial.println(F("DFPlayer OK"));
  Serial.println(_volume);

  _player.numFolders();
  int16_t numFolders = _player.numFolders();
  Serial.println(numFolders);
  //_tracksInFolder = new int16_t[numFolders];
  _tracksInFolder = new int16_t[numFolders];

  for (int i = 0; i < _player.numFolders(); i++)
  {
    _player.numTracksInFolder(i + 1);
    _tracksInFolder[i] = _player.numTracksInFolder(i + 1);
    Serial.println(_tracksInFolder[i]);
  }
}

void MyAudioPlayer::reset()
{
  Component::reset();
}

void MyAudioPlayer::play(uint8_t folderNum, uint8_t trackNum)
{
  _player.playFolder(folderNum, trackNum);
}

void MyAudioPlayer::play(uint8_t folderNum)
{
  _player.repeatFolder(folderNum);
}

void MyAudioPlayer::playRandom(uint8_t folderNum)
{
  _player.playFolder(folderNum, random(_tracksInFolder[folderNum - 1]));
}

bool MyAudioPlayer::isPlaying()
{
  return _player.isPlaying();
}

void MyAudioPlayer::stop()
{
  _player.stop();
}

unsigned long MyAudioPlayer::update(unsigned long time)
{
  return 0;
}
