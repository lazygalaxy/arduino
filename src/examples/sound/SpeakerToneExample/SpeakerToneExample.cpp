/*
   SpeakerToneExample.cpp - Asynchronous melody and sound playing example.
   Created by LazyGalaxy - Evangelos Papakonstantis, August 18, 2025.
   Released into the public domain.
*/

#include <LazyGalaxyCircuit.h>
#include <LazyGalaxyToneSpeaker.h>

MyToneSpeaker toneSpeaker(D8, 10);

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

Melody *zorbasMelody =
    new Melody((int[]){TCS4, TD4, TCS4, TD4,
                       TEND},
               (int[]){1, 16, 1, 16},
               100);

void noteCallback(unsigned long time, int note)
{
  Serial.print("note play ");
  Serial.println(note);
}

void step2(unsigned long time)
{
  Serial.println("step2");
  toneSpeaker.playMelody(santaClausMelody, noteCallback);
}

void setup()
{
  Circuit::add(&toneSpeaker);
  Circuit::setup();

  toneSpeaker.playMelody(jingleBellsMelody, noteCallback, step2);
}

void loop()
{
  Circuit::loop();
}
