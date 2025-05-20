#include "config.h"

#if defined(ADAFRUIT_MP3)
#include <Adafruit_VS1053.h>

Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS); // create breakout-example object!

#elif defined(SPARK_FUN_MP3)
vs1053 MP3player;

#elif defined(TMR_PCM)
#include <SD.h>     // required library: SD by Arduino, SparkFun
#include <TMRpcm.h> // required library: TMRpcm by TMRh20

TMRpcm tmrpcm; // define wav file player library
#endif

void audioSetup()
{
#if defined(ADAFRUIT_MP3)
    if (! musicPlayer.begin()) { // initialise the music player
        Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
        while (1);
    }
    Serial.println(F("VS1053 found"));

    musicPlayer.setVolume(20,20);

    // Timer interrupts are not suggested, better to use DREQ interrupt!
    //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

    // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background audio playing
    musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);

    Serial.println(F("playing test audio file..."));
    musicPlayer.startPlayingFile("track002.mp3");
    Serial.println(F("...done"));
#elif defined(SPARK_FUN_MP3)
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
#if defined(ADAFRUIT_MP3)
    Serial.print(F("audioPlay: "));
    Serial.println(soundFile);

    // Play another file in the background, REQUIRES interrupts!
    musicPlayer.startPlayingFile(soundFile);

    // Synchronous variant
    // musicPlayer.playFullFile(soundFile);

#elif defined(SPARK_FUN_MP3)
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
#if defined(ADAFRUIT_MP3)
#elif defined(SPARK_FUN_MP3)
    // Below is only needed if not interrupt driven. Safe to remove if not using.
    #if defined(USE_MP3_REFILL_MEANS) && ( (USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer) ||   (USE_MP3_REFILL_MEANS == USE_MP3_Polled))
    MP3player.available();
    #endif
#else
#endif
}

bool audioIsPlaying()
{
#if defined(ADAFRUIT_MP3)
    return musicPlayer.playingMusic;
#elif defined(SPARK_FUN_MP3)
    return MP3player.isPlaying();
#else
    return tmrpcm.isPlaying();
#endif
}

bool audioStop()
{
#if defined(ADAFRUIT_MP3)
    musicPlayer.stopPlaying(); // stop playing the file
#elif defined(SPARK_FUN_MP3)
    MP3player.stopTrack();
#else
    digitalWrite(tmrpcm.speakerPin, LOW);
    delay(100);
#endif
}
