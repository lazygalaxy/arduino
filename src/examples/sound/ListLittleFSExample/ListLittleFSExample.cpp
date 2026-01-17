#include <Arduino.h>
#include <LittleFS.h>

#include "AudioFileSourceLittleFS.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"

AudioGeneratorWAV *wav = nullptr;
AudioFileSourceLittleFS *file = nullptr;
AudioOutputI2S *out = nullptr;

void listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
  Serial.printf("Listing: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root)
  {
    Serial.println("Failed to open dir");
    return;
  }
  if (!root.isDirectory())
  {
    Serial.println("Not a dir");
    return;
  }

  File file = root.openNextFile();
  while (file)
  {
    if (file.isDirectory())
    {
      Serial.printf("  DIR : %s\n", file.name());
      if (levels)
        listDir(fs, file.name(), levels - 1);
    }
    else
    {
      Serial.printf("  FILE: %s  SIZE: %u\n", file.name(), (unsigned)file.size());
    }
    file = root.openNextFile();
  }
}

void setup()
{
  Serial.begin(115200);
  delay(500);

  Serial.println("\nMounting LittleFS...");
  if (!LittleFS.begin(true))
  {
    Serial.println("LittleFS mount FAILED");
    while (true)
      delay(1000);
  }
  Serial.println("LittleFS mounted OK");

  // List root
  listDir(LittleFS, "/", 2);

  // Try opening your expected file
  const char *path = "/a2.wav";
  File f = LittleFS.open(path, "r");
  if (!f)
  {
    Serial.printf("ERROR: Cannot open %s\n", path);
  }
  else
  {
    Serial.printf("OK: Opened %s (%u bytes)\n", path, (unsigned)f.size());
    // Read first few bytes to prove it's real data
    uint8_t hdr[16];
    int n = f.read(hdr, sizeof(hdr));
    Serial.printf("Read %d bytes. First 16 bytes (hex): ", n);
    for (int i = 0; i < n; i++)
      Serial.printf("%02X ", hdr[i]);
    Serial.println();
    f.close();

    Serial.println("Opening WAV...");
    file = new AudioFileSourceLittleFS("/a2.wav");
    if (!file->isOpen())
    {
      Serial.println("ERROR: /sound.wav not found or failed to open");
      while (true)
        delay(1000);
    }

    Serial.println("Starting output (INTERNAL_DAC)...");
    out = new AudioOutputI2S(0, AudioOutputI2S::INTERNAL_DAC);
    out->SetGain(0.3); // keep low for PAM8403

    wav = new AudioGeneratorWAV();
    wav->begin(file, out);

    Serial.println("Playing.");
  }
}

void loop()
{
  if (wav && wav->isRunning())
  {
    if (!wav->loop())
    {
      wav->stop();
      Serial.println("Playback finished.");
    }
  }
}
