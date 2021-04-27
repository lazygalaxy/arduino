#include <Otto9.h>
Otto9 Otto;

#define PIN_YL 2       // left leg, servo[0]
#define PIN_YR 3       // right leg, servo[1]
#define PIN_RL 4       // left foot, servo[2]
#define PIN_RR 5       // right foot, servo[3]
#define PIN_Trigger 8  // ultrasound
#define PIN_Echo 9     // ultrasound
#define PIN_Buzzer 13  // buzzer

void setup() {
  Otto.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR, true, A6, PIN_Buzzer, PIN_Trigger,
            PIN_Echo);
}

void loop() {
  Otto.sing(S_OhOoh2);
  Otto.sing(S_OhOoh2);
  Otto.walk(1, 1000, 1);  // FORWARD
  Otto.walk(1, 1000, 1);  // FORWARD
  Otto.walk(1, 1000, 1);  // FORWARD
  delay(2 * 1000);
  Otto.turn(1, 1000, -1);  // RIGHT
  Otto.turn(1, 1000, -1);  // RIGHT
  delay(2 * 1000);
}