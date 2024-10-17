/*
   SpeakerExample.cpp - Asynchronous melody playing example.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 22, 2018.
   Released into the public domain.
*/

// #include <LazyGalaxySDCard.h>
#include <LazyGalaxySpeaker.h>
#include <LazyGalaxyTimer.h>

// MySDCard sdcard(D10);
MySpeaker speaker(D9, 5);

Melody *santaClausMelody =
    new Melody((int[]){TG4, TE4, TF4, TG4, TG4, TG4, TA4, TB4, TC5, TC5,
                       TC5, TE4, TF4, TG4, TG4, TG4, TA4, TG4, TF4, TF4,
                       TE4, TG4, TC4, TE4, TD4, TF4, TB3, TC4, TEND},
               (int[]){2, 2, 2, 4, 4, 4, 2, 2, 4, 4, 4, 2, 2, 4,
                       4, 4, 2, 2, 4, 8, 4, 4, 4, 4, 4, 8, 4, 8},
               100);

Melody *jingleBellsMelody =
    new Melody((int[]){TE5, TE5, TE5, TE5, TE5, TE5, TE5, TG5, TC5,
                       TD5, TE5, TF5, TF5, TF5, TF5, TF5, TE5, TE5,
                       TE5, TE5, TE5, TD5, TD5, TE5, TD5, TG5, TEND},
               (int[]){2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 8, 2, 2,
                       2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 4, 4},
               100);

void noteCallback(unsigned long time, int note)
{
  DEBUG_DEBUG("note play %i %u", note, time);
}

void step4(unsigned long time)
{
  DEBUG_INFO("step4");
  // speaker.playWav("OFF.wav");
  speaker.playMelody(santaClausMelody, noteCallback);
}

void step3(unsigned long time)
{
  DEBUG_INFO("step3");
  speaker.playMelody(jingleBellsMelody, noteCallback, step4);
}

void step2(unsigned long time)
{
  DEBUG_INFO("step2");
  speaker.playMelody(santaClausMelody, noteCallback, step3);
}

void step1(unsigned long time)
{
  DEBUG_INFO("step1 %lu", time);
  speaker.playMelody(jingleBellsMelody, noteCallback, step2);
  // speaker.playWav("ON.wav", step2);
}

void setup()
{
  Serial.begin(9600);
  Debug.setDebugLevel(DBG_VERBOSE);

  // sdcard.setup();
  step1(millis());
  // schedule a task / function callback to play the future
  // Timer::scheduleTask(2000, updatePlayWav1);
}

void loop()
{
  // update all LazyGalaxy tasks
  Timer::updateTasks();
}
