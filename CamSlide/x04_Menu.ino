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
	boolean left, right;
	if (controller.X < -75)
		left = true;
	else if (controller.X > 75)
		right = true;
	else 
		left = right = false;
	// Now set the menu
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
					settingsMenu.active = true;
					break;
				default:
					mainMenu.active = true;
			}
		}
	}
	else if (photoMenu.active)
	{

	}
	else if (videoMenu.active)
	{

	}
	else if (settingsMenu.active)
	{

	}

	// only print the menu when any value has been changed
	left || right || controller.X || controller.A || controller.B ? return true : return false;
}
// #####################################################################################################################
// ######################################### END OF CODE ###############################################################
// #####################################################################################################################