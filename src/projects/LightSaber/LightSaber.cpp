// #include <Adafruit_MPU6050.h>
// #include <Adafruit_Sensor.h>
#include <LazyGalaxySpeaker.h>
#include <LazyGalaxyTimer.h>

// Adafruit_MPU6050 accelgyro;
MySpeaker speaker(D13);

unsigned long ACC, GYR, COMPL;
int freq_prev = 20;
float k = 0.2;

int counter = 30;
int change = +1;

void playHum(unsigned long time)
{
  // unsigned int freq = (cos(time / 100) * 100) + 550;
  // Serial.println(freq);
  if (counter >= 2000)
  {
    change = -1;
  }
  else if (counter <= 500)
  {
    change = +1;
  }
  counter += change;
  speaker.playNote(counter);
}

void setup(void)
{
  Serial.begin(9600);
  while (!Serial)
  {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

  // Try to initialize!
  // if (!accelgyro.begin()) {
  //   Serial.println("Failed to find MPU6050 chip");
  //   while (1) {
  //     delay(10);
  //   }
  // }

  // accelgyro.setAccelerometerRange(MPU6050_RANGE_16_G);
  // accelgyro.setGyroRange(MPU6050_RANGE_250_DEG);
  // accelgyro.setFilterBandwidth(MPU6050_BAND_21_HZ);
  // Serial.println("");
  // delay(100);

  Timer::scheduleTask(3000, playHum);
}

void loop()
{
  // sensors_event_t a, g, temp;
  // accelgyro.getEvent(&a, &g, &temp);

  // // vector sum
  // ACC = sq((long)a.acceleration.x) + sq((long)a.acceleration.y) +
  //       sq((long)a.acceleration.z);
  // ACC = sqrt(ACC);
  // GYR = sq((long)g.gyro.x) + sq((long)g.gyro.y) + sq((long)g.gyro.z);
  // GYR = sqrt((long)GYR);
  // COMPL = ACC + GYR;
  // /*
  //    // отладка работы IMU
  //    Serial.print("$");
  //    Serial.print(gyroX);
  //    Serial.print(" ");
  //    Serial.print(gyroY);
  //    Serial.print(" ");
  //    Serial.print(gyroZ);
  //    Serial.println(";");
  // */
  // int freq_new = (long)COMPL * COMPL;  // parabolic tone change
  //                                      // freq = constrain(freq, 18, 300);
  // freq_new = (freq_prev * k) + (freq_new * (1 - k));  // smooth filter
  // // Serial.println(freq_new);
  // freq_prev = freq_new;

  Timer::updateTasks();
}