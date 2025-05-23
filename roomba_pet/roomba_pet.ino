//* This file is the main file that sets up the Roomba, SD-card, speaker
//* It then loops through Roomba battery check and roomba sensor to implement the pet behaviour
//* on bump as long as there is enough battery.

#include <SoftwareSerial.h>
#include <SPI.h>
#include <avr/pgmspace.h>

#include "config.h"

#define DEBUG false

#if defined(ADAFRUIT_MP3)
// Avoid writing debug output to pins used for the audio breakout board: Breaks audio output and causes clicking noise.
int bumpPin = 0;
int ledPin = 1;
#else
int bumpPin = 4;
int ledPin = 8;
#endif

#if defined(SPARK_FUN_MP3)
int roombaRxPin = 0;
int roombaTxPin = 1; // for SparkFun MP3 shield (DEV-12660)
#else
int roombaRxPin = 6;
int roombaTxPin = 7; // default
#endif

uint8_t personality = 1; // The Personlity selector
uint8_t interval = 100;
uint8_t batteryLowCounter = 0; // Counts how many consequent times the battery gave low indication or was on charge
char soundFile[13];            // space reserved for sound file

SoftwareSerial Roomba(roombaRxPin, roombaTxPin); // define the connection to roomba
void doStartMove();
void updateSensor();
bool checkLowBattery();
void readSDSettings();

void setup()
{
    // uint8_t audioSpeakerPin = 9;
    // uint8_t sdChipSelectPin = 10;
    pinMode(ledPin, OUTPUT);  // sets the pins as output
    pinMode(bumpPin, OUTPUT); // sets the pins as output

    // Set the serial output line
    Serial.begin(115200);
    sdSetup();
    
    // read setting
    readSDSettings();
    digitalWrite(bumpPin, LOW); // reset
    digitalWrite(ledPin, LOW);  // reset

    audioSetup();

    // start roomba initialisation
    Roomba.begin(115200);
    digitalWrite(ledPin, HIGH); // say roomba's alive
    Serial.println(F("Sending start command..."));
    delay(1000);
    // set up ROI to receive commands
    Roomba.write(128); // START
    delay(150);
    Serial.println(F("Sending Safe Mode command..."));
    delay(1000);
    Roomba.write(131); // SAFE MODE
    delay(150);
    delay(5000);
    digitalWrite(ledPin, LOW); // say we've finished setup
    doStartMove();             // Do start moves as a visual let's go indicator
    Serial.println(F("Ready to go!"));
    if (!DEBUG)
    {
        Roomba.write(135);
    } // CLEAN MODE

    delay(500);
}

// declared reset function at address 0
void (*resetFunc)(void) = 0;

void loop()
{
    audioLoop();

#if defined(TMR_PCM)
    // Not required for audio boards
    if (!audioIsPlaying())
    {
        audioStop();
    }
#endif

    if (interval > 0)
    {
        // not time for battery check yet
        Serial.println(F("Sensor..."));
        digitalWrite(ledPin, HIGH); // say we're are doing sensing
        updateSensor();             // Do bumper sensor activity
        digitalWrite(ledPin, LOW);  // say finished sensing
        delay(150);
        interval--;
    }
    else
    {
        // time for a battery check
        Serial.println(F("battery check..."));
        // Setup next check interval
        interval = uint8_t(100); // next check in 100 sensing
        if (!checkLowBattery())
        {
            // battery indicated not low
            Serial.println(F("battery fine..."));
            digitalWrite(ledPin, HIGH); // waiting to dock
            delay(2000);
            digitalWrite(ledPin, LOW);
            delay(500);
            // So battery was not low, reset consequtive battery low counter
            batteryLowCounter = uint8_t(0);
        }
        else
        {
            // battery was low on this reading
            if (batteryLowCounter < 1)
            {
                // sometimes the battery sensor gives a wrong reading when packets
                // are missed or not in correct position or some other issue not documented
                // when an all high is received. So we will read twice to check
                Serial.println(F("Check again"));
                batteryLowCounter = uint8_t(batteryLowCounter + 1);
            }
            else
            {
                // Battery must be low 2 or more continuous low readings
                Serial.println(F("time up..."));
                digitalWrite(ledPin, HIGH); // waiting to dock
                // Trying to force seek dock. Does not seem to work.
                Roomba.write(143);
                // Roomba.write(165); Roomba.write((byte)4);
                delay(6000);               // give it a minute to try to dock
                digitalWrite(ledPin, LOW); // had enough pause
                delay(150);
                while (true)
                {
                } // Stop program
            }
        }
    }
}
