#include <Arduino.h>
#include <DFPlayerMini_Fast.h>

#if !defined(UBRR1H)
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
#endif

DFPlayerMini_Fast myMP3;

void setup()
{
    Serial.begin(115200);
#if !defined(UBRR1H)
    mySerial.begin(9600);
    myMP3.begin(mySerial, true);

#else
    Serial1.begin(9600);
    myMP3.begin(Serial1, true);
#endif

    myMP3.reset();
    Serial.println("setting volume");
    myMP3.volume(20);

    Serial.println("playing track 1");
    myMP3.play(1);
}

void loop()
{
    // do nothing
}