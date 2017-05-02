// #####################################################################################################################
// ######################################### DISPLAY ###################################################################
// #####################################################################################################################
void printString(const char data[], byte column, byte row)
{
	char buffer;

	if (!data)
		return;
    while ((buffer = pgm_read_byte(data++)))
    {
      	lcd.printChar(buffer, column, row);
      	column++;
    }
}

void printMenu()
{
	// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
	// MAIN MENU
	// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
	if (!mainMenu.indexActive)
	{
		switch (mainMenu.index)
		{
			case 0:
				lcd.drawBitmap(photoMenuBitmap, 0, 0, 16, 8);
				break;
			case 1:
				lcd.drawBitmap(manualMenuBitmap, 0, 0, 16, 8);
				break;
			case 2:
				lcd.drawBitmap(settingsMenuBitmap, 0, 0, 16, 8);
				break;
			default:
				break;
		}
	}
	else
	{
		int buffer = 0;
		switch(mainMenu.index)
		{
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			// PHOTO MENU
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			case 0:
				switch (photoMenu.index)
				{
					case 0: // Select zero
						printString(lcdPhotoMenuZero00, 2, 0);
						printString(lcdPhotoMenuZero01, 0, 2);
						printString(lcdPhotoMenuZero02, 0, 3);
						printString(lcdPhotoMenuZero03, 0, 4);
						printString(lcdPhotoMenuZero04, 0, 5);
						printString(lcdPhotoMenuZero05, 0, 6);
						break;
					case 1: // Goto zero
						printString(lcdPhotoMenuZero10, 1, 0);
						printString(lcdPhotoMenuZero11, 0, 2);
						printString(lcdPhotoMenuZero12, 0, 3);
						printString(lcdPhotoMenuZero13, 0, 4);
						printString(lcdPhotoMenuZero14, 0, 5);
						break;
					case 2: // Select start angle
						printString(lcdPhotoMenuAngle00, 1, 0);
						printString(lcdTextCurrentPosition, 0, 2);
						printString(lcdUnitDegree, 10, 5);
						break;
					case 3: // Select length
						printString(lcdPhotoMenuLength00, 1, 0);
						printString(lcdTextCurrentPosition, 0, 2);
						printString(lcdUnitMillimeter, 10, 5);
						break;
					case 4: // Select end angle
						printString(lcdPhotoMenuAngle10, 1, 0);
						printString(lcdTextCurrentPosition, 0, 2);
						printString(lcdUnitDegree, 10, 5);
						break;
					case 5: // Amount of shots
						printString(lcdPhotoMenuAmount00, 3, 0);
						printHorizontalSelector(camera.amount, selector.index, 3, 4, 3);
						printBuffer((int)camera.distancePerShot, 5, 7, true);
						printString(lcdUnitMillimeterPerShot, 10, 7);
						break;
					case 6: // Repeats of capture
						printString(lcdPhotoMenuRepeats00, 2, 0);
						printHorizontalSelector(camera.repeats, selector.index, 3, 4, 3);
						break;
				}
				/*
				if (!photoMenu.indexActive)
				{
					printString(lcdPhotoMenu00, 3, 0);

					printString(lcdPhotoMenu01, 0, 2);
					buffer = arrayToInt(camera.distance);
					printBuffer(buffer, 9, 2);
					printString(lcdUnitMillimeter, 13, 2);

					printString(lcdPhotoMenu02, 0, 3);
					buffer = arrayToInt(camera.repeats);
					printBuffer(buffer, 9, 3);

					printString(lcdPhotoMenu03, 0, 4);
					buffer = arrayToInt(camera.shutter);
					printBuffer(buffer, 9, 4);
					printString(lcdUnitSecond, 13, 4);

					printString(lcdPhotoMenu04, 0, 5);
					buffer = arrayToInt(camera.delay);
					printBuffer(buffer, 9, 5);
					printString(lcdUnitSecond, 13, 5);

					printString(lcdPhotoMenu05, 0, 7);

					printVerticalSelector(photoMenu.index, 0, 2, 4);
				}
				else 
				{
					switch (photoMenu.index)
					{
						case 0:
							printString(lcdPhotoMenuDistance, 4, 0);
							printHorizontalSelector(camera.distance, selector.index, 3, 2, 3);
							printString(lcdUnitMillimeter, 11, 3);
							break;
						case 1:
							printString(lcdPhotoMenuRepeats, 4, 0);
							printHorizontalSelector(camera.repeats, selector.index, 3, 4, 3);
							break;
						case 2:
							printString(lcdPhotoMenuShutter, 1, 0);
							printHorizontalSelector(camera.shutter, selector.index, 3, 2, 3);
							printString(lcdUnitSecond, 11, 3);
							break;
						case 3:
							printString(lcdPhotoMenuDelay, 5, 0);
							printHorizontalSelector(camera.delay, selector.index, 3, 2, 3);
							printString(lcdUnitSecond, 11, 3);
							break;
					}
				}
				*/
				break;
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			// MANUAL MENU
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			case 1:
				// Nothing to do here
				// Everything will be set & shown @x05_Working
				break;
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			// SETTINGS MENU
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			case 2:
				if (!settingsMenu.indexActive)
				{
					printString(lcdSettingsMenu00, 3, 0);
					printString(lcdSettingsMenu01, 0, 2);
					motor.enabled ? printString(lcdMenuOn, 12, 2) : printString(lcdMenuOff, 12, 2);
					printString(lcdSettingsMenu02, 0, 3);
					buffer = arrayToInt(slider.length);
					printBuffer(buffer, 9, 3, false);
					printString(lcdUnitMillimeter, 13, 3);

					printString(lcdSettingsMenu03, 0, 4);

					printVerticalSelector(settingsMenu.index, 0, 2, 4);
				}
				else 
				{
					switch (settingsMenu.index)
					{
						case 0:
							// Nothing to do here
							break;
						case 1:
							printString(lcdSettingsMenuLength, 4, 0);
							printHorizontalSelector(slider.length, selector.index, 3, 2, 3);
							printString(lcdUnitMillimeter, 11, 3);
							break;
						case 2:
							printString(lcdSettingsMenuReset00, 4, 0);
							printString(lcdSettingsMenuReset01, 0, 2);
							printString(lcdSettingsMenuReset02, 0, 3);
							printString(lcdSettingsMenuReset03, 0, 4);
							printString(lcdSettingsMenuReset04, 4, 5);
							break;
					}
				}
				break;
		}
	}
}

void printHorizontalSelector(int value[], int index, int max, int lcdX, int lcdY)
{
	for (int i = 0; i < max + 1; i++)
	{
		lcd.printNumber(long(value[i]), lcdX + i * 2, lcdY);
		if (index == i)
			lcd.printChar('^', lcdX + i * 2, lcdY + 2);
		else 
			lcd.printChar(' ', lcdX + i * 2, lcdY + 2);
	}
}

void printVerticalSelector(int index, int lcdX, int lcdY, int blank) // default for blank: 99
{	
	index == blank ? lcd.printChar('>', lcdX, lcdY + index + 1) : lcd.printChar('>', lcdX, lcdY + index);
}

void printBuffer(int buffer, int lcdX, int lcdY, boolean blanc)
{
	int counter = 0;
	if (buffer < 10)
		counter = 3;
	else if (buffer < 100)
		counter = 2;
	else if (buffer < 1000)
		counter = 1;
	else 
		counter = 0;
	if (blanc)
		for (int i = 0; i < counter; i++)
			lcd.printChar(' ', lcdX + i, lcdY);
	for (int i = 0; i < counter; i++);
		lcd.printNumber(long(buffer), lcdX + counter, lcdY);
}

int arrayToInt(int buffer[])
{
	return buffer[0] * 1000 + buffer[1] * 100 + buffer[2] * 10 + buffer[3];
}
// #####################################################################################################################
// ######################################### END OF CODE ###############################################################
// #####################################################################################################################