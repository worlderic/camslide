// #####################################################################################################################
// ######################################### CAM SLIDE #################################################################
// #####################################################################################################################
/*
    DELOARTS RESEARCH INC.
    CAM SLIDE 2.0.0
	26.11.2016

	LICENSE

		This project is licensed under the GNU GPLv3 (https://www.gnu.org/licenses/gpl.html) open source license.
		Thus anybody is allowed to copy and modify the source code, provided all changes are open source too and the author is in knowledge of all changes.
		This can happen either via eMail or directly on GitHub, in other words, on this repository.
	
	DESCRIPTION

		English: http://deloarts.com/en/projects/camslide/
		German: http://deloarts.com/de/projects/camslide/
		Blog: http://deloarts.wordpress.com

	MICROCONTROLLER
		- Arduino Nano v3

	PINOUT

		Arduino |	Driver 		|	Display 	| 	Interface 	| 	Sensor 	| 	Controller 	| 	Camera
		  D0 	|	  			|				|				|			|				|	  
		  D1 	|	  			|				|				|			|				|	  
		  D2 	|	  Enable A 	|				|				|			|				|	  
		  D3 	|	  DIR A 	|				|				|			|				|	  
		  D4 	|	  STEP A	|				|				|			|				|	  
		  D5 	|	  Enable B	|				|				|			|				|	  
		  D6 	|	  DIR B		|				|				|			|				|	  
		  D7 	|	  STEP B	|				|				|			|				|	  
		  D8 	|	  			|				|				|	  S1	|				|	  
		  D9 	|	  			|				|				|			|	  A 		|	  
		  D10 	|	  			|				|				|			|	  B 		|	  
		  D11 	|	  			|				|				|			|	  			|	  Focus     
		  D12 	|	  			|				|				|			|	  			|	  Trigger
		  D13 	|	  			|				|				|			|	   			|	  
		  A0	|				|				|				|			|	  Z			|
		  A1 	|	  			|				|				|			|	  X			|	  
		  A2 	|	  			|				|				|			|	  Y 		|	  
		  A3	|	  			|				|				|			|				|	  
		  A4	|	  			|	  SDA		|	  SDA		|			|				|	  
		  A5	|	  			|	  SCL		|	  SCL		|			|				|	  
		  A6	|	  			|				|				|			|	  			|	  
		  A7	|	  			|				|				|			|	  			|	  

	EEPROM
		Fail				bit 	0
		Position			bit 	1, 2, 3, 4
		Slider length 		bit 	5, 6, 7, 8
		Controller min X 	int 	10, 11
		Controller max X 	int 	12, 13
		Controller min Y 	int 	14, 15
		Controller max Y 	int 	16, 17
*/	
#define D3BUG
#define MOTORTIME

#include <EEPROM.h>
#include <OLED_I2C_128x64_Monochrome.h>
#include <Wire.h>

// Define software
#define MOTOR_DELAY 250
#define MOTOR_MIN_DELAY	1200
#define MOTOR_MAX_DELAY	5000
#define MOTOR_ACCEL_STEP 100
#define MOTOR_DECEL_STEP 100

// Define hardware
#define DRV8825_A_ENBL 2
#define DRV8825_A_DIR 3
#define DRV8825_A_STEP 4
#define DRV8825_B_ENBL 5
#define DRV8825_B_DIR 6
#define DRV8825_B_STEP 7

#define Sensor 8

#define Controller_A 9
#define Controller_B 10
#define Controller_X A1
#define Controller_Y A2
#define Controller_Z A0

#define Camera_Focus 11
#define Camera_Trigger 12

// Better reading
#define zeroIsAllowed false
#define zeroNotAllowed true

// DEFINE EEPROM
#define EEPROM_fail	0x00
#define EEPROM_pos 1
#define EEPROM_length 5
#define EEPROM_MSB_ctrlMinX	0x0A
#define EEPROM_LSB_ctrlMinX	0x0B
#define EEPROM_MSB_ctrlMaxX	0x0C
#define EEPROM_LSB_ctrlMaxX	0x0D
#define EEPROM_MSB_ctrlMinY 0x0E
#define EEPROM_LSB_ctrlMinY	0x0F
#define EEPROM_MSB_ctrlMaxY 0x10
#define EEPROM_LSB_ctrlMaxY	0x11
#define EEPROM_MSB_transmission 0x12
#define EEPROM_LSB_transmission 0x13
#define EEPROM_mirrorLockup 0x14
#define EEPROM_autoFocus 0x15
#define EEPROM_motorLocked 0x16

struct inputData
{
	int X, Y, XMin, XMax, YMin, YMax;
	boolean A, B, Z;
} controller, controllerPrev;

struct menuData
{
	int index, maxIndex;
	boolean indexActive;
} mainMenu, photoMenu, manualMenu, settingsMenu, selector;

struct sliderData
{
	int length[4], position1, position2, runtime, totalSteps, absPos;
	float transmission;
	boolean zeroIsLeft;
} slider, sliderPrev, turner;

struct motorData
{
	boolean enabled, locked;
	int delay, maxDelay, minDelay;
} motor, step;

struct cameraData
{
	int amount[4], repeats[4], shutter[4], delay[4], speed;
	float travelDistance, distancePerShot;
	boolean mirrorLockup, autoFocus;
} camera;

void setup()
{
	#ifdef D3BUG
	Serial.begin(9600);
	Serial.println("D3BUG MODE");
	#endif
	#ifdef MOTORTIME
	
	#endif
	boot();
}

void loop()
{
	getControllerData(true); // true for the calibration
	if (setMenu()) printMenu();
}