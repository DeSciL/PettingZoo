#ifndef CONFIG_H
#define CONFIG_H

#define ADAFRUIT_MP3 true
//#define SPARK_FUN_MP3 true
//#define TMR_PCM true

#if defined(ADAFRUIT_MP3)
#include <SPI.h>
#include <SD.h>

#define BREAKOUT_RESET  8 // RST, VS1053 reset pin (output)
#define BREAKOUT_CS     3 // CS, VS1053 chip select pin (output)
#define BREAKOUT_DCS    4 // XDCS, VS1053 Data/command select pin (output)

#define DREQ 2            // DREQ, VS1053 Data request, ideally an Interrupt pin, see http://arduino.cc/en/Reference/attachInterrupt

#define CARDCS 9     // SDCS, Card chip select pin

typedef File file_t;

#elif defined(SPARK_FUN_MP3)

// Note: Uno will not support SD_FAT_TYPE = 3.
// SD_FAT_TYPE = 0 for SdFat/File as defined in SdFatConfig.h, 1 for FAT16/FAT32, 2 for exFAT, 3 for FAT16/FAT32 and exFAT.
// #define SD_FAT_TYPE 1 // FAT16/FAT32 //TODO: fails, "sd_t sd" needs to match with "SdFat sd" in vs1053_SdFat.h???
#define SD_FAT_TYPE 0

#include <SPI.h>
#include <vs1053_SdFat.h>

#define ENABLE_DEDICATED_SPI 0

//TODO: already in vs1053_SdFat.h?
#if SD_FAT_TYPE == 0
typedef SdFat sd_t;
typedef File file_t;
#elif SD_FAT_TYPE == 1
typedef SdFat32 sd_t;
typedef File32 file_t;
#elif SD_FAT_TYPE == 2
typedef SdExFat sd_t;
typedef ExFile file_t;
#elif SD_FAT_TYPE == 3
typedef SdFs sd_t;
typedef FsFile file_t;
#else  // SD_FAT_TYPE
#error Invalid SD_FAT_TYPE
#endif  // SD_FAT_TYPE

#elif defined(TMR_PCM)

#include <SD.h>     // required library: SD by Arduino, SparkFun

//#define FILE File
typedef File file_t;

#endif

#endif  // CONFIG_H