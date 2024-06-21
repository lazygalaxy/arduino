#include <LazyGalaxyMotorDriver.h>

MotorDriver motorDriver(D5, D6, D7, D8, D9, D10);

void demoOne()
{
    motorDriver.setForward();
    motorDriver.setSpeed(255);
}

void setup()
{
    demoOne();
}

// void demoTwo()
// {
//     // this function will run the motors across the range of possible speeds
//     // note that maximum speed is determined by the motor itself and the operating voltage
//     // the PWM values sent by analogWrite() are fractions of the maximum speed possible
//     // by your hardware
//     // turn on motors
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, HIGH);
//     digitalWrite(in3, LOW);
//     digitalWrite(in4, HIGH);
//     // accelerate from zero to maximum speed
//     for (int i = 200; i < 256; i++)
//     {
//         analogWrite(enA, i);
//         analogWrite(enB, i);
//         delay(50);
//     }
//     // decelerate from maximum speed to zero
//     for (int i = 255; i >= 200; --i)
//     {
//         analogWrite(enA, i);
//         analogWrite(enB, i);
//         delay(50);
//     }
//     // now turn off motors
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, LOW);
//     digitalWrite(in3, LOW);
//     digitalWrite(in4, LOW);
// }

void loop()
{
}