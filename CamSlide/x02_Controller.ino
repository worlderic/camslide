// #####################################################################################################################
// ######################################### CONTROLLER ################################################################
// #####################################################################################################################
void getControllerData(boolean mapData)
{
	controllerPrev.A = controller.A;
	controllerPrev.B = controller.B;
	controllerPrev.Z = controller.Z;

	controllerPrev.X = controller.X;
	controllerPrev.Y = controller.Y;

	controller.A = !digitalRead(Controller_A);
	controller.B = !digitalRead(Controller_B);
	controller.Z = !digitalRead(Controller_Z);

	controller.X = analogRead(Controller_X);
	controller.Y = analogRead(Controller_Y);

	/* 	Map the analog data:
		Range: -100 to +100
	*/
	if (mapData)
	{
		controller.X = map(controller.X, controller.XMin, controller.XMax, -100, 100);
		controller.Y = map(controller.Y, controller.YMin, controller.YMax, 100, -100);
	}
}

void calibrateController()
{
	lcd.clearDisplay();
	printString(lcdCalibrateDisplay01, 0, 0);
	printString(lcdCalibrateDisplay02, 0, 1);
	printString(lcdCalibrateDisplay03, 0, 2);
	printString(lcdCalibrateDisplay04, 0, 3);
	printString(lcdCalibrateDisplay05, 0, 5);
	printString(lcdCalibrateDisplay06, 0, 6);

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

	EEPROM.write(EEPROM_MSB_ctrlMinX, (controller.XMin >> 8) & 0xFF);
	EEPROM.write(EEPROM_LSB_ctrlMinX, controller.XMin & 0xFF);
	EEPROM.write(EEPROM_MSB_ctrlMaxX, (controller.XMax >> 8) & 0xFF);
	EEPROM.write(EEPROM_LSB_ctrlMaxX, controller.XMax & 0xFF);
	EEPROM.write(EEPROM_MSB_ctrlMinY, (controller.YMin >> 8) & 0xFF);
	EEPROM.write(EEPROM_LSB_ctrlMinY, controller.YMin & 0xFF);
	EEPROM.write(EEPROM_MSB_ctrlMaxY, (controller.YMax >> 8) & 0xFF);
	EEPROM.write(EEPROM_LSB_ctrlMaxY, controller.YMax & 0xFF);

	lcd.clearDisplay();
	printString(lcdCalibrateDisplay07, 0, 0);
	printString(lcdCalibrateDisplay08, 0, 1);
	printString(lcdCalibrateDisplay09, 0, 2);
	printString(lcdCalibrateDisplay10, 0, 3);

	#ifdef D3BUG
	Serial.print(F("\nCalibrated data:"));
	Serial.print("\n  X: " + String(controller.XMin) + ", " + String(controller.XMax));
	Serial.print("\n  Y: " + String(controller.YMin) + ", " + String(controller.YMax));
	delay(1000);
	#endif
}
// #####################################################################################################################  
// ######################################### END OF CODE ###############################################################
// #####################################################################################################################