//----------------------------------------------------------------
//-- Otto Dance single ladies
//-- This code will make Otto dance play the by Beyonce song at the same time
// and see it in action
//-- April 2019: Designed to work with the basic Otto but could be compatible
// with PLUS or Humanoid or other biped robots
/******************************************************************************************************
  Make sure to have installed all libraries:
 https://wikifactory.com/+OttoDIY/otto-diy Otto DIY invests time and resources
 providing open source code and hardware, please support by purchasing kits from
 (https://www.ottodiy.com) BSD license, all text above must be included in any
 redistribution
 *******************************************************************/
//-----------------------------------------------------------------
#include <Otto9.h>
Otto9 Otto;

#define N_SERVOS 4

#define TRIM_YL 0
#define TRIM_YR -10
#define TRIM_RL 0
#define TRIM_RR -10

#define PIN_Trigger 8      // ultrasound
#define PIN_Echo 9         // ultrasound
#define PIN_YL 2           // left leg, servo[0]
#define PIN_YR 3           // right leg, servo[1]
#define PIN_RL 4           // left foot, servo[2]
#define PIN_RR 5           // right foot, servo[3]
#define PIN_Buzzer 13      // buzzer
#define PIN_NoiseSensor A6 // buzzer

#define INTERVALTIME 10.0

Oscillator servo[N_SERVOS];

void drunk(int tempo);
void kickLeft(int tempo);
void kickRight(int tempo);
void pasitos(int steps, int tempo);
void run(int steps, int T = 500);
void walk(int steps, int T = 1000);
void backyard(int steps, int T = 3000);
void moonWalkLeft(int steps, int T = 1000);
void moonWalkRight(int steps, int T = 1000);
void crusaito(int steps, int T = 1000);
void swing(int steps, int T = 1000);
void upDown(int steps, int tempo);
void flapping(int steps, int T = 1000);

void setup()
{
  Otto.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR, true, PIN_NoiseSensor, PIN_Buzzer,
            PIN_Trigger, PIN_Echo);
  Otto.setTrims(TRIM_YL, TRIM_YR, TRIM_RL, TRIM_RR);

  servo[0].attach(PIN_YL);
  servo[1].attach(PIN_YR);
  servo[2].attach(PIN_RL);
  servo[3].attach(PIN_RR);

  Otto.home();
}

// TEMPO: 97 BPM
int t = 620;
double pause = 0;

//////////////////////////////////CONTROL
/// FUNCTIONS//////////////////////////////////
void oscillate(int A[N_SERVOS], int O[N_SERVOS], int T,
               double phase_diff[N_SERVOS])
{
  for (int i = 0; i < 4; i++)
  {
    servo[i].SetO(O[i]);
    servo[i].SetA(A[i]);
    servo[i].SetT(T);
    servo[i].SetPh(phase_diff[i]);
  }
  double ref = millis();
  for (double x = ref; x < T + ref; x = millis())
  {
    for (int i = 0; i < 4; i++)
    {
      servo[i].refresh();
    }
  }
}

unsigned long final_time;
unsigned long interval_time;
int oneTime;
int iteration;
float increment[N_SERVOS];
int oldPosition[] = {90, 90, 90, 90};

void moveNServos(int time, int newPosition[])
{
  for (int i = 0; i < N_SERVOS; i++)
    increment[i] = ((newPosition[i]) - oldPosition[i]) / (time / INTERVALTIME);

  final_time = millis() + time;

  iteration = 1;
  while (millis() < final_time)
  { // Javi del futuro cambia esto
    interval_time = millis() + INTERVALTIME;

    oneTime = 0;
    while (millis() < interval_time)
    {
      if (oneTime < 1)
      {
        for (int i = 0; i < N_SERVOS; i++)
        {
          servo[i].SetPosition(oldPosition[i] + (iteration * increment[i]));
        }
        iteration++;
        oneTime++;
      }
    }
  }

  for (int i = 0; i < N_SERVOS; i++)
  {
    oldPosition[i] = newPosition[i];
  }
}
////////////////////////////////Dance Steps////////////////////////////////
void pasitos(int steps, int tempo)
{
  int move1[4] = {90, 120, 60, 60};
  int move2[4] = {90, 90, 90, 90};
  int move3[4] = {60, 90, 120, 120};
  int move4[4] = {90, 90, 90, 90};

  for (int i = 0; i < steps; i++)
  {
    pause = millis();
    moveNServos(tempo * 0.25, move1);
    moveNServos(tempo * 0.25, move2);
    moveNServos(tempo * 0.25, move3);
    moveNServos(tempo * 0.25, move4);
    while (millis() < (pause + t))
      ;
  }
}

void patada(int tempo)
{
  for (int i = 0; i < 4; i++)
    servo[i].SetPosition(90);
  servo[0].SetPosition(115);
  servo[1].SetPosition(120);
  delay(tempo / 4);
  servo[0].SetPosition(115);
  servo[1].SetPosition(70);
  delay(tempo / 4);
  servo[0].SetPosition(100);
  servo[1].SetPosition(80);
  delay(tempo / 4);
  servo[0].SetPosition(90);
  servo[1].SetPosition(90);
  delay(tempo / 4);
}

void twist(int steps, int tempo)
{
  int move1[4] = {90, 90, 50, 130};
  int move2[4] = {90, 90, 90, 90};

  for (int x = 0; x < steps; x++)
  {
    pause = millis();
    moveNServos(tempo * 0.1, move1);
    moveNServos(tempo * 0.1, move2);
    while (millis() < (pause + tempo))
      ;
  }
}

void reverencia1(int steps, int tempo)
{
  int move1[4] = {130, 50, 90, 90};
  int move2[4] = {90, 90, 90, 90};

  for (int x = 0; x < steps; x++)
  {
    pause = millis();
    for (int i = 0; i < 4; i++)
      servo[i].SetPosition(90);
    moveNServos(tempo * 0.3, move1);
    delay(tempo * 0.2);
    moveNServos(tempo * 0.3, move2);
    while (millis() < (pause + tempo))
      ;
  }
}

void reverencia2(int steps, int tempo)
{
  int move1[4] = {130, 50, 90, 90};
  int move2[4] = {130, 50, 60, 120};
  int move3[4] = {90, 90, 90, 90};

  for (int x = 0; x < steps; x++)
  {
    pause = millis();
    for (int i = 0; i < 4; i++)
      servo[i].SetPosition(90);
    delay(tempo * 0.2);
    moveNServos(tempo * 0.05, move1);
    moveNServos(tempo * 0.05, move2);
    moveNServos(tempo * 0.05, move1);
    moveNServos(tempo * 0.05, move2);
    delay(tempo * 0.2);
    moveNServos(tempo * 0.1, move3);
    while (millis() < (pause + tempo))
      ;
  }
}

void saludo(int steps, int tempo)
{
  int move1[4] = {60, 60, 90, 90};
  int move2[4] = {120, 60, 90, 90};

  for (int x = 0; x < steps; x++)
  {
    pause = millis();
    for (int i = 0; i < 4; i++)
      servo[i].SetPosition(90);
    moveNServos(tempo * 0.25, move1);
    moveNServos(tempo * 0.25, move2);
    moveNServos(tempo * 0.25, move1);
    moveNServos(tempo * 0.25, move2);
    while (millis() < (pause + tempo))
      ;
  }
}

void upDown(int steps, int tempo)
{
  int move1[4] = {50, 130, 90, 90};
  int move2[4] = {90, 90, 90, 90};

  for (int x = 0; x < steps; x++)
  {
    pause = millis();
    moveNServos(tempo * 0.2, move1);
    delay(tempo * 0.4);
    moveNServos(tempo * 0.2, move2);
    while (millis() < (pause + tempo))
      ;
  }
}

void lateral_fuerte(boolean side, int tempo)
{
  for (int i = 0; i < 4; i++)
    servo[i].SetPosition(90);
  if (side)
    servo[0].SetPosition(40);
  else
    servo[1].SetPosition(140);
  delay(tempo / 2);
  servo[0].SetPosition(90);
  servo[1].SetPosition(90);
  delay(tempo / 2);
}

void run(int steps, int T)
{
  int A[4] = {10, 10, 10, 10};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};

  for (int i = 0; i < steps; i++)
    oscillate(A, O, T, phase_diff);
}

void drunk(int tempo)
{
  pause = millis();

  int move1[] = {60, 70, 90, 90};
  int move2[] = {110, 120, 90, 90};
  int move3[] = {60, 70, 90, 90};
  int move4[] = {110, 120, 90, 90};
  int move5[] = {90, 90, 90, 90};

  moveNServos(tempo * 0.235, move1);
  moveNServos(tempo * 0.235, move2);
  moveNServos(tempo * 0.235, move3);
  moveNServos(tempo * 0.235, move4);
  moveNServos(tempo * 0.06, move5);
  while (millis() < (pause + tempo))
    ;
}

void kickLeft(int tempo)
{
  for (int i = 0; i < 4; i++)
    servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(50); // pie derecho
  servo[1].SetPosition(60); // pie izquiero
  delay(tempo);
  servo[0].SetPosition(80); // pie derecho
  servo[1].SetPosition(60); // pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(40); // pie derecho
  servo[1].SetPosition(60); // pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(80); // pie derecho
  servo[1].SetPosition(60); // pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(40); // pie derecho
  servo[1].SetPosition(60); // pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(80); // pie derecho
  servo[1].SetPosition(60); // pie izquiero
  delay(tempo);
}

void kickRight(int tempo)
{
  for (int i = 0; i < 4; i++)
    servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(120); // pie derecho
  servo[1].SetPosition(130); // pie izquiero
  delay(tempo);
  servo[0].SetPosition(120); // pie derecho
  servo[1].SetPosition(100); // pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(120); // pie derecho
  servo[1].SetPosition(140); // pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(120); // pie derecho
  servo[1].SetPosition(80);  // pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(120); // pie derecho
  servo[1].SetPosition(140); // pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(120); // pie derecho
  servo[1].SetPosition(100); // pie izquiero
  delay(tempo);
}

void walk(int steps, int T)
{
  int A[4] = {15, 15, 30, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};

  for (int i = 0; i < steps; i++)
    oscillate(A, O, T, phase_diff);
}

void backyard(int steps, int T)
{
  int A[4] = {15, 15, 30, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)};

  for (int i = 0; i < steps; i++)
    oscillate(A, O, T, phase_diff);
}

void moonWalkRight(int steps, int T)
{
  int A[4] = {25, 25, 0, 0};
  int O[4] = {-15, 15, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90),
                          DEG2RAD(90)};

  for (int i = 0; i < steps; i++)
    oscillate(A, O, T, phase_diff);
}

void moonWalkLeft(int steps, int T)
{
  int A[4] = {25, 25, 0, 0};
  int O[4] = {-15, 15, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90),
                          DEG2RAD(90)};

  for (int i = 0; i < steps; i++)
    oscillate(A, O, T, phase_diff);
}

void crusaito(int steps, int T)
{
  int A[4] = {25, 25, 30, 30};
  int O[4] = {-15, 15, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90),
                          DEG2RAD(90)};

  for (int i = 0; i < steps; i++)
    oscillate(A, O, T, phase_diff);
}

void swing(int steps, int T)
{
  int A[4] = {25, 25, 0, 0};
  int O[4] = {-15, 15, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};

  for (int i = 0; i < steps; i++)
    oscillate(A, O, T, phase_diff);
}

void flapping(int steps, int T)
{
  int A[4] = {15, 15, 8, 8};
  int O[4] = {-A[0], A[1], 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};

  for (int i = 0; i < steps; i++)
    oscillate(A, O, T, phase_diff);
}

void loop()
{
  if (Otto.getDistance() < 15)
  {
    pasitos(8, t * 2);
    crusaito(1, t);
    patada(t);
    delay(t);
    twist(2, t);
    twist(3, t / 2);
    upDown(1, t * 2);
    patada(t * 2);
    drunk(t * 2);
    flapping(1, t * 2);
    walk(2, t);
    walk(1, t * 2);
    backyard(2, t);
    patada(t * 2);
    flapping(1, t * 2);
    patada(t * 2);
    twist(8, t / 2);
    moonWalkLeft(2, t);
    crusaito(1, t * 2);

    for (int i = 0; i < 2; i++)
    {
      lateral_fuerte(0, t);
      lateral_fuerte(1, t);
      upDown(1, t * 2);
    }

    saludo(1, t * 2);
    saludo(1, t);
    delay(t);
    swing(3, t);
    for (int i = 0; i < 4; i++)
      servo[i].SetPosition(90);
    delay(t);

    lateral_fuerte(0, t);
    lateral_fuerte(1, t);
    lateral_fuerte(0, t / 2);
    lateral_fuerte(1, t / 2);
    lateral_fuerte(0, t / 2);
    delay(t / 2);
    lateral_fuerte(0, t);
    lateral_fuerte(1, t);
    lateral_fuerte(0, t / 2);
    lateral_fuerte(1, t / 2);
    delay(t);

    pasitos(1, t * 2);
    pasitos(1, t);
    delay(t / 2);
    pasitos(1, t * 2);
    pasitos(1, t);
    delay(t / 2);

    crusaito(2, t);
    crusaito(1, t * 2);
    crusaito(2, t);
    crusaito(1, t * 2);
    crusaito(2, t);
    crusaito(1, t * 2);

    upDown(2, t);
    crusaito(1, t * 2);
    for (int i = 0; i < 4; i++)
      servo[i].SetPosition(90);
    delay(t / 2);
    pasitos(2, t * 2);
    pasitos(2, t);
    flapping(1, t * 2);
    upDown(2, t);
    upDown(1, t * 2);

    for (int i = 0; i < 4; i++)
    {
      pasitos(1, t);
      delay(t);
    }
    reverencia1(1, t * 4);
    reverencia2(1, t * 4);
    upDown(1, t);
    run(2, t / 2);
    patada(t * 2);

    lateral_fuerte(0, t);
    lateral_fuerte(1, t);
    upDown(2, t);
    lateral_fuerte(0, t);
    lateral_fuerte(1, t);
    upDown(2, t);
    pasitos(4, t);
    lateral_fuerte(0, t);
    lateral_fuerte(1, t);
    upDown(2, t);

    patada(t * 2);
    pasitos(2, t);
    patada(t * 2);
    pasitos(2, t);
    swing(2, t * 2);
    pasitos(4, t);

    for (int i = 0; i < 4; i++)
    {
      lateral_fuerte(0, t);
      lateral_fuerte(1, t);
      lateral_fuerte(0, t / 2);
      lateral_fuerte(1, t / 2);
      lateral_fuerte(0, t / 2);
      delay(t / 2);
    }

    pasitos(6, t);
    delay(t);
    pasitos(1, t);
    delay(t / 2);
    pasitos(3, t);
    delay(t / 2);
    swing(4, t);

    twist(2, t / 2);
    delay(t / 2);
    twist(2, t / 2);
    delay(t / 2);

    drunk(t * 2);
    drunk(t / 2);
    drunk(t * 2);
    delay(t / 2);
    walk(1, t);
    backyard(1, t);

    servo[0].SetPosition(110);
    servo[1].SetPosition(130);
    delay(t);

    crusaito(3, t);
    crusaito(1, 2 * t);
    upDown(1, t * 2);
    upDown(2, t / 2);

    kickLeft(t / 2);
    kickRight(t / 2);
    moonWalkLeft(1, t * 2);
    moonWalkLeft(2, t);
    moonWalkRight(1, t * 2);
    moonWalkRight(2, t);

    walk(4, t);
    backyard(4, t);

    lateral_fuerte(0, t);
    lateral_fuerte(0, t);
    lateral_fuerte(1, t);
    lateral_fuerte(1, t);
    walk(2, t);
    backyard(2, t);

    pasitos(6, t * 2);
    swing(1, t);
    upDown(1, t);
    delay(t);
    upDown(6, t);
    delay(t);

    for (int i = 0; i < 4; i++)
    {
      lateral_fuerte(0, t);
      lateral_fuerte(1, t);
    }

    delay(t);
    for (int i = 0; i < 7; i++)
    {
      pasitos(2, t);
      swing(2, t);
    }

    pasitos(1, t);
    crusaito(1, t * 2);
    upDown(1, t);

    delay(2000);
  }
}
