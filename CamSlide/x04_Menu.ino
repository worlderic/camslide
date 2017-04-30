// #####################################################################################################################
// ######################################### MENU ######################################################################
// #####################################################################################################################
/*	Menu index:
		- Main menu
			0: Photo
			1: Manual
			2: Settings
		- Photo menu

		- Manual menu

		- Settings menu

*/
boolean setMenu()
{
	// X & Y are in a range where they can vary.
	boolean left = false, right = false, up = false, down = false;
	if (controller.X < -75)
		left = true;
	else if (controller.X > 75)
		right = true;
	if (controller.Y < -75)
		down = true;
	else if (controller.Y > 75)
		up = true;
	// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
	// MAIN MENU
	// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
	if (!mainMenu.indexActive)
	{
		if (left) 
			mainMenu.index--;
		if (right) 
			mainMenu.index++;

		if (mainMenu.index < 0)
			mainMenu.index = mainMenu.maxIndex;
		else if (mainMenu.index > mainMenu.maxIndex)
			mainMenu.index = 0;

		if (controller.A)
		{
			mainMenu.indexActive = true;
			lcd.clearDisplay();
		}
	}
	else 
	{
		switch(mainMenu.index)
		{
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			// PHOTO MENU
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			case 0:
				if (!photoMenu.indexActive)
				{
					if (up)
						photoMenu.index--;
					if (down)
						photoMenu.index++;

					if (photoMenu.index < 0)
						photoMenu.index = photoMenu.maxIndex;
					else if (photoMenu.index > photoMenu.maxIndex)
						photoMenu.index = 0;

					if (controller.A)
					{
						for (int i = 0; i < 4; i++)
						{
							switch (photoMenu.index)
							{
								case 0:
									workingPrev.distance[i] = working.distance[i];
									break;
								case 1:
									workingPrev.repeats[i] = working.repeats[i];
									break;	
								case 2:
									workingPrev.shutter[i] = working.shutter[i];
									break;
								case 3:
									workingPrev.delay[i] = working.delay[i];
									break;
							}
						}
						lcd.clearDisplay();
						photoMenu.indexActive = true;
						selector.index = 0;
					}
					if (controller.B)
					{
						mainMenu.indexActive = false;
						lcd.clearDisplay();
					}
				}
				else 
				{
					if (right)
						selector.index + 1 > 3 ? selector.index = 0 : selector.index++;
					if (left)
						selector.index - 1 < 0 ? selector.index = 3 : selector.index--;
					switch (photoMenu.index)
					{
						case 0:
							if (up)
								working.distance[selector.index] + 1 > 9 ? working.distance[selector.index] = 0 : working.distance[selector.index] ++;
							if (down)
								working.distance[selector.index] - 1 < 0 ? working.distance[selector.index] = 9 : working.distance[selector.index] --;
							if (controller.B)
								for (int i = 0; i < 4; i++)
									working.distance[i] = workingPrev.distance[i];
							break;
						case 1:
							if (up)
								working.repeats[selector.index] + 1 > 9 ? working.repeats[selector.index] = 0 : working.repeats[selector.index] ++;
							if (down)
								working.repeats[selector.index] - 1 < 0 ? working.repeats[selector.index] = 9 : working.repeats[selector.index] --;
							if (controller.B)
								for (int i = 0; i < 4; i++)
									working.repeats[i] = workingPrev.repeats[i];
							break;
						case 2:
							if (up)
								working.shutter[selector.index] + 1 > 9 ? working.shutter[selector.index] = 0 : working.shutter[selector.index] ++;
							if (down)
								working.shutter[selector.index] - 1 < 0 ? working.shutter[selector.index] = 9 : working.shutter[selector.index] --;
							if (controller.B)
								for (int i = 0; i < 4; i++)
									working.shutter[i] = workingPrev.shutter[i];
							break;
						case 3:
							if (up)
								working.delay[selector.index] + 1 > 9 ? working.delay[selector.index] = 0 : working.delay[selector.index] ++;
							if (down)
								working.delay[selector.index] - 1 < 0 ? working.delay[selector.index] = 9 : working.delay[selector.index] --;
							if (controller.B)
								for (int i = 0; i < 4; i++)
									working.delay[i] = workingPrev.delay[i];
							break;
						case 4: 
							run();
							controller.B = true;
							break;
					}

					if (controller.A || controller.B)
					{
						photoMenu.indexActive = false;
						lcd.clearDisplay();
					}
				}
				break;
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			// MANUAL MENU
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			case 1:
				lcd.setDisplayOff();
				manualRun();
				mainMenu.indexActive = false;;
				lcd.setDisplayOn();
				break;
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			// SETTINGS MENU
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			case 2:
				if (!settingsMenu.indexActive)
				{
					if (up)
						settingsMenu.index--;
					if (down)
						settingsMenu.index++;

					if (settingsMenu.index < 0)
						settingsMenu.index = settingsMenu.maxIndex;
					else if (settingsMenu.index > settingsMenu.maxIndex)
						settingsMenu.index = 0;

					if (controller.A)
					{
						for (int i = 0; i < 4; i++)
						{
							switch (settingsMenu.index)
							{
								case 0:
									slider.enabled ? slider.enabled = false : slider.enabled = true;
									slider.enabled ? enableAll() : disableAll();
									delay(200);
									return(true);
								case 1:
									sliderPrev.length[i] = slider.length[i];
									break;
								case 2:
									// Nothing to do here
									break;	
							}
						}
						lcd.clearDisplay();
						settingsMenu.indexActive = true;
						selector.index = 0;
					}
					if (controller.B)
					{
						mainMenu.indexActive = false;
						lcd.clearDisplay();
					}
				}
				else 
				{
					if (right)
						selector.index + 1 > 3 ? selector.index = 0 : selector.index++;
					if (left)
						selector.index - 1 < 0 ? selector.index = 3 : selector.index--;
					switch (settingsMenu.index)
					{
						case 0:
							// Nothing to do here
							break;
						case 1:
								if (up)
									slider.length[selector.index] + 1 > 9 ? slider.length[selector.index] = 0 : slider.length[selector.index] ++;
								if (down)
									slider.length[selector.index] - 1 < 0 ? slider.length[selector.index] = 9 : slider.length[selector.index] --;
								if (controller.A)
									for (int i = 0; i < 4; i++)
										EEPROM.write(i + EEPROM_length, slider.length[i]);
								if (controller.B)
									for (int i = 0; i < 4; i++)
										slider.length[i] = sliderPrev.length[i];
							break;
						case 2:
							if (controller.A)
							{
								EEPROM.write(EEPROM_fail, 0);
								for (int i = 0; i < 4; i++)
								{
									EEPROM.write(i + EEPROM_pos, 0);
									EEPROM.write(i + EEPROM_length, 0);
								}
							}
							break;
					}

					if (controller.A || controller.B)
					{
						settingsMenu.indexActive = false;
						lcd.clearDisplay();
					}
				}
				break;
		}
	}

	// Check if all data are valid:
	if (arrayToInt(working.distance) > arrayToInt(slider.length))
		for (byte i = 0; i < 4; i++)
			working.distance[i] = slider.length[i];

	// Print menu only when something has been changed
	while (controller.X < -75 || controller.X > 75 || controller.Y < -75 || controller.Y > 75 || controller.Z || controller.A || controller.B)
	{
		getControllerData(true);
		if (!(controller.X < -75 || controller.X > 75 || controller.Y < -75 || controller.Y > 75 || controller.Z || controller.A || controller.B))
		{
			delay(50);
			return true;
		}
	}
	return false;
}

void unactiveAll()
{
	mainMenu.indexActive = false;
	photoMenu.indexActive = false;
	manualMenu.indexActive = false;
	settingsMenu.indexActive = false;
}

void zeroAll()
{
	for (byte i = 0; i < 4; i++)
	{
		working.distance[i] = 0;
		working.repeats[i] = 0;
		working.shutter[i] = 0;
		working.delay[i] = 0;
	}
	working.mirrorLockup = false;
	working.autoFocus = false;
}
// #####################################################################################################################
// ######################################### END OF CODE ###############################################################
// #####################################################################################################################