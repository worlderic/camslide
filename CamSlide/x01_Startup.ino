// #####################################################################################################################
// ######################################### STARTUP ###################################################################
// #####################################################################################################################
void startup()
{
	// INITIALIZE DISPLAY
	lcd.initialize();
	// ROTATE DISPLAY
	lcd.rotateDisplay180();
	lcd.setBrightness(250);
	#ifndef TEST_RUN
	// PRINT START SCREEN
	lcd.drawBitmap(Bitmap_Start_Screen, 0, 0, 16, 8);
	delay(500);
	#endif
	// SET INPUTS
	pinMode(Input_Button_OK,     INPUT);
	pinMode(Input_Button_Cancel, INPUT);
	pinMode(Input_Button_Up,     INPUT);
	pinMode(Input_Button_Down,   INPUT);
	// SET OUTPUTS
	pinMode(Output_Focus,        OUTPUT);
	pinMode(Output_Camera,       OUTPUT);
	pinMode(Output_Relais_Left,  OUTPUT);
	pinMode(Output_Relais_Right, OUTPUT);
	// DISABLE RELAIS
	digitalWrite(Output_Relais_Left,  HIGH);
	digitalWrite(Output_Relais_Right, HIGH);
	// GET ALL STORED VALUES
	for (byte X = 0; X < 4; X++)
		Way_Array[X] = EEPROM.read(X + 10);
	for (byte X = 0; X < 6; X++)
		Delay_Array[X] = EEPROM.read(X + 20);
	for (byte X = 0; X < 5; X++)
		Repeats_Array[X] = EEPROM.read(X + 30);
	for (byte X = 0; X < 4; X++)
		Shutter_Speed_Array[X] = EEPROM.read(X + 40);
	EEPROM.read(50) == 0 ? Current_Auto_Focus = false : Current_Auto_Focus = true;
	EEPROM.read(60) == 0 ? Current_Mirror_Lockup = false : Current_Mirror_Lockup = true;
	// SET SLIDE TO ZERO POSITION
	setSlideToZero();
	restoreMenu();
}
// #####################################################################################################################  
// ######################################### END OF CODE ###############################################################
// #####################################################################################################################