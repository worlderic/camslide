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
		  D2 	|	  Enable 	|				|				|			|				|	  
		  D3 	|	  DIR 		|				|				|			|				|	  
		  D4 	|	  STEP 		|				|				|			|				|	  
		  D5 	|	  M0 		|				|				|			|				|	  
		  D6 	|	  M1 		|				|				|			|				|	  
		  D7 	|	  M2 		|				|				|			|				|	  
		  D8 	|	  			|				|				|	  S1	|				|	  
		  D9 	|	  			|				|				|			|	  S2		|	  
		  D10 	|	  			|				|				|			|	  S3		|	  
		  D11 	|	  			|				|				|			|	  S4		|	  
		  D12 	|	  			|				|				|			|				|	  Focus	  
		  D13 	|	  			|				|				|			|				|	  Trigger
		  A1 	|	  			|				|				|			|				|	  
		  A2 	|	  			|				|				|			|				|	  
		  A3	|	  			|				|				|			|				|	  
		  A4	|	  			|	  SDA		|	  SDA		|			|				|	  
		  A5	|	  			|	  SCL		|	  SCL		|			|				|	  
		  A6	|	  			|				|				|			|	  X			|	  
		  A7	|	  			|				|				|			|	  Y			|	  

	EEPROM
		- 0: Calibrated X-axis minimum
		- 1: Calibrated X-axis maximum
		- 2: Calibrated Y-axis minimum
		- 3: Calibrated Y-axis maximum

*/	
// #####################################################################################################################
// ######################################### VARIABLES #################################################################
// #####################################################################################################################
#define D3BUG

#include <EEPROM.h>
#include <OLED_I2C_128x64_Monochrome.h>
#include <Wire.h>

#define DRV8825_ENBL	2
#define DRV8825_DIR		3
#define DRV8825_STEP	4
#define DRV8825_M0		5
#define DRV8825_M1		6
#define DRV8825_M2		7

#define Sensor 			8

#define Controller_A	9
#define Controller_B	10
#define Controller_X	A6
#define Controller_Y	A7
#define Controller_Z	11

#define Camera_Focus	12
#define Camera_Trigger	13

struct inputData
{
	int X, Y, XMin, XMax, YMin, YMax;
	boolean A, B, Z;
} controller;
// #####################################################################################################################  
// ######################################### SETUP #####################################################################
// #####################################################################################################################
void setup()
{
	#ifdef D3BUG
	Serial.begin(9600);
	#endif
	boot();
}
// #####################################################################################################################
// ######################################### LOOP ######################################################################
// #####################################################################################################################
void loop()
{
	getControllerData(true); // true for the calibration
}
// #####################################################################################################################  
// ######################################### END OF CODE ###############################################################
// #####################################################################################################################