// #####################################################################################################################
// ######################################### INPUT MANAGEMENT ##########################################################
// #####################################################################################################################
void inputManagement()
{
	boolean Button_Pressed_Once = false;
	// CLEAR ALL INPUT
	for (byte X = 0; X < 4; X++)
		Input_Array[X] = 0;
	// WAIT UNTIL BUTTON GOES LOW
	while (digitalRead(Input_Button_OK) || digitalRead(Input_Button_Cancel) || digitalRead(Input_Button_Up) || digitalRead(Input_Button_Down))
	{
		// SET THE PINS
		Input_Array[0] = digitalRead(Input_Button_OK);
		Input_Array[1] = digitalRead(Input_Button_Cancel);
		Input_Array[2] = digitalRead(Input_Button_Up);
		Input_Array[3] = digitalRead(Input_Button_Down);
		delay(25);
		Button_Pressed_Once = true;
	}
	// START MENU MANAGEMENT, IF A BUTTON IS PRESSED
	if (Button_Pressed_Once && Main_Menu)
		menuManagement();
	else if (Button_Pressed_Once && !Main_Menu)
		menuManagement(Register);
}
// #####################################################################################################################   
// ######################################### INTERRUPT RIGHT SIDE ######################################################
// #####################################################################################################################
void interruptHandlerRight()
{
	// DISABLE OUTPUT
	digitalWrite(Output_Relais_Right, HIGH);
	// GO AWAY FROM SENSOR
	while (digitalRead(Input_Sensor_Right) && !digitalRead(Input_Sensor_Left))
		digitalWrite(Output_Relais_Left, LOW);
	digitalWrite(Output_Relais_Left, HIGH);
	// DISABLE WORKING
	System_Is_Working = false;
}
// ##################################################################################################################### 
// ######################################### INTERRUPT LEFT SIDE #######################################################
// #####################################################################################################################
void interruptHandlerLeft()
{
	// DISABLE OUTPUT
	digitalWrite(Output_Relais_Left, HIGH);
	// GO AWAY FROM SENSOR
	while (digitalRead(Input_Sensor_Left) && !digitalRead(Input_Sensor_Right))
		digitalWrite(Output_Relais_Right, LOW);
	digitalWrite(Output_Relais_Right, HIGH);
	// STARTUP DONE
	Startup_Done = true;
	Slide_On_Track = false;
}
// #####################################################################################################################   
// ######################################### END OF CODE ###############################################################
// #####################################################################################################################