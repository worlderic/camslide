// #####################################################################################################################
// ######################################### CAM SLIDE #################################################################
// #####################################################################################################################
/*
    DELOARTS RESEARCH INC.
    CAM SLIDE 2.0.0
	26.11.2016
	
	DESCRIPTION

		CamSlide is an Arduino based embedded system to slide a camera sideways on a guide rail for time-lapse shots.
		This project was compiled with the Arduino IDE 1.6.6

	MICROCONTROLLER
		- Arduino UNO Rev3
		- Arduino Nano v3

		There is no need to change the pin occupancy, when the UNO is replaced with the Nano, and vice versa.
		Just be careful, that you change the board in the settings!

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
		  D11 	|	  			|				|				|			|	    		|	  Focus
		  D12 	|	  			|				|				|			|				|	  Trigger
		  D13 	|	  			|				|				|			|	  Z			|	  
		  A0	|				|				|				|			|	  X			|
		  A1 	|	  			|				|				|			|	  Y			|	  
		  A2 	|	  			|				|				|			|				|	  
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

// Define hardware
#define DRV8825_A_ENBL	2
#define DRV8825_A_DIR	3
#define DRV8825_A_STEP	4
#define DRV8825_B_ENBL	5
#define DRV8825_B_DIR	6
#define DRV8825_B_STEP	7

#define Sensor 			8

#define Controller_A	9
#define Controller_B	10
#define Controller_X	A0
#define Controller_Y	A1
#define Controller_Z	13

#define Camera_Focus	11
#define Camera_Trigger	12

// Better reading
#define zeroIsAllowed	false
#define zeroNotAllowed	true

// DEFINE EEPROM
#define EEPROM_fail				0x00
#define EEPROM_pos 				1
#define EEPROM_length 			5
#define EEPROM_MSB_ctrlMinX		0x0A
#define EEPROM_LSB_ctrlMinX		0x0B
#define EEPROM_MSB_ctrlMaxX		0x0C
#define EEPROM_LSB_ctrlMaxX		0x0D
#define EEPROM_MSB_ctrlMinY 	0x0E
#define EEPROM_LSB_ctrlMinY		0x0F
#define EEPROM_MSB_ctrlMaxY 	0x10
#define EEPROM_LSB_ctrlMaxY		0x11

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
	boolean enabled;
	int delay, maxDelay, minDelay;
} motor, step;

struct cameraData
{
	int amount[4], repeats[4], shutter[4], delay[4];
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