/*
   ChristmasPartyScene.cpp - Roger Christmas scene implementation
   Created by LazyGalaxy - Evangelos Papakonstantis, October 24, 2024.
   Released into the public domain.
*/

#include <LazyGalaxySystem.h>
#include <LazyGalaxyTimer.h>
#include <LazyGalaxyLED.h>
#include <LazyGalaxyAudioPlayer.h>

// the speaker volume from 0 to 30
static const uint8_t SPEAKER_VOLUME = 15;
// how long each scene lasts in milliseconds
static const unsigned int SCENE_DURATION_MILLIS = 10000;
// how long does the disco light blink
static const unsigned int DISCO_BLINK_MILLIS = 500;

// keep track of the Christmas vs Disco Scenes
bool isChristmasScene = true;

// all scene components
LED *chrismasLED = new LED(D4);
LED *discoLED = new LED(D5);
MyAudioPlayer *audioPlayer = new MyAudioPlayer(SPEAKER_VOLUME);

unsigned long playScene(unsigned long time)
{
  if (isChristmasScene)
  {
    // our christmas scene logic
    discoLED->stopBlink();
    chrismasLED->setLight(true);
    audioPlayer->play(1);
  }
  else
  {
    // our disco scene logic
    chrismasLED->setLight(false);
    discoLED->startBlink(DISCO_BLINK_MILLIS);
    audioPlayer->play(2);
  }

  // switch the scene flag
  isChristmasScene = !isChristmasScene;
  // schedule the timer for the next scene
  return time + SCENE_DURATION_MILLIS;
}

void setup()
{
  Serial.begin(115200);

  // System setup
  System::add(chrismasLED);
  System::add(discoLED);
  System::add(audioPlayer);
  System::setup();

  // schedule the timer immediatly to play a scene
  Timer::schedule(0, playScene);
}

void loop()
{
  System::loop();
  Timer::loop();
}
