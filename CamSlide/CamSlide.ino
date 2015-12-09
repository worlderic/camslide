// #####################################################################################################################
// ######################################### CAM SLIDE #################################################################
// #####################################################################################################################
/*
    DELOARTS RESEARCH INC.
    CAM SLIDE 1.0.1
	02.11.2015
	
	DESCRIPTION

		CamSlide is an Arduino based embedded system to slide a camera sideways on a guide rail for time-lapse shots.
		There are several settings, which are set via a display and a 4-button user interface.

		This project was compiled with the Arduino IDE 1.6.6

	MICROCONTROLLER
		- Arduino UNO Rev3
		- Arduino Nano v3

		There is no need to change the pin occupancy, when the UNO is replaced with the Nano, and vice versa.
		Just be careful, that you change the board in the settings!
*/
// #####################################################################################################################
// ######################################### VARIABLES #################################################################
// #####################################################################################################################
// DEFINE CODE SETTINGs
//#define TEST_RUN
// GET MODULES
#include <EEPROM.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <OLED_I2C_128x64_Monochrome.h>
#include <Wire.h>
// DEFINE PINS
// INPUT
#define Input_Sensor_Left    		2
#define Input_Sensor_Right   		3
// INPUTS (User Interface)
#define Input_Button_OK     		4
#define Input_Button_Cancel 		5
#define Input_Button_Up     		6 
#define Input_Button_Down   		7
// OUTPUTS
#define Output_Relais_Right  	 	9
#define Output_Relais_Left   		10
#define Output_Focus         		11
#define Output_Camera   	    	12
// DEFINE VARIABLES 	
// CONSTANTS
const byte Pulley_Diameter      	= 10;
const byte Engine_RPM           	= 10;
const long Maximum_Lenght       	= 1300;
// MATHEMATICS
const float Math_Pi	  		    	= 3.14159265359;
// STARTUP MANAGEMENT
boolean Startup_Done        		= false;
// INPUT MANAGEMENT
boolean Input_Array[4]      		= {0,0,0,0};
boolean Current_Auto_Focus  		= false;
boolean Current_Mirror_Lockup 		= false;
// OUTPUT MANAGEMENT
boolean System_Is_Working   		= false;
boolean Slide_On_Track      		= true;
// MENU MANAGEMENT
boolean Main_Menu					= true;
int Page 							= 0;
int Register						= 0;
byte Number_Index          	 		= 0;
byte Way_Array[4]          	 		= {0,0,0,0};
byte Way_Delay[4]					= {0,0,0,0};
byte Delay_Array[6]					= {0,0,0,0,0,0};
byte Repeats_Array[5]       		= {0,0,0,0,0};
byte Shutter_Speed_Array[4] 		= {0,0,0,0};
boolean Show_Way_Delay      		= false;
// #####################################################################################################################  
// ######################################### SETUP #####################################################################
// #####################################################################################################################
void setup()
{
	attachInterrupt(0, interruptHandlerLeft,  RISING);
	attachInterrupt(1, interruptHandlerRight, RISING);
	startup();
	menuManagement();
}
// #####################################################################################################################
// ######################################### LOOP ######################################################################
// #####################################################################################################################
void loop()
{
	inputManagement();
}
// #####################################################################################################################  
// ######################################### END OF CODE ###############################################################
// #####################################################################################################################