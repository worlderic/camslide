// #####################################################################################################################
// ######################################### BOOT ######################################################################
// #####################################################################################################################
void boot()
{
	lcd.initialize();
	lcd.rotateDisplay180();
	lcd.drawBitmap(bootscreen, 0, 0, 16, 8);

	pinMode(DRV8825_ENBL, OUTPUT);
	pinMode(DRV8825_DIR, OUTPUT);
	pinMode(DRV8825_STEP, OUTPUT);
	pinMode(DRV8825_M0, OUTPUT);
	pinMode(DRV8825_M1, OUTPUT);
	pinMode(DRV8825_M2, OUTPUT);
	pinMode(Sensor, INPUT);
	pinMode(Controller_A, INPUT_PULLUP);
	pinMode(Controller_B, INPUT_PULLUP);
	pinMode(Controller_Z, INPUT_PULLUP);
	pinMode(Camera_Focus, OUTPUT);
	pinMode(Camera_Trigger, OUTPUT);

	controller.A = controller.B = controller.X = controller.Y = controller.Z = 0;

	// Enter controller calibration mode
	unsigned long bootTimer = millis() + 1000;
	while (millis() < bootTimer)
	{
		getControllerData(false);
		if (controller.A && controller.B)
			calibrateController();
	}

	controller.XMin = (EEPROM.read(EEPROM_MSB_ctrlMinX) << 8) | EEPROM.read(EEPROM_LSB_ctrlMinX);
	controller.XMax = (EEPROM.read(EEPROM_MSB_ctrlMaxX) << 8) | EEPROM.read(EEPROM_LSB_ctrlMaxX);
	controller.YMin = (EEPROM.read(EEPROM_MSB_ctrlMinY) << 8) | EEPROM.read(EEPROM_LSB_ctrlMinY);
	controller.YMax = (EEPROM.read(EEPROM_MSB_ctrlMaxY) << 8) | EEPROM.read(EEPROM_LSB_ctrlMaxY);

	for (byte i = 0; i < 4; i++)
	{
		slider.position[i] = EEPROM.read(i + EEPROM_pos);
		slider.length[i] = EEPROM.read(i + EEPROM_length);
	}

	mainMenu.maxIndex = 2;
	photoMenu.maxIndex = 4;
	settingsMenu.maxIndex = 1;

	unactiveAll();
	gotoZero();
	printMenu();
}
// #####################################################################################################################  
// ######################################### END OF CODE ###############################################################
// #####################################################################################################################