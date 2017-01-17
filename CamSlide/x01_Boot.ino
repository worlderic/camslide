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

	controller.XMin = (EEPROM.read(0) << 8) | EEPROM.read(1);
	controller.XMax = (EEPROM.read(2) << 8) | EEPROM.read(3);
	controller.YMin = (EEPROM.read(4) << 8) | EEPROM.read(5);
	controller.YMax = (EEPROM.read(6) << 8) | EEPROM.read(7);

	mainMenu.index = photoMenu.index = videoMenu.index = settingsMenu.index = 0;
	mainMenu.maxIndex = 3;
	photoMenu.maxIndex = 1;
	videoMenu.maxIndex = 1;
	settingsMenu.maxIndex = 1;
	mainMenu.active = true;
	photoMenu.active = videoMenu.active = manualMenu.active = settingsMenu.active = false;

	printMenu();
}
// #####################################################################################################################  
// ######################################### END OF CODE ###############################################################
// #####################################################################################################################