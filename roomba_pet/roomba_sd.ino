#if defined(SPARK_FUN_MP3)
#include <SPI.h>
#include <SdFat.h>
#include <vs1053_SdFat.h>

// Note: Uno will not support SD_FAT_TYPE = 3.
// SD_FAT_TYPE = 0 for SdFat/File as defined in SdFatConfig.h, 1 for FAT16/FAT32, 2 for exFAT, 3 for FAT16/FAT32 and exFAT.
#define SD_FAT_TYPE 1 // FAT16/FAT32

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

// #define FILE file_t
#define FILE File32
sd_t sd;

#else

#include <SD.h>     // required library: SD by Arduino, SparkFun

#define FILE File

#endif

void sdSetup()
{
#if defined(SPARK_FUN_MP3)
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

FILE sdOpen(char* filename)
{
#if defined(SPARK_FUN_MP3)
    return sd.open(filename);
#else
    return SD.open(F(filename));
#endif
}