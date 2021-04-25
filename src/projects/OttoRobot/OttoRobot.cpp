#include <Arduino.h>
#include <Servo.h>

Servo leftHip;
Servo rightHip;
Servo leftFoot;
Servo rightFoot;

int pos;

void setup() {
  leftHip.attach(2);
  rightHip.attach(3);
  leftFoot.attach(4);
  rightFoot.attach(5);

  leftHip.write(90);
  rightHip.write(90);
  leftFoot.write(90);
  rightFoot.write(90);
}

// the loop function runs over and over again forever
void loop() {
  for (pos = 90; pos <= 150; pos += 1) {
    rightHip.write(pos);
    rightFoot.write(pos);
    delay(15);
  }
  for (pos = 150; pos >= 90; pos -= 1) {
    rightHip.write(pos);
    rightFoot.write(pos);
    delay(15);
  }
}
