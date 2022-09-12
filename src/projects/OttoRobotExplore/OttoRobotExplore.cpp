#include <Otto9.h>
#include <US.h>
Otto9 Otto;

#define PIN_Trigger 8  // ultrasound
#define PIN_Echo 9     // ultrasound
#define PIN_YL 2       // left leg, servo[0]
#define PIN_YR 3       // right leg, servo[1]
#define PIN_RL 4       // left foot, servo[2]
#define PIN_RR 5       // right foot, servo[3]
#define PIN_Buzzer 13  // buzzer

#define TRIM_YL 0
#define TRIM_YR -10
#define TRIM_RL 0
#define TRIM_RR -10

void setup() {
  Otto.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR, true, A6, PIN_Buzzer, PIN_Trigger,
            PIN_Echo);
  Otto.setTrims(TRIM_YL, TRIM_YR, TRIM_RL, TRIM_RR);
}

void loop() {
  if (Otto.getDistance() < 15) {
    Otto.playGesture(OttoConfused);
    for (int count = 0; count < 3; count++) {
      Otto.turn(1, 1000, 1);  // LEFT
    }
  }
  Otto.walk(1, 1000, 1);  // FORWARD
}