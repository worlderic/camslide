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
				if (!photoMenu.indexActive)
				{
					printString(lcdPhotoMenu00, 3, 0);

					printString(lcdPhotoMenu01, 0, 2);
					buffer = arrayToInt(working.distance);
					printBuffer(buffer, 9, 2);
					printString(lcdUnitMillimeter, 13, 2);

					printString(lcdPhotoMenu02, 0, 3);
					buffer = arrayToInt(working.repeats);
					printBuffer(buffer, 9, 3);

					printString(lcdPhotoMenu03, 0, 4);
					buffer = arrayToInt(working.shutter);
					printBuffer(buffer, 9, 4);
					printString(lcdUnitSecond, 13, 4);

					printString(lcdPhotoMenu04, 0, 5);
					buffer = arrayToInt(working.delay);
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
							printHorizontalSelector(working.distance, selector.index, 3, 2, 3);
							printString(lcdUnitMillimeter, 11, 3);
							break;
						case 1:
							printString(lcdPhotoMenuRepeats, 4, 0);
							printHorizontalSelector(working.repeats, selector.index, 3, 4, 3);
							break;
						case 2:
							printString(lcdPhotoMenuShutter, 1, 0);
							printHorizontalSelector(working.shutter, selector.index, 3, 2, 3);
							printString(lcdUnitSecond, 11, 3);
							break;
						case 3:
							printString(lcdPhotoMenuDelay, 5, 0);
							printHorizontalSelector(working.delay, selector.index, 3, 2, 3);
							printString(lcdUnitSecond, 11, 3);
							break;
					}
				}
				break;
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			// MANUAL MENU
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			case 1:
				lcd.printString("Manual Menu", 0, 0);
				break;
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			// SETTINGS MENU
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			case 2:
				lcd.printString("Settings Menu", 0, 0);
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

void printBuffer(int buffer, int lcdX, int lcdY)
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