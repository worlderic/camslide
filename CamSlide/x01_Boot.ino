// #####################################################################################################################
// ######################################### BOOT ######################################################################
// #####################################################################################################################
void boot()
{
	lcd.init(true);
	lcd.rotateDisplay180();
	//lcd.drawBitmap(bootscreen, 0, 0, 16, 8);
	printString(lcdStartup00, 7, 2);
	printString(lcdStartup01, 6, 3);
	printString(lcdStartup02, 8, 6);

	pinMode(DRV8825_A_ENBL, OUTPUT);
	pinMode(DRV8825_A_DIR, OUTPUT);
	pinMode(DRV8825_A_STEP, OUTPUT);
	pinMode(DRV8825_B_ENBL, OUTPUT);
	pinMode(DRV8825_B_DIR, OUTPUT);
	pinMode(DRV8825_B_STEP, OUTPUT);
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
		slider.length[i] = EEPROM.read(i + EEPROM_length);
		
		camera.amount[i] = 0;
		camera.repeats[i] = 0;
		camera.shutter[i] = 0;
		camera.delay[i] = 0;
	}

	slider.transmission = ((EEPROM.read(EEPROM_MSB_transmission) << 8) | EEPROM.read(EEPROM_LSB_transmission)) / 100; // steps/mm
	slider.position1 = -1; // -1 means the position is unclear
	slider.position2 = 0;
	slider.zeroIsLeft = true;

	turner.transmission = 38.25; // steps/deg    13772
	turner.position1 = 0;
	turner.position2 = 0;
	turner.absPos = 0;

	camera.amount[3] = 1;
	camera.repeats[3] = 1;
	camera.travelDistance = 0;
	camera.distancePerShot = 0;
	camera.mirrorLockup = EEPROM.read(EEPROM_mirrorLockup) == 1 ? true : false;
	camera.autoFocus = EEPROM.read(EEPROM_autoFocus) == 1 ? true : false;

	motor.enabled = false;
	motor.locked = EEPROM.read(EEPROM_motorLocked) == 1 ? true : false;
	motor.delay = MOTOR_DELAY; // µs

	step.minDelay = MOTOR_MIN_DELAY; // µs
	step.maxDelay = MOTOR_MAX_DELAY; // µs

	mainMenu.maxIndex = 2;
	photoMenu.maxIndex = 0; // Irellevant
	settingsMenu.maxIndex = 4;

	// Check sensor
	if (!digitalRead(Sensor))
	{
		lcd.clear();
		printString(lcdSensorError00, 0, 0);
		printString(lcdSensorError01, 0, 1);
		printString(lcdSensorError02, 0, 3);
		printString(lcdSensorError03, 0, 4);
		printString(lcdSensorError04, 0, 5);
		printString(lcdSensorError05, 0, 6);
		delay(6000);
	}

	unactiveAll();
	printMenu();
}