/*
   AsyncMelody.ino - Asynchronous melody playing example.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 22, 2018.
   Released into the public domain.
*/

#include <LazyGalaxyMelody.h>
#include <LazyGalaxySpeaker.h>
#include <LazyGalaxyTimer.h>

LazyGalaxySpeaker speaker(11);

LazyGalaxyMelody* santaClausMelody = new LazyGalaxyMelody(
    (int[]){TG4, TE4, TF4, TG4, TG4, TG4, TA4, TB4, TC5, TC5,
            TC5, TE4, TF4, TG4, TG4, TG4, TA4, TG4, TF4, TF4,
            TE4, TG4, TC4, TE4, TD4, TF4, TB3, TC4, TTE},
    (int[]){2, 2, 2, 4, 4, 4, 2, 2, 4, 4, 4, 2, 2, 4,
            4, 4, 2, 2, 4, 8, 4, 4, 4, 4, 4, 8, 4, 8},
    100);

LazyGalaxyMelody* jingleBellsMelody =
    new LazyGalaxyMelody((int[]){TE5, TE5, TE5, TE5, TE5, TE5, TE5, TG5, TC5,
                                 TD5, TE5, TF5, TF5, TF5, TF5, TF5, TE5, TE5,
                                 TE5, TE5, TE5, TD5, TD5, TE5, TD5, TG5, TTE},
                         (int[]){2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 8, 2, 2,
                                 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 4, 4},
                         100);

LazyGalaxyMelody* merryChristmasMelody = new LazyGalaxyMelody(
    (int[]){TB3, TF4, TF4, TG4, TF4, TE4, TD4, TD4, TD4, TG4, TG4,
            TA4, TG4, TF4, TE4, TE4, TE4, TA4, TA4, TB4, TA4, TG4,
            TF4, TD4, TB3, TB3, TD4, TG4, TE4, TF4, TTE},
    (int[]){4, 4, 2, 2, 2, 2, 4, 4, 4, 4, 2, 2, 2, 2, 4,
            4, 4, 4, 2, 2, 2, 2, 4, 4, 2, 2, 4, 4, 4, 8},
    100);

void noteCallback(unsigned long time, int note) {
  Serial.println("played " + String(note) + " @" + String(time));
}

void finalCallback(unsigned long time) {
  // play the third melody, provide a note callback
  speaker.playMelody(merryChristmasMelody, noteCallback);
}

void taskCallback(unsigned long time) {
  // stop playing the current melody, this will interrupt the melody playing
  speaker.stopMelody();
  // play the second melody, provide a note callback and final callback to play
  // the third melody
  speaker.playMelody(jingleBellsMelody, noteCallback, finalCallback);
}

void setup() {
  Serial.begin(9600);
  // play the frist melody
  speaker.playMelody(santaClausMelody);
  // schedule a task/function callback to play the second melody in 2 seconds
  LazyGalaxyTimer::scheduleTask(2000, taskCallback);
}

void loop() {
  // update all LazyGalaxy tasks
  LazyGalaxyTimer::updateTasks();
}
