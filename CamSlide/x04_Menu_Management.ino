// #####################################################################################################################  
// ######################################### MENU MANAGEMENT ###########################################################
// #####################################################################################################################
void menuManagement()
{
	// CLEAR ALL VALUES & GO TO FIRST POSITION
	if (Input_Array[1])
	{
		for (byte X = 0; X < 4; X++)
			Way_Array[X] = 0;
		for (byte X = 0; X < 6; X++)
			Delay_Array[X] = 0;
			Delay_Array[5] = 1;
		for (byte X = 0; X < 4; X++)
			Repeats_Array[X] = 0;
			Repeats_Array[4] = 1;
		for (byte X = 0; X < 4; X++)
			Shutter_Speed_Array[X] = 0;
		restoreMenu();
		Register = 0;
	}
	// SET REGISTER
	if (Input_Array[2])
	{
		Register--;
		Register < 0 ? Register = 6 : Register = Register;
		switchPage();
	}
	else if (Input_Array[3])
	{
		Register++;
		Register > 6 ? Register = 0 : Register = Register;
		switchPage();
	}
	// SWITCH REGISTER
	switch (Register)
	{
    	// --------------------------------- START WORKING -------------------------------------------------------------
		case 0:
			Input_Array[0] && !Slide_On_Track ? outputManagement() : printSelectedItem(2);
			break;
		// --------------------------------- SET WAY -------------------------------------------------------------------
		case 1:
			Input_Array[0] ? prepareSubMenu(Register) : printSelectedItem(4);
			break;
		// --------------------------------- SET DELAY -----------------------------------------------------------------
		case 2:
			Input_Array[0] ? prepareSubMenu(Register) : printSelectedItem(5);
			break;
		// --------------------------------- SET REPEATS ---------------------------------------------------------------
		case 3:
			Input_Array[0] ? prepareSubMenu(Register) : printSelectedItem(6);
			break;
		// --------------------------------- SET SHUTTER SPEED ---------------------------------------------------------
		case 4:
			Input_Array[0] ? prepareSubMenu(Register) : printSelectedItem(7);
			break;
		// --------------------------------- AUTO FOCUS ----------------------------------------------------------------
		case 5:
			Input_Array[0] ? processCameraSettings(Register) : printSelectedItem(4);
			break;
		// --------------------------------- MIRROR LOCKUP -------------------------------------------------------------
		case 6:
			Input_Array[0] ? processCameraSettings(Register) : printSelectedItem(5);
			break;
	}
	// PRINT THE WAY, IF SELECTED
	if (Main_Menu && Register == 1)
	{
		Show_Way_Delay = true;
		printMenu();
	}
	else if (Main_Menu && Register != 1)
	{
		Show_Way_Delay = false;
		printMenu();
	}
}
// #####################################################################################################################  
// ######################################### MENU MANAGEMENT (NUMBERS) #################################################
// #####################################################################################################################
void menuManagement(byte Parameter_Type)
{
	// SWITCH MENU DEPENDING ON TYPE
	switch (Parameter_Type)
	{
		// --------------------------------- SET WAY -------------------------------------------------------------------
		case 1: 
			if (Input_Array[0])
			{
				Number_Index++;
				// RETURN, IF EVERY NUMBER HAS BEEN CHANGED, OR THE MAXIMUM HAS BEEN REACHED
				if (Number_Index > 3)
				{
					// GO BACK TO MAIN MENU
					restoreMenu();
					return;
				}
			}
			else if (Input_Array[1])
			{
				Number_Index == 0 ? Number_Index = 0 : Number_Index--;
			}
			else if (Input_Array[2])
			{
				// The number can be any value from 0 to 9.
				Way_Array[Number_Index] == 9 ? Way_Array[Number_Index] = 0 : Way_Array[Number_Index]++;
				// Except, if the first number is 1, because the maximum range is 1000mm.
				Number_Index == 0 && Way_Array[0] > 1 ? Way_Array[0] = 0 : Way_Array[0] = Way_Array[0];
				if (Way_Array[0] > 0)
					for (byte X = 1; X < 4; X++)
						Way_Array[X] = 0;
			}
			else if (Input_Array[3])
			{
				// The number can be any value from 0 to 9.
				Way_Array[Number_Index] == 0 ? Way_Array[Number_Index] = 9 : Way_Array[Number_Index]--;
				// Except, if the first number is 1, because the maximum range is 1000mm.
				Number_Index == 0 && Way_Array[0] > 1 ? Way_Array[0] = 1 : Way_Array[0] = Way_Array[0];
				if (Way_Array[0] > 0)
					for (byte X = 1; X < 4; X++)
						Way_Array[X] = 0;
			}
			break;
		// --------------------------------- SET DELAY -----------------------------------------------------------------
		case 2:
			if (Input_Array[0])
			{
				Number_Index++;
				// RETURN, IF EVERY NUMBER HAS BEEN CHANGED
				if (Number_Index > 5)
				{
					// GO BACK TO MAIN MENU
					restoreMenu();
					return;
				}
			}
			else if (Input_Array[1])
			{
				Number_Index == 0 ? Number_Index = 0 : Number_Index--;
			}
			else if (Input_Array[2])
			{
				Delay_Array[Number_Index] == 9 ? Delay_Array[Number_Index] = 0 : Delay_Array[Number_Index]++;
				Delay_Array[2] > 5 ? Delay_Array[2] = 0 : Delay_Array[2] = Delay_Array[2];
				Delay_Array[4] > 5 ? Delay_Array[4] = 0 : Delay_Array[4] = Delay_Array[4];
				Delay_Array[5] == 0 && Delay_Array[4] == 0 && Delay_Array[3] == 0 && Delay_Array[2] == 0 && Delay_Array[1] == 0 && Delay_Array[0] == 0 ? Delay_Array[5] = 1 : Delay_Array[5] = Delay_Array[5];
			}
			else if (Input_Array[3])
			{
				Delay_Array[Number_Index] == 0 ? Delay_Array[Number_Index] = 9 : Delay_Array[Number_Index]--;
				Delay_Array[2] > 5 ? Delay_Array[2] = 5 : Delay_Array[2] = Delay_Array[2];
				Delay_Array[4] > 5 ? Delay_Array[4] = 5 : Delay_Array[4] = Delay_Array[4];
				Delay_Array[5] == 0 && Delay_Array[4] == 0 && Delay_Array[3] == 0 && Delay_Array[2] == 0 && Delay_Array[1] == 0 && Delay_Array[0] == 0 ? Delay_Array[5] = 9 : Delay_Array[5] = Delay_Array[5];
			}
			break;
		// --------------------------------- SET REPEATS ---------------------------------------------------------------
		case 3:
			if (Input_Array[0])
			{
				Number_Index++;
				// RETURN, IF EVERY NUMBER HAS BEEN CHANGED
				if (Number_Index > 4)
				{
					// GO BACK TO MAIN MENU
					restoreMenu();
					return;
				}
			}
			else if (Input_Array[1])
			{
				Number_Index == 0 ? Number_Index = 0 : Number_Index--;
			}
			else if (Input_Array[2])
			{
				Repeats_Array[Number_Index] == 9 ? Repeats_Array[Number_Index] = 0 : Repeats_Array[Number_Index]++;
				Repeats_Array[4] == 0 ? Repeats_Array[4] = 1 : Repeats_Array[4] = Repeats_Array[4];
			}
			else if (Input_Array[3])
			{
				Repeats_Array[Number_Index] == 0 ? Repeats_Array[Number_Index] = 9 : Repeats_Array[Number_Index]--;
				Repeats_Array[4] == 0 ? Repeats_Array[4] = 9 : Repeats_Array[4] = Repeats_Array[4];
			}
			break;
		// --------------------------------- SET SHUTTER SPEED ---------------------------------------------------------
		case 4:
			if (Input_Array[0])
			{
				Number_Index++;
				// RETURN, IF EVERY NUMBER HAS BEEN CHANGED
				if (Number_Index > 3)
				{
					// GO BACK TO MAIN MENU
					restoreMenu();
					return;
				}
			}
			else if (Input_Array[1])
			{
				Number_Index == 0 ? Number_Index = 0 : Number_Index--;
			}
			else if (Input_Array[2])
			{
				Shutter_Speed_Array[Number_Index] == 9 ? Shutter_Speed_Array[Number_Index] = 0 : Shutter_Speed_Array[Number_Index]++;
				Shutter_Speed_Array[0] > 5 ? Shutter_Speed_Array[0] = 0 : Shutter_Speed_Array[0] = Shutter_Speed_Array[0];
				Shutter_Speed_Array[2] > 5 ? Shutter_Speed_Array[2] = 0 : Shutter_Speed_Array[2] = Shutter_Speed_Array[2];
			}
			else if (Input_Array[3])
			{
				Shutter_Speed_Array[Number_Index] == 0 ? Shutter_Speed_Array[Number_Index] = 9 : Shutter_Speed_Array[Number_Index]--;
				Shutter_Speed_Array[0] > 5 ? Shutter_Speed_Array[0] = 5 : Shutter_Speed_Array[0] = Shutter_Speed_Array[0];
				Shutter_Speed_Array[2] > 5 ? Shutter_Speed_Array[2] = 5 : Shutter_Speed_Array[2] = Shutter_Speed_Array[2];
			}
			break;
	}
	// PRINT MENU
	printMenu(Parameter_Type);
}
// ##################################################################################################################### 
// ######################################### RESTORE MENU ##############################################################
// #####################################################################################################################
void restoreMenu()
{
	lcd.setBrightness(250);
	// GET WAY DELAY
	for (byte X = 0; X < 4; X++)
		Way_Delay[X] = 0;
	// CALCULATE WAY DELAY
	long Way_Millimeter = Way_Array[0] * 1000 + Way_Array[1] * 100 + Way_Array[2] * 10 + Way_Array[3];
	long Way_Delay_Calc = round((60 * Way_Millimeter) / ((Pulley_Diameter * Math_Pi) * Engine_RPM));
	// GET SINGLE PARTS OF WAY DELAY
	long Way_Delay_Seconds = Way_Delay_Calc % 60;
	long Way_Delay_Minutes = Way_Delay_Calc / 60;
	// GET SINGLE PARTS OF WAY DELAY
	Way_Delay[3] = Way_Delay_Seconds % 10;
	Way_Delay_Seconds /= 10;
	Way_Delay[2] = Way_Delay_Seconds % 10;
	Way_Delay[1] = Way_Delay_Minutes % 10;
	Way_Delay_Minutes /= 10;
	Way_Delay[0] = Way_Delay_Minutes % 10;
	// GET MAX. REPEATS
	long User_Lenght = Way_Array[0] * 1000 + Way_Array[1] * 100 + Way_Array[2] * 10 + Way_Array[3];
	long User_Repeats = Repeats_Array[0] * 1000 + Repeats_Array[1] * 100 + Repeats_Array[2] * 10 + Repeats_Array[3];
	long Total_Lenght = User_Repeats * User_Lenght;
	// CLEAR REPEATS DELAY
	for (byte X = 0; X < 4; X++)
		Repeats_Array[X] = 0;
	// COMPARE LENGHTS
	while (Total_Lenght > Maximum_Lenght)
	{
		User_Repeats--;
		Total_Lenght = User_Repeats * User_Lenght;
	}
	// GET SINGLE PARTS OF NEW REPEATS
	byte X = 3;
	while (User_Repeats)
	{
		Repeats_Array[X] = User_Repeats % 10;
		User_Repeats /= 10;
		X--;
	}
	for (byte X = 0; X < 4; X++)
		EEPROM.write(X + 10, Way_Array[X]);
	for (byte X = 0; X < 6; X++)
		EEPROM.write(X + 20, Delay_Array[X]);	
	for (byte X = 0; X < 5; X++)
		EEPROM.write(X + 30, Repeats_Array[X]);
	for (byte X = 0; X < 4; X++)
		EEPROM.write(X + 40, Shutter_Speed_Array[X]);					
	// CLEAR INPUT ARRAY
	for (byte X = 0; X < 4; X++)
		Input_Array[X] = 0;
	Main_Menu = true;
	lcd.clearDisplay();
	printMenu();
	menuManagement();
}
// #####################################################################################################################  
// ######################################### PREPARE SUB MENU ##########################################################
// #####################################################################################################################
void prepareSubMenu(byte Parameter_Register)
{
	Main_Menu = false;
	Number_Index = 0;
	lcd.clearDisplay();
	// PRINT THE NEW MENU
	printMenu(Parameter_Register);
}
// #####################################################################################################################  
// ######################################### PROCESS CAMERA SETTING ####################################################
// #####################################################################################################################
void processCameraSettings(byte Parameter_Register)
{
	switch (Parameter_Register)
	{
		case 5:
			Current_Auto_Focus ? Current_Auto_Focus = false : Current_Auto_Focus = true;
			Current_Auto_Focus ? EEPROM.write(50, 1) : EEPROM.write(50, 0);
			break;
		case 6:
			Current_Mirror_Lockup ? Current_Mirror_Lockup = false : Current_Mirror_Lockup = true;
			Current_Mirror_Lockup ? EEPROM.write(60, 1) : EEPROM.write(60, 0);	
			break;
	}
}
// #####################################################################################################################  
// ######################################### SWITCH PAGE ###############################################################
// #####################################################################################################################
void switchPage()
{
	if (Register > 4)
	{
		if (Page == 0) 
			lcd.clearDisplay();
		Page = 1;
	}
	else if (Register < 5)
	{
		if (Page == 1) 
			lcd.clearDisplay();
		Page = 0;
	}
}
// #####################################################################################################################   
// ######################################### END OF CODE ###############################################################
// #####################################################################################################################