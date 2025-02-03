#if defined(SPARK_FUN_MP3)
#define ENABLE_DEDICATED_SPI 0

vs1053 MP3player;

#else

#include <SD.h>     // required library: SD by Arduino, SparkFun
#include <TMRpcm.h> // required library: TMRpcm by TMRh20

TMRpcm tmrpcm; // define wav file player library
#endif

void audioSetup()
{
#if defined(SPARK_FUN_MP3)
    MP3player.begin();
    MP3player.setVolume(10, 10);
#else
    tmrpcm.speakerPin = 9; // setup speaker and SD wav reader

    tmrpcm.setVolume(4); // set the volume
    digitalWrite(tmrpcm.speakerPin, LOW);
#endif
}

void audioPlay(char *soundFile)
{
#if defined(SPARK_FUN_MP3)
    int8_t result = MP3player.playMP3(soundFile);
    // check result, see readme for error codes.
    if (result != 0)
    {
        Serial.print(F("Error code: "));
        Serial.print(result);
        Serial.println(F(" when trying to play track"));
    }
#else
    // This functions reads the soundFile and plays it
    //  Just be sure there to switch off what was playing before
    digitalWrite(tmrpcm.speakerPin, LOW);
    tmrpcm.disable();
    delay(200);
    tmrpcm.play(soundFile);
    delay(300);
    tmrpcm.loop(0);
#endif
}

void audioLoop()
{
#if defined(SPARK_FUN_MP3)
    // Below is only needed if not interrupt driven. Safe to remove if not using.
    #if defined(USE_MP3_REFILL_MEANS) && ( (USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer) ||   (USE_MP3_REFILL_MEANS == USE_MP3_Polled))
    MP3player.available();
    #endif
#else
#endif
}

bool audioIsPlaying()
{
#if defined(SPARK_FUN_MP3)
    return MP3player.isPlaying();
#else
    return tmrpcm.isPlaying();
#endif
}

bool audioStop()
{
#if defined(SPARK_FUN_MP3)
    MP3player.stopTrack();
#else
    digitalWrite(tmrpcm.speakerPin, LOW);
    delay(100);
#endif
}
