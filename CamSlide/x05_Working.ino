// #####################################################################################################################
// ######################################### WORKING ###################################################################
// #####################################################################################################################
void run()
{
	int runtime, length, position, distance, repeats, shutter, d3lay;
	unsigned long stepsPerShot;

	// Calculate & print runtime
	runtime = 200;

	lcd.clearDisplay();
	printString(lcdRun01, 0, 0);
	printString(lcdRun02, 0, 2);
	printBuffer(runtime, 3, 4);
	printString(lcdUnitSecond, 8, 4);
	printString(lcdRun03, 0, 6);
	printString(lcdRun04, 0, 7);
	delay(5000);

	// Set to zero
	gotoZero();
	lcd.setDisplayOff();

	// Prepare for working routine
	length = arrayToInt(slider.length);
	position = arrayToInt(slider.length);
	distance = arrayToInt(working.distance);
	repeats = arrayToInt(working.repeats);
	shutter = arrayToInt(working.shutter);
	d3lay = arrayToInt(working.delay);

	// Calculate steps per shot
	stepsPerShot = 100;

	while (true)
	{

	}

	printMenu();
	lcd.setDisplayOn();
}

void gotoZero()
{
	
}
// #####################################################################################################################
// ######################################### END OF CODE################################################################
// #####################################################################################################################