#include <Arduino.h>
#include <Servo.h>

Servo leftLeg;
Servo rightLeg;
Servo leftFoot;
Servo rightFoot;

int pos;

void stand() {
  leftLeg.write(90);
  rightLeg.write(90);
  leftFoot.write(90);
  rightFoot.write(90);

  delay(1000);
}

void jump() {
  leftFoot.write(20);
  rightFoot.write(160);

  delay(1000);
}

void setup() {
  leftLeg.attach(2);
  rightLeg.attach(3);
  leftFoot.attach(4);
  rightFoot.attach(5);

  stand();
}

// the loop function runs over and over again forever
void loop() {
  // leftFoot.write(0);
  // delay(2000);
  // leftFoot.write(180);
  // delay(2000);

  jump();
  stand();
  // for (pos = 90; pos <= 150; pos += 1) {
  //   rightLeg.write(pos);

  //   delay(15);
  // }
  // for (pos = 150; pos >= 90; pos -= 1) {
  //   rightLeg.write(pos);
  //   rightFoot.write(pos);
  //   delay(15);
  // }
}
