/*
     SUPER-DUPER COOL ARDUINO BASED MULTICOLOR SOUND PLAYING LIGHTSABER!
   HARDWARE:
     Addressable LED strip (WS2811) to get any blade color and smooth turn on effect
     MicroSD card module to play some sounds
     IMU MPU6050 (accel + gyro) to generate hum. Frequency depends on angle velocity of blade
     OR measure angle speed and play some hum sounds from SD
   CAPABILITIES:
     Smooth turning on/off with lightsaber-like sound effect
     Randomly pulsing color (you can turn it off)
     Sounds:
       MODE 1: generated hum. Frequency depends on angle velocity of blade
       MODE 2: hum sound from SD card
         Slow swing - long hum sound (randomly from 4 sounds)
         Fast swing - short hum sound (randomly from 5 sounds)
     Bright white flash when hitting
     Play one of 16 hit sounds, when hit
       Weak hit - short sound
       Hard hit - long "bzzzghghhdh" sound
     After power on blade shows current battery level from 0 to 100 percent
     Battery safe mode:
       Battery is drain BEFORE TURNING ON: GyverSaber will not turn on, button LED will PULSE a couple of times
       Battery is drain AFTER TURNING ON: GyverSaber will be turned off automatically
   CONTROL BUTTON:
     HOLD - turn on / turn off GyverSaber
     TRIPLE CLICK - change color (red - green - blue - yellow - pink - ice blue)
     QUINARY CLICK - change sound mode (hum generation - hum playing)
     Selected color and sound mode stored in EEPROM (non-volatile memory)
*/

// ---------------------------- SETTINGS -------------------------------
#define NUM_LEDS 30     // number of microcircuits WS2811 on LED strip (note: one WS2811 controls 3 LEDs!)
#define BTN_TIMEOUT 800 // button hold delay, ms
#define BRIGHTNESS 255  // max LED brightness (0 - 255)

#define SWING_TIMEOUT 500 // timeout between swings
#define SWING_L_THR 150   // swing angle speed threshold
#define SWING_THR 300     // fast swing angle speed threshold
#define STRIKE_THR 150    // hit acceleration threshold
#define STRIKE_S_THR 320  // hard hit acceleration threshold
#define FLASH_DELAY 80    // flash time while hit

#define PULSE_ALLOW 1  // blade pulsation (1 - allow, 0 - disallow)
#define PULSE_AMPL 20  // pulse amplitude
#define PULSE_DELAY 30 // delay between pulses

#define R1 100000      // voltage divider real resistance
#define R2 51000       // voltage divider real resistance
#define BATTERY_SAFE 1 // battery monitoring (1 - allow, 0 - disallow)

#define DEBUG 0 // debug information in Serial (1 - allow, 0 - disallow)
// ---------------------------- SETTINGS -------------------------------

#define LED_PIN 6
#define BTN 3
#define IMU_GND A1
#define SD_GND A0
#define VOLT_PIN A6
#define BTN_LED 4

// -------------------------- LIBS ---------------------------
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include <toneAC.h> // hum generation library
#include <LazyGalaxySpeaker.h>

MPU6050 accelgyro;
// -------------------------- LIBS ---------------------------

// ------------------------------ VARIABLES ---------------------------------
int16_t ax, ay, az;
int16_t gx, gy, gz;
unsigned long ACC, GYR, COMPL;
int gyroX, gyroY, gyroZ, accelX, accelY, accelZ, freq, freq_f = 20;
float k = 0.2;
unsigned long humTimer = -9000, mpuTimer, nowTimer;
int stopTimer;
boolean bzzz_flag, ls_chg_state, ls_state;
boolean btnState, btn_flag, hold_flag;
byte btn_counter;
unsigned long btn_timer, PULSE_timer, swing_timer, swing_timeout, battery_timer, bzzTimer;
byte nowNumber;
boolean eeprom_flag, swing_flag, swing_allow, strike_flag;
float voltage;
int PULSEOffset;
MySpeaker speaker(D13);
// ------------------------------ VARIABLES ---------------------------------

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  // ---- НАСТРОЙКА ПИНОВ ----
  pinMode(BTN, INPUT_PULLUP);
  pinMode(IMU_GND, OUTPUT);
  pinMode(SD_GND, OUTPUT);
  pinMode(BTN_LED, OUTPUT);
  digitalWrite(IMU_GND, 0);
  digitalWrite(SD_GND, 0);
  digitalWrite(BTN_LED, 1);
  // ---- НАСТРОЙКА ПИНОВ ----

  randomSeed(analogRead(2)); // starting point for random generator

  // IMU initialization
  accelgyro.initialize();
  accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_16);
  accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  if (DEBUG)
  {
    if (accelgyro.testConnection())
      Serial.println(F("MPU6050 OK"));
    else
      Serial.println(F("MPU6050 fail"));
  }
}

void getFreq()
{
  if (millis() - mpuTimer > 500)
  {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // find absolute and divide on 100
    gyroX = abs(gx / 100);
    gyroY = abs(gy / 100);
    gyroZ = abs(gz / 100);
    accelX = abs(ax / 100);
    accelY = abs(ay / 100);
    accelZ = abs(az / 100);

    // vector sum
    ACC = sq((long)accelX) + sq((long)accelY) + sq((long)accelZ);
    ACC = sqrt(ACC);
    GYR = sq((long)gyroX) + sq((long)gyroY) + sq((long)gyroZ);
    GYR = sqrt((long)GYR);
    COMPL = ACC + GYR;
    freq = (long)COMPL * COMPL / 1500; // parabolic tone change
    freq = constrain(freq, 20, 300);
    freq_f = freq * k + freq_f * (1 - k); // smooth filter
    mpuTimer = micros();

    toneAC(freq_f);
    speaker.playNote(freq_f);

    Serial.print(freq_f);
    Serial.print(" ");
    Serial.print(gyroX);
    Serial.print(" ");
    Serial.print(gyroY);
    Serial.print(" ");
    Serial.print(gyroZ);
    Serial.print(" ");
    Serial.print(accelX);
    Serial.print(" ");
    Serial.print(accelY);
    Serial.print(" ");
    Serial.print(accelZ);
    Serial.println(";");
  }
}

// --- MAIN LOOP---
void loop()
{
  getFreq();
}
// --- MAIN LOOP---
