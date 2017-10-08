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
						lcd.setFont(1); // Bold
						printString(lcdPhotoMenuZero00, 2, 0);
						lcd.setFont(0); // Regular
						printString(lcdPhotoMenuZero01, 0, 2);
						printString(lcdPhotoMenuZero02, 0, 3);
						printString(lcdPhotoMenuZero03, 0, 4);
						printString(lcdPhotoMenuZero04, 0, 5);
						printString(lcdPhotoMenuZero05, 0, 6);
						break;
					case 1: // Goto zero
						lcd.setFont(1); // Bold
						printString(lcdPhotoMenuZero10, 1, 0);
						lcd.setFont(0); // Regular
						printString(lcdPhotoMenuZero11, 0, 2);
						printString(lcdPhotoMenuZero12, 0, 3);
						printString(lcdPhotoMenuZero13, 0, 4);
						printString(lcdPhotoMenuZero14, 0, 5);
						break;
					case 2: // Select start angle
						lcd.setFont(1); // Bold
						printString(lcdPhotoMenuAngle00, 1, 0);
						lcd.setFont(0); // Regular
						printString(lcdTextCurrentPosition, 0, 2);
						printString(lcdUnitDegree, 10, 5);
						break;
					case 3: // Select length
						lcd.setFont(1); // Bold
						printString(lcdPhotoMenuLength00, 1, 0);
						lcd.setFont(0); // Regular
						printString(lcdTextCurrentPosition, 0, 2);
						printString(lcdUnitMillimeter, 10, 5);
						break;
					case 4: // Select end angle
						lcd.setFont(1); // Bold
						printString(lcdPhotoMenuAngle10, 1, 0);
						lcd.setFont(0); // Regular
						printString(lcdTextCurrentPosition, 0, 2);
						printString(lcdUnitDegree, 10, 5);
						break;
					case 5: // Amount of shots
						lcd.setFont(1); // Bold
						printString(lcdPhotoMenuAmount00, 3, 0);
						lcd.setFont(0); // Regular
						printHorizontalSelector(camera.amount, selector.index, 3, 4, 3);
						printBuffer((int)camera.distancePerShot, 4, 7, true);
						printString(lcdUnitMillimeterPerShot, 10, 7);
						break;
					case 6: // Repeats of shots
						lcd.setFont(1); // Bold
						printString(lcdPhotoMenuRepeats00, 2, 0);
						lcd.setFont(0); // Regular
						printHorizontalSelector(camera.repeats, selector.index, 3, 4, 3);
						break;
					case 7: // Set shutter speed
						lcd.setFont(1); // Bold
						printString(lcdPhotoMenuShutterSpeed00, 2, 0);
						lcd.setFont(0); // Regular
						printHorizontalSelector(camera.shutter, selector.index, 3, 4, 3);
						break;
					case 8: // Set delay
						lcd.setFont(1); // Bold
						printString(lcdPhotoMenuDelay00, 3, 0);
						lcd.setFont(0); // Regular
						printHorizontalSelector(camera.delay, selector.index, 3, 4, 3);						
						break;
					case 9: // Set speed
						lcd.setFont(1); // Bold
						printString(lcdPhotoMenuSpeed00, 3, 0);
						lcd.setFont(0); // Regular
						camera.speed = printTextSelector(selector.index, 4, 4);
						break;
					default:
						lcd.setFont(1); // Bold
						printString(lcdRun00, 3, 0);
						lcd.setFont(0); // Regular
						printString(lcdRun01, 0, 2);
						printBuffer(slider.runtime, 2, 4, false);
						printString(lcdUnitSecond, 8, 4);
						printString(lcdRun02, 0, 6);
						printString(lcdRun03, 0, 7);
				}
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
					camera.mirrorLockup ? printString(lcdMenuOn, 12, 3) : printString(lcdMenuOff, 12, 3);

					printString(lcdSettingsMenu03, 0, 4);
					camera.autoFocus ? printString(lcdMenuOn, 12, 4) : printString(lcdMenuOff, 12, 4);

					printString(lcdSettingsMenu04, 0, 5);
					buffer = arrayToInt(slider.length);
					printBuffer(buffer, 8, 5, false);
					printString(lcdUnitMillimeter, 13, 5);

					printString(lcdSettingsMenu05, 0, 6);

					printVerticalSelector(settingsMenu.index, 0, 2, 6);
				}
				else 
				{
					switch (settingsMenu.index)
					{
						case 0:
							// Nothing to do here
							break;
						case 1:
							// Nothing to do here
							break;
						case 2:
							// Nothing to do here
							break;
						case 3:
							lcd.setFont(1);
							printString(lcdSettingsMenuLength, 4, 0);
							lcd.setFont(0);
							printHorizontalSelector(slider.length, selector.index, 3, 2, 3);
							printString(lcdUnitMillimeter, 11, 3);
							break;
						case 4:
							lcd.setFont(1);
							printString(lcdSettingsMenuReset00, 4, 0);
							lcd.setFont(0);
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

void printVerticalSelector(int index, int lcdX, int lcdY, int blanc) // default for blanc: 99
{	
	index == blanc ? lcd.printChar('>', lcdX, lcdY + index + 1) : lcd.printChar('>', lcdX, lcdY + index);
}

int printTextSelector(int index, int lcdX, int lcdY)
{
	switch (index) 
	{
	    case 0:
	    	printString(lcdPhotoMenuSpeed01, lcdX, lcdY);
	     	break;
	    case 1:
	    	printString(lcdPhotoMenuSpeed02, lcdX, lcdY);
	     	break;
	    case 2:
	    	printString(lcdPhotoMenuSpeed03, lcdX, lcdY);
	     	break;
	    case 3:
	    	printString(lcdPhotoMenuSpeed04, lcdX, lcdY);
	     	break;
	    case 4:
	    	printString(lcdPhotoMenuSpeed05, lcdX, lcdY);
	     	break;
	}
	return index;
}

void printBuffer(int buffer, int lcdX, int lcdY, boolean blanc)
{
	int counter = 0, absBuffer = abs(buffer);
	if (absBuffer < 10)
		counter = 4;
	else if (absBuffer < 100)
		counter = 3;
	else if (absBuffer < 1000)
		counter = 2;
	else 
		counter = 1;

	if (blanc)
		for (int i = 0; i < counter; i++)
			lcd.printChar(' ', lcdX + i, lcdY);
	//for (int i = 0; i < counter; i++);
	if (buffer < 0)
		lcd.printChar('-', lcdX + counter - 1, lcdY);
	lcd.printNumber(long(absBuffer), lcdX + counter, lcdY);
}

int arrayToInt(int buffer[])
{
	return buffer[0] * 1000 + buffer[1] * 100 + buffer[2] * 10 + buffer[3];
}