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
			photoMenu.index = 0;
			lcd.clear();
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
				switch (photoMenu.index)
				{
					case 0: // Set zero
						if (controller.B)
							mainMenu.indexActive = false;
						else if (left || right)
						{
							left ? slider.zeroIsLeft = true : slider.zeroIsLeft = false;
							photoMenu.index++;
							lcd.clear();
						}
						break;
					case 1: // Goto zero
						gotoZero(false, 2);
						photoMenu.index++;
						lcd.clear();
						printMenu();
						break;
					case 2: // Set angle 1
						turner.position1 = turner.absPos;
						PORTD |= _BV(PORTD5);
						while (!controller.A && !controller.B)
						{
							getControllerData(true);
							if (abs(controller.X) > 5)
							{
								if (controller.X > 0)
								{
									PORTD &= ~_BV(PORTD6);
									turner.position1++;
								}
								else 
								{
									PORTD |= _BV(PORTD6);
									turner.position1--;	
								}
								PORTD |= _BV(PORTD7); // HIGH
							    delayMicroseconds(motor.delay);
							    PORTD &= ~_BV(PORTD7); // LOW
							    delayMicroseconds(map(abs(controller.X), 5, 100, 3000, 1500));
							}
							else
							{
								printBuffer((int)stepsToDegrees(turner.position1), 4, 5, true);
							}
						}
						turner.absPos = turner.position1;
						if (controller.A || controller.B)
						{
							lcd.clear();
							controller.A ? photoMenu.index++ : photoMenu.index = 0;
							motor.locked ? enableMotors() : disableMotors();
						}
						break;
					case 3: // Set length
						PORTD |= _BV(PORTD2);
						while (!controller.A && !controller.B)
						{
							getControllerData(true);
							if (abs(controller.X) > 5)
							{
								if (controller.X > 0)
								{
									PORTD |= _BV(PORTD3);
									slider.zeroIsLeft ? slider.position2++ : slider.position2--;
								}
								else 
								{
									PORTD &= ~_BV(PORTD3);	
									slider.zeroIsLeft ? slider.position2-- : slider.position2++;
								}
								PORTD |= _BV(PORTD4); // HIGH
							    delayMicroseconds(motor.delay);
							    PORTD &= ~_BV(PORTD4); // LOW
							    delayMicroseconds(map(abs(controller.X), 5, 100, MOTOR_MAX_DELAY, MOTOR_MIN_DELAY));
							}
							else
							{
								printBuffer((int)stepsToMillimeter(slider.position2), 4, 5, true);
							}
						}
						slider.totalSteps = abs(slider.position2); //abs(slider.position2 - slider.position1);
						camera.travelDistance = stepsToMillimeter(slider.totalSteps);
						//camera.distancePerShot = (camera.travelDistance / arrayToInt(camera.amount));
						standardOnControllerAB();
						break;
					case 4: // Set angle 2
						turner.position2 = turner.absPos;
						PORTD |= _BV(PORTD5);
						while (!controller.A && !controller.B)
						{
							getControllerData(true);
							if (abs(controller.X) > 5)
							{
								if (controller.X > 0)
								{
									PORTD &= ~_BV(PORTD6);
									turner.position2++;
								}
								else 
								{
									PORTD |= _BV(PORTD6);
									turner.position2--;	
								}
								PORTD |= _BV(PORTD7); // HIGH
							    delayMicroseconds(motor.delay);
							    PORTD &= ~_BV(PORTD7); // LOW
							    delayMicroseconds(map(abs(controller.X), 5, 100, 3000, 1500));
							}
							else
							{
								printBuffer((int)stepsToDegrees(turner.position2), 4, 5, true);
							}
						}
						turner.absPos = turner.position2;
						turner.totalSteps = abs(turner.position2 - turner.position1);
						standardOnControllerAB();
						break;
					case 5: // Set amount of shots
						setSelectorHorizontal(0, 3, right, left);
						setSelectorHorizontalIndex(camera.amount, 0, 9, up, down, zeroNotAllowed);
						camera.distancePerShot = (camera.travelDistance / arrayToInt(camera.amount));
						standardOnControllerAB();
						break;
					case 6: // Set repeats of shots
						setSelectorHorizontal(0, 3, right, left);
						setSelectorHorizontalIndex(camera.repeats, 0, 9, up, down, zeroNotAllowed);
						standardOnControllerAB();
						break;
					case 7: // Set shutter speed
						setSelectorHorizontal(0, 3, right, left);
						setSelectorHorizontalIndex(camera.shutter, 0, 9, up, down, zeroIsAllowed);
						standardOnControllerAB();
						break;
					case 8: // Set delay
						setSelectorHorizontal(0, 3, right, left);
						setSelectorHorizontalIndex(camera.delay, 0, 9, up, down, zeroIsAllowed);
						standardOnControllerAB();
						break;
					case 9: // Set speed
						setSelectorVertical(0, 4, up, down);
						standardOnControllerAB();
						break;
					default:
						//
						slider.runtime = 200;
						//				
						if (controller.A)
						{
							run();
							mainMenu.indexActive = false;
							photoMenu.index = 0;
							lcd.clear();
							printMenu();
							lcd.setDisplayOn();
						}
						else if (controller.B)
						{
							photoMenu.index--;
							lcd.clear();
						}
				}
				break;
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			// MANUAL MENU
			// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
			case 1:
				lcd.setDisplayOff();
				manualRun();
				mainMenu.indexActive = false;
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
						switch (settingsMenu.index)
						{
							case 0: // En/Disable motor
								motor.enabled = !motor.enabled;
								motor.enabled ? enableMotors() : disableMotors();
								delay(200);
								return(true);
							case 1: // Mirror lockup
								camera.mirrorLockup = !camera.mirrorLockup;
								EEPROM.write(EEPROM_mirrorLockup, camera.mirrorLockup ? byte(1) : byte(0));
								delay(200);
								return(true);
								break;
							case 2: // Autofocus
								camera.autoFocus = !camera.autoFocus;
								EEPROM.write(EEPROM_autoFocus, camera.autoFocus ? 1 : 0);
								delay(200);
								return(true);
								break;
							case 3: // Set length
								for (int i = 0; i < 4; i++)
									sliderPrev.length[i] = slider.length[i];
								break;
							case 4: // Lock
								motor.locked = !motor.locked;
								EEPROM.write(EEPROM_motorLocked, motor.locked ? 1 : 0);
								delay(200);
								return(true);
								break;	
						}
						lcd.clear();
						settingsMenu.indexActive = true;
						selector.index = 0;
					}
					if (controller.B)
					{
						mainMenu.indexActive = false;
						lcd.clear();
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
						case 0: // En/Disable Stepper
							break;
						case 1: // Mirror lockup								
							break;
						case 2: // Autofocus								
							break;
						case 3: // Set length
							if (up)
								slider.length[selector.index] + 1 > 9 ? slider.length[selector.index] = 0 : slider.length[selector.index] ++;
							if (down)
								slider.length[selector.index] - 1 < 0 ? slider.length[selector.index] = 9 : slider.length[selector.index] --;
							if (controller.A)
							{
								lcd.clear();
								lcd.setFont(1);
								printString(lcdPhotoMenuLength00, 1, 0);
								lcd.setFont(0);
								printString(lcdPhotoMenuLength01, 0, 2);
								printString(lcdPhotoMenuLength02, 0, 3);
								printString(lcdPhotoMenuLength03, 0, 4);
								// Now go from zero A to zero B to get the amount of steps per mm
								unsigned long ticks = 0;
								slider.zeroIsLeft = true;
								gotoZero(false, 1);
								PORTD |= _BV(PORTD2);
								PORTD |= _BV(PORTD3);
								while (digitalRead(Sensor))
								{
									PORTD |= _BV(PORTD4);
									delayMicroseconds(motor.delay);
									PORTD &= ~_BV(PORTD4);
									delayMicroseconds(step.minDelay);
									ticks++;
								}
								slider.zeroIsLeft = false;
								gotoZero(false, 1);
								disableMotors();

								slider.transmission = ticks / arrayToInt(slider.length); // steps/mm

								EEPROM.write(EEPROM_MSB_transmission, (int(slider.transmission * 100) >> 8) & 0xFF);
								EEPROM.write(EEPROM_LSB_transmission, (int(slider.transmission * 100)) & 0xFF);
								for (int i = 0; i < 4; i++)
									EEPROM.write(i + EEPROM_length, slider.length[i]);
							}
							if (controller.B)
								for (int i = 0; i < 4; i++)
									slider.length[i] = sliderPrev.length[i];
							break;
						case 4: // Locked
							break;
					}

					if (controller.A || controller.B)
					{
						settingsMenu.indexActive = false;
						lcd.clear();
					}
				}
				break;
		}
	}

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

void setSelectorHorizontal(int minVal, int maxVal, boolean right, boolean left)
{
	if (right)
		selector.index + 1 > maxVal ? selector.index = minVal : selector.index++;
	else if (left)
		selector.index - 1 < minVal ? selector.index = maxVal : selector.index--;
}

void setSelectorVertical(int minVal, int maxVal, boolean up, boolean down)
{
	setSelectorHorizontal(minVal, maxVal, up, down);
}

void setSelectorHorizontalIndex(int data[], int minVal, int maxVal, boolean up, boolean down, boolean zeroAllowence)
{
	if (up)
		data[selector.index] + 1 > maxVal ? data[selector.index] = minVal : data[selector.index] ++;
	else if (down)
		data[selector.index] - 1 < minVal ? data[selector.index] = maxVal : data[selector.index] --;
	if (zeroAllowence && (data[0] < 1 && data[1] < 1 && data[2] < 1 && data[3] < 1))
		data[3] = 1;
}

void standardOnControllerAB()
{
	if (controller.A || controller.B)
	{
		lcd.clear();
		controller.A ? photoMenu.index++ : photoMenu.index--;
		motor.locked ? enableMotors() : disableMotors();
	}
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
		//camera.distance[i] = 0;
		camera.amount[i] = i == 0 ? 1 : 0;
		camera.repeats[i] = i == 0 ? 1 : 0;
		camera.shutter[i] = 0;
		camera.delay[i] = 0;
	}
}