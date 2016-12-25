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
	pinMode(Controller_A, INPUT);
	pinMode(Controller_B, INPUT);
	pinMode(Controller_Z, INPUT);
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

	controller.XMin = EEPROM.read(0);
	controller.XMax = EEPROM.read(1);
	controller.YMin = EEPROM.read(2);
	controller.YMax = EEPROM.read(3);
}
// #####################################################################################################################  
// ######################################### END OF CODE ###############################################################
// #####################################################################################################################