#include "config.h"

#if defined(ADAFRUIT_MP3)

#elif defined(SPARK_FUN_MP3)
sd_t sd;

#elif defined(TMR_PCM)
#endif

void sdSetup()
{
#if defined(ADAFRUIT_MP3)
    if (!SD.begin(CARDCS)) {
        Serial.println(F("SD failed, or not present"));
        while (1);  // don't do anything more
    }
#elif defined(SPARK_FUN_MP3)
  if(!sd.begin(9, SPI_HALF_SPEED)) sd.initErrorHalt();
  if (!sd.chdir("/")) sd.errorHalt("sd.chdir");
#else
    if (!SD.begin(10))
    {
        Serial.println(F("SD fail"));
        return;
    }
#endif
}

file_t sdOpen(const char* filename)
{
#if defined(SPARK_FUN_MP3)
    return sd.open(filename);
#else
    return SD.open(filename);
#endif
}