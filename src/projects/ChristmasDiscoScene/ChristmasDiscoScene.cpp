/*
   ChristmasPartyScene.cpp - Roger's Christmas scene implementation
   Created by LazyGalaxy - Evangelos Papakonstantis, October 24, 2024.
   Released into the public domain.
*/

#include <LazyGalaxyButton.h>
#include <LazyGalaxyCircuit.h>
#include <LazyGalaxyLED.h>
#include <LazyGalaxyAudioPlayer.h>

// the speaker volume from 0 to 30
static const uint8_t SPEAKER_VOLUME = 20;

bool flag = false;
// all scene components
MyLED chrismasLED(D2);
// MyLED discoLED(D3);
MyButton button(D5);

MyAudioPlayer audioPlayer(D10, D11, SPEAKER_VOLUME);

void buttonPress(unsigned long time, uint8_t clicks)
{
  // Serial.print("press");
  if (clicks > 0)
  {
    // Serial.print("click");
    if (!flag)
    {
      audioPlayer.playAll(1);
      chrismasLED.setLight(true);
      // Serial.print("play");
    }
    else
    {
      audioPlayer.stop();
      chrismasLED.setLight(false);
      // Serial.print("stop");
    }
    flag = !flag;
  }
}

void setup()
{
  // Serial.begin(115200);
  randomSeed(analogRead(A0));

  Circuit::add(&audioPlayer);
  Circuit::add(&button);
  Circuit::setup();

  button.startClicksCallback(buttonPress);
}

void loop()
{
  // loop through the circuit components and the timers
  Circuit::loop();
}
