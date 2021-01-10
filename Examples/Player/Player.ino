/*
  Audio player, non blocking.
  read 8bit mono .wav file, up to 4 channels
  use Audacity to convert your audio file

  Author : AloyseTech
  Modified: BriscoeTech
*/


#include <SamdAudio.h>
#include <SdFat.h>
#include <SPI.h>

SamdAudio AudioPlayer;
SdFat sdCard(&SPI); //the sd card object to use for all our file access

#define NUM_AUDIO_CHANNELS 4 //could be 1,2 or 4 for sound

// which Serial you prefer, for information.
//#define SERIAL SerialUSB
#define SERIAL Serial

// SD chip select pin (with ethernet shield : 4)
#define YOUR_SD_CS 			4//10
#define SPI_CLOCK_SPEED		12 //mhz //max samd21 spi speed

//indicate sample rate here (use audacity to convert your wav)
const unsigned int sampleRate = 22050;

bool state = true;
uint32_t timer = 0;
uint32_t updatetimer = 0;

//************************************************************************

void setup()
{

	// debug output at 115200 baud
	SERIAL.begin(115200);
	while (!SERIAL);


	bool sdGood = sdCard.begin(YOUR_SD_CS, SD_SCK_MHZ(SPI_CLOCK_SPEED));
	while ( !sdGood ) //this command blocks if there is no sd card inserted
	{
		SERIAL.println(F("Unable To read SD card"));
		delay(1000);

		sdGood = sdCard.begin(YOUR_SD_CS, SD_SCK_MHZ(SPI_CLOCK_SPEED));
	}
	SERIAL.println(F("SD Ready"));


	// setup SD-card
	SERIAL.print("Initializing SD card...");
	if (AudioPlayer.begin(sampleRate, NUM_AUDIO_CHANNELS, &sdCard) == -1)
	{
		SERIAL.println(" failed!");
		return;
	}
	SERIAL.println(" done.");


	AudioPlayer.play("R2D2.wav", 0);
	SERIAL.println("Playing file.....");
}

void loop()
{

	if (SERIAL.available())
	{
		char c = SERIAL.read();

		if ( c == 'q')
		{
		  AudioPlayer.play("LaserFire1.wav", 0);
		}
		else if ( c == 'w')
		{
		  AudioPlayer.play("LaserFire1.wav", 1);
		}
		else if ( c == 'e')
		{
		  AudioPlayer.play("LaserFire2.wav", 2);
		}
		else if ( c == 'r')
		{
		  AudioPlayer.play("LaserFire2.wav", 3);
		}
		else if ( c == 't')
		{
		  AudioPlayer.play("R2D2.wav", 3);
		}

		else if ( c == '1')
		{
		  AudioPlayer.stopChannel(0);
		  SERIAL.println("ch0 off!");
		}
		else if ( c == '2')
		{
		  AudioPlayer.stopChannel(1);
		  SERIAL.println("ch1 off!");
		}
		else if ( c == '3')
		{
		  AudioPlayer.stopChannel(2);
		  SERIAL.println("ch2 off!");
		}
		else if ( c == '4')
		{
		  AudioPlayer.stopChannel(3);
		  SERIAL.println("ch3 off!");
		}
	}

}
