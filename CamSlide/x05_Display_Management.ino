// ##################################################################################################################### 
// ######################################### WRITE STRING ##############################################################
// #####################################################################################################################
void writeText(const char Parameter_String[], byte Parameter_X, byte Parameter_Y)
{
	// SET PROGMEM BUFFER
	char x05_Buffer;
	// PRINT CHAR FROM PROGMEM
	if (!Parameter_String)
		return;
    while ((x05_Buffer = pgm_read_byte(Parameter_String++)))
    {
      	lcd.printChar(x05_Buffer, Parameter_X, Parameter_Y);
      	Parameter_X++;
    }
}
// #####################################################################################################################  
// ######################################### PRINT MENU ################################################################
// #####################################################################################################################
void printMenu()
{
	// --------------------------------- HEADER ------------------------------------------------------------------------
	writeText(LCD_Menu_Header, 4, 0);
	// --------------------------------- START -------------------------------------------------------------------------
	writeText(LCD_Menu_Start, 2, 2);
	// SWITCH PAGE
	if (Page == 0)
	{
	// --------------------------------- WAY ---------------------------------------------------------------------------
		writeText(LCD_Menu_Way, 2, 4);
		if (Show_Way_Delay)
		{
			for (byte X = 0; X < 4; X++)
				lcd.printNumber((long)Way_Array[X], 9 + X, 4);
			writeText(LCD_Unit_mm, 13, 4);
		}
		else
		{
			lcd.printChar(' ', 9, 4);
			lcd.printNumber((long)Way_Delay[0], 10, 4);
			lcd.printNumber((long)Way_Delay[1], 11, 4);
			lcd.printChar(':', 12, 4);
			lcd.printNumber((long)Way_Delay[2], 13, 4);
			lcd.printNumber((long)Way_Delay[3], 14, 4);
		}
	// --------------------------------- DELAY -------------------------------------------------------------------------
		writeText(LCD_Menu_Delay, 2, 5);
			lcd.printNumber((long)Delay_Array[0], 7, 5);
			lcd.printNumber((long)Delay_Array[1], 8, 5);
			lcd.printChar(':', 9, 5);
			lcd.printNumber((long)Delay_Array[2], 10, 5);
			lcd.printNumber((long)Delay_Array[3], 11, 5);
			lcd.printChar(':', 12, 5);
			lcd.printNumber((long)Delay_Array[4], 13, 5);
			lcd.printNumber((long)Delay_Array[5], 14, 5);
	// --------------------------------- REPEATS -----------------------------------------------------------------------
		writeText(LCD_Menu_Repeats, 2, 6);
		for (byte X = 0; X < 4; X++)
			lcd.printNumber((long)Repeats_Array[X], 7 + X, 6);
			lcd.printChar('|', 12, 6);
			lcd.printNumber((long)Repeats_Array[4], 14, 6);
	// --------------------------------- SHUTTER SPEED -----------------------------------------------------------------
		writeText(LCD_Menu_Shutter_Speed, 2, 7);
			lcd.printNumber((long)Shutter_Speed_Array[0], 10, 7);
			lcd.printNumber((long)Shutter_Speed_Array[1], 11, 7);
			lcd.printChar(':', 12, 7);
			lcd.printNumber((long)Shutter_Speed_Array[2], 13, 7);
			lcd.printNumber((long)Shutter_Speed_Array[3], 14, 7);
	}
	else
	{
	// --------------------------------- AUTO FOCUS --------------------------------------------------------------------
		writeText(LCD_Menu_Auto_Focus, 2, 4);
			Current_Auto_Focus ? writeText(LCD_State_On, 12, 4) : writeText(LCD_State_Off, 12, 4);
	// --------------------------------- MIRROR LOCKUP -----------------------------------------------------------------
		writeText(LCD_Menu_Mirror_Lockup, 2, 5);
			Current_Mirror_Lockup ? writeText(LCD_State_On, 12, 5) : writeText(LCD_State_Off, 12, 5);
	}
}
// #####################################################################################################################   
// ######################################### PRINT MENU (NUMBERS) ######################################################
// #####################################################################################################################
void printMenu(byte Parameter_Register)
{
	switch (Parameter_Register)
	{
		// --------------------------------- SET WAY -------------------------------------------------------------------
		case 1:
			// PRINT BASIC MENU
			writeText(LCD_Numbers_Way, 3, 0);
			lcd.printNumber((long)Way_Array[0], 5, 3);
			lcd.printNumber((long)Way_Array[1], 7, 3);
			lcd.printNumber((long)Way_Array[2], 9, 3);
			lcd.printNumber((long)Way_Array[3], 11, 3);
			writeText(LCD_Unit_Millimeter, 3, 7);
			// PRINT NUMBER INDEX
			Number_Index == 0 ? lcd.printChar('^', 5, 5) : lcd.printChar(' ', 5, 5);
			Number_Index == 1 ? lcd.printChar('^', 7, 5) : lcd.printChar(' ', 7, 5);
			Number_Index == 2 ? lcd.printChar('^', 9, 5) : lcd.printChar(' ', 9, 5);
			Number_Index == 3 ? lcd.printChar('^', 11, 5) : lcd.printChar(' ', 11, 5);
			break;
		// --------------------------------- SET DELAY -----------------------------------------------------------------
		case 2:
			// PRINT BASIC MENU
			writeText(LCD_Numbers_Delay, 2, 0);
			lcd.printNumber((long)Delay_Array[0], 1, 3);
			lcd.printNumber((long)Delay_Array[1], 3, 3);
			lcd.printChar(':', 5, 3);
			lcd.printNumber((long)Delay_Array[2], 7, 3);
			lcd.printNumber((long)Delay_Array[3], 9, 3);
			lcd.printChar(':', 11, 3);
			lcd.printNumber((long)Delay_Array[4], 13, 3);
			lcd.printNumber((long)Delay_Array[5], 15, 3);
			// PRINT UNIT DEPENDING ON PLACE
			if (Number_Index == 0 || Number_Index == 1)
				writeText(LCD_Unit_Hours, 5, 7);
			else if (Number_Index == 2 || Number_Index == 3)
				writeText(LCD_Unit_Minutes, 5, 7);
			else
				writeText(LCD_Unit_Seconds, 5, 7);
			// PRINT NUMBER INDEX
			Number_Index == 0 ? lcd.printChar('^', 1, 5) : lcd.printChar(' ', 1, 5);
			Number_Index == 1 ? lcd.printChar('^', 3, 5) : lcd.printChar(' ', 3, 5);
			Number_Index == 2 ? lcd.printChar('^', 7, 5) : lcd.printChar(' ', 7, 5);
			Number_Index == 3 ? lcd.printChar('^', 9, 5) : lcd.printChar(' ', 9, 5);
			Number_Index == 4 ? lcd.printChar('^', 13, 5) : lcd.printChar(' ', 13, 5);
			Number_Index == 5 ? lcd.printChar('^', 15, 5) : lcd.printChar(' ', 15, 5);
			break;
		// --------------------------------- SET REPEATS ---------------------------------------------------------------
		case 3:
			// PRINT BASIC MENU
			writeText(LCD_Numbers_Repeats, 1, 0);
			lcd.printNumber((long)Repeats_Array[0], 3, 3);
			lcd.printNumber((long)Repeats_Array[1], 5, 3);
			lcd.printNumber((long)Repeats_Array[2], 7, 3);
			lcd.printNumber((long)Repeats_Array[3], 9, 3);
			lcd.printChar('|', 11, 3);
			lcd.printNumber((long)Repeats_Array[4], 13, 3);
			// PRINT NUMBER INDEX
			Number_Index == 0 ? lcd.printChar('^', 3, 5) : lcd.printChar(' ', 3, 5);
			Number_Index == 1 ? lcd.printChar('^', 5, 5) : lcd.printChar(' ', 5, 5);
			Number_Index == 2 ? lcd.printChar('^', 7, 5) : lcd.printChar(' ', 7, 5);
			Number_Index == 3 ? lcd.printChar('^', 9, 5) : lcd.printChar(' ', 9, 5);
			Number_Index == 4 ? lcd.printChar('^', 13, 5) : lcd.printChar(' ', 13, 5);
			break;
		// --------------------------------- SET SHUTTER SPEED ---------------------------------------------------------
		case 4:
			// PRINT BASIC MENU
			writeText(LCD_Numbers_Shutter_Speed, 1, 0);
			lcd.printNumber((long)Shutter_Speed_Array[0], 4, 3);
			lcd.printNumber((long)Shutter_Speed_Array[1], 6, 3);
			lcd.printChar(':', 8, 3);
			lcd.printNumber((long)Shutter_Speed_Array[2], 10, 3);
			lcd.printNumber((long)Shutter_Speed_Array[3], 12, 3);
			// PRINT UNIT DEPENDING ON PLACE
			if (Number_Index == 0 || Number_Index == 1)
				writeText(LCD_Unit_Minutes, 5, 7);
			else
				writeText(LCD_Unit_Seconds, 5, 7);
			// PRINT NUMBER INDEX
			Number_Index == 0 ? lcd.printChar('^', 4, 5) : lcd.printChar(' ', 4, 5);
			Number_Index == 1 ? lcd.printChar('^', 6, 5) : lcd.printChar(' ', 6, 5);
			Number_Index == 2 ? lcd.printChar('^', 10, 5) : lcd.printChar(' ', 10, 5);
			Number_Index == 3 ? lcd.printChar('^', 12, 5) : lcd.printChar(' ', 12, 5);
			break;
	}
}
// #####################################################################################################################   
// ######################################### PRINT SELECTED ITEM #######################################################
// #####################################################################################################################
void printSelectedItem(byte Y)
{
	for (byte X = 2; X < 8; X++)
		Y == X ? lcd.printChar('>', 0, X) : lcd.printChar(' ', 0, X);
}
// #####################################################################################################################  
// ######################################### SET DISPLAY ###############################################################
// #####################################################################################################################
void setDisplay(boolean Parameter_State)
{
	if (Parameter_State)
	{
		lcd.setDisplayOn();
		lcd.setBrightness(0);
		for (byte X = 0; X < 250; X++)
		{
			lcd.setBrightness(X);
			delay(2);
		}
	}
	else
	{
		for (byte X = 250; X > 0; X--)
		{
			lcd.setBrightness(X);
			delay(2);
		}
		lcd.setDisplayOff();
	}

}
// #####################################################################################################################  
// ######################################### END OF CODE ###############################################################
// #####################################################################################################################