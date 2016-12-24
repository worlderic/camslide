// #####################################################################################################################
// ######################################### CONTROLLER ################################################################
// #####################################################################################################################
void getControllerData(boolean mapData)
{
	controller.A = digitalRead(Controller_A);
	controller.B = digitalRead(Controller_B);
	controller.Z = digitalRead(Controller_Z);

	controller.X = analogRead(Controller_X);
	controller.Y = analogRead(Controller_Y);

	/* 	Map the analog data:
		Range: -100 to +100
	*/
	if (mapData)
	{
		controller.X = map(controller.X, controller.XMin, controller.XMax, -100, 100);
		controller.Y = map(controller.Y, controller.YMin, controller.YMax, -100, 100);
	}
}

void calibrateController()
{
	int bufferXMin = 1023;
	int bufferXMax = 0;
	int bufferYMin = 1023;
	int bufferYMax = 0;

	do {
		getControllerData(false);
		if (controller.X < bufferXMin)
			bufferXMin = controller.X;
		if (controller.X > bufferXMax)
			bufferXMax = controller.X;
		if (controller.Y < bufferYMin)
			bufferYMin = controller.Y;
		if (controller.Y > bufferYMax)
			bufferYMax = controller.Y;
	} while (!controller.Z);
	
	controller.XMin = bufferXMin;
	controller.XMax = bufferXMax;
	controller.YMin = bufferYMin;
	controller.YMax = bufferYMax;

	EEPROM.write(0, controller.XMin);
	EEPROM.write(1, controller.XMax);
	EEPROM.write(2, controller.YMin);
	EEPROM.write(3, controller.YMax);

	#ifdef D3BUG
	Serial.print(F("\nCalibrated data:"));
	Serial.print(F("\n  X: ") + controller.XMin + F(" | ") + controller.XMax);
	Serial.print(F("\n  Y: ") + controller.YMin + F(" | ") + controller.YMax);
	delay(1000);
	#endif
}
// #####################################################################################################################  
// ######################################### END OF CODE ###############################################################
// #####################################################################################################################