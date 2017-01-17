// #####################################################################################################################
// ######################################### MENU ######################################################################
// #####################################################################################################################
/*	Menu index:
		- Main menu
			0: Photo
			1: Video
			2: Settings
		- Photo menu

		- Video menu

		- Settings menu

*/
boolean setMenu()
{
	// X & Y are in a range where they can vary.
	boolean left = false, right = false;
	if (controller.X < -75)
		left = true;
	else if (controller.X > 75)
		right = true;
	// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
	// MAIN MENU
	// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
	if (mainMenu.active)
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
			mainMenu.active = false;
			switch (mainMenu.index)
			{
				case 0:
					photoMenu.active = true;
					break;
				case 1:
					videoMenu.active = true;
					break;
				case 2:
					manualMenu.active = true;
					break;
				case 3:
					settingsMenu.active = true;
					break;
				default:
					mainMenu.active = true;
			}
		}
	}
	// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
	// PHOTO MENU
	// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
	else if (photoMenu.active)
	{

	}
	// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
	// VIDEO MENU
	// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
	else if (videoMenu.active)
	{

	}
	// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
	// MANUAL MENU
	// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
	else if (manualMenu.active)
	{

	}
	// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
	// SETTINGS MENU
	// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
	else if (settingsMenu.active)
	{

	}

	// Hold when a button is pressed
	unsigned long buttonBHoldingTime = millis() + 1000;
	while (controller.X < -75 || controller.X > 75 || controller.Y < -75 || controller.Y > 75 || controller.Z || controller.A || controller.B)
	{
		getControllerData(true);
		if (!(controller.X < -75 || controller.X > 75 || controller.Y < -75 || controller.Y > 75 || controller.Z || controller.A || controller.B))
		{
			delay(50);
			return true;
		}
		// Holding the B button for 1 sec will lead to a jump back to the main menu
		else if (controller.B && millis() > buttonBHoldingTime)
		{
			mainMenu.active = true;
			photoMenu.active = false;
			videoMenu.active = false;
			manualMenu.active = false;
			settingsMenu.active = false;
		}
	}
	return false;
}
// #####################################################################################################################
// ######################################### END OF CODE ###############################################################
// #####################################################################################################################