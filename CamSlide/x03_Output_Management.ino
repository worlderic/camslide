// ##################################################################################################################### 
// ######################################### OUTPUT MANAGEMENT #########################################################
// #####################################################################################################################
void outputManagement()
{
	// DISABLE DISPLAY
	setDisplay(false);
	// CREATE NECCESARY VARIABLES
	long Current_Repeats = 0;
	long Counter = 0;
	// GET WAY DELAY
	long Way_Millimeter = Way_Array[0] * 1000 + Way_Array[1] * 100 + Way_Array[2] * 10 + Way_Array[3];
	long Way_Delay_Milliseconds = 1000 * (60 * Way_Millimeter) / ((Pulley_Diameter * Math_Pi) * Engine_RPM);
	// GET USER DELAY
	long Delay_Milliseconds = 1000 * (Delay_Array[0] * 36000 + Delay_Array[1] * 3600 + Delay_Array[2] * 600 + Delay_Array[3] * 60 + Delay_Array[4] * 10 + Delay_Array[5]);
	// GET REPEATS
	long Repeats = Repeats_Array[0] * 1000 + Repeats_Array[1] * 100 + Repeats_Array[2] * 10 + Repeats_Array[3];
	// GET SHUTTER SPEED
	long Shutter_Speed_Milliseconds = 1000 * (Shutter_Speed_Array[0] * 600 + Shutter_Speed_Array[1] * 60 + Shutter_Speed_Array[2] * 10 + Shutter_Speed_Array[3]);
	// CALCULATE TOTAL DELAY
	long Total_Delay_Milliseconds = Way_Delay_Milliseconds + Delay_Milliseconds;
	// SET SHUTTER SPEED IN CASE IT IS ZERO
	Shutter_Speed_Milliseconds < 1000 ? Shutter_Speed_Milliseconds = 1000 : Shutter_Speed_Milliseconds = Shutter_Speed_Milliseconds;
	/*
		Every time spawn under 1 second is too short for CamSlide, therefore the camera HAS TO process it by itself !
		Every time spawn under 30 seconds is processed by the camera itself !
	*/
	// START PROCESS
	System_Is_Working = true;
	Slide_On_Track = true;
	// VARY WORKING STATE DEPENDING ON AMOUNT OF REAPEATS
	if (Repeats > 0)
	{
		while (Current_Repeats < Repeats && System_Is_Working)
		{
			// FIRST: SET AUTO-FOCUS & MIRROR LOCKUP
			if (Current_Auto_Focus)
			{
				digitalWrite(Output_Focus, HIGH);
				delay(1000);
			}
			if (Current_Mirror_Lockup)
			{
				digitalWrite(Output_Camera, HIGH);
				delay(500);
				digitalWrite(Output_Camera, LOW);
				delay(1500);
			}
			// SECOND: TRIGGER CAMERA (DEPENDING ON REPEATS)
			for (byte X = 0; X < Repeats_Array[4]; X++)
			{
				digitalWrite(Output_Camera, HIGH);
				digitalWrite(Output_Focus, LOW);
				Shutter_Speed_Milliseconds < 30000 ? delay(500) : delay(Shutter_Speed_Milliseconds);
				digitalWrite(Output_Camera, LOW);
				Shutter_Speed_Milliseconds < 30000 ? delay(Shutter_Speed_Milliseconds) : delay(500);
				// DELAY, IF MORE THAN ONE SHOT - CAMERA PROCESSING TIME
				Repeats_Array[4] > 1 && X + 1 < Repeats_Array[4] ? delay(Total_Delay_Milliseconds) : delay(0);
			}
			// THIRD: SET MOTOR AND WAIT DELAY TIME (EXCEPT THE LAST ROUND)
			if (Current_Repeats + 1 < Repeats)
			{
				digitalWrite(Output_Relais_Right, LOW);
				while (Counter < Way_Delay_Milliseconds && System_Is_Working)
				{
					delayMicroseconds(900);
					Counter++;
				}
				digitalWrite(Output_Relais_Right, HIGH);
				// WAIT THE USER DELAY (Do not wait, if an interrupt happened!)
				if (System_Is_Working)
					delay(Delay_Milliseconds);
			}
			// FOURTH: INCREASE REPEATS, RESET COUNTER
			Current_Repeats++;
			Counter = 0;
		}
	}
	// REPEATS = 0 -> GO TO THE END!
	else
	{
		digitalWrite(Output_Relais_Right, LOW);
		while (System_Is_Working)
		{
			// DO NOTHING, INTERRUPT WILL HANDLE IT
		}
	}
	// END WORKING
	System_Is_Working = false;
	// GO TO ZERO POSITION
	setSlideToZero();
	// RESTORE MENU
	restoreMenu();
	// ENABLE DISPLAY
	setDisplay(true);
}
// #####################################################################################################################
// ######################################### SLIDE TO ZERO #############################################################
// #####################################################################################################################
void setSlideToZero()
{
	#ifndef TEST_RUN
	// SET SLIDE TO ZERO POSITION
	digitalWrite(Output_Relais_Left, LOW);
	#endif
}
// #####################################################################################################################  
// ######################################### END OF CODE ###############################################################
// #####################################################################################################################