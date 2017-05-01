// #####################################################################################################################
// ######################################### WORKING ###################################################################
// #####################################################################################################################
void run()
{
	int runtime, length, position, distance, repeats, shutter, d3lay;
	unsigned long stepsPerShot;

	// Calculate runtime
	runtime = 200;
	// ???
	
	// Print message on display for at least 5 secs.
	unsigned long messageTime = millis() + 5000;

	lcd.clearDisplay();
	printString(lcdRun01, 0, 0);
	printString(lcdRun02, 0, 1);
	printBuffer(runtime, 3, 4);
	printString(lcdUnitSecond, 8, 4);
	printString(lcdRun03, 0, 6);
	printString(lcdRun04, 0, 7);

	gotoZero();

	while (messageTime > millis()) {} // Do nothing
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

	// And finally start
	while (true)
	{
		PORTD &= ~_BV(PORTD3); // Direction LOW

		for(int i = 0; i < 5000; i++) 
		{
		    if (digitalRead(Sensor))
		    {
			    PORTD |= _BV(PORTD4); // Step HIGH
			    delayMicroseconds(motor.delay);
			    PORTD &= ~_BV(PORTD4); // Step LOW
			    delayMicroseconds(750);
			}
		}

		break;
	}
}

void manualRun()
{
	enableMotors();
	while (!controller.B)
	{
		getControllerData(true);

		controller.X > 0 ? PORTD |= _BV(PORTD3) : PORTD &= ~_BV(PORTD3);

		if (abs(controller.X) > 5 && digitalRead(Sensor))
		{
			PORTD |= _BV(PORTD4); // HIGH
		    delayMicroseconds(motor.delay);
		    PORTD &= ~_BV(PORTD4); // LOW
		    delayMicroseconds(map(abs(controller.X), 5, 100, 3000, 200));
		}
	}
}

void gotoZero()
{
	enableMotors();
	slider.zeroIsLeft ? PORTD |= _BV(PORTD3) : PORTD &= ~_BV(PORTD3);
	while (digitalRead(Sensor))
	{
		PORTD |= _BV(PORTD4); // HIGH
	    delayMicroseconds(motor.delay);
	    PORTD &= ~_BV(PORTD4); // LOW
	    delayMicroseconds(1750);
	}
	delay(100);
	slider.zeroIsLeft ? PORTD &= ~_BV(PORTD3) : PORTD |= _BV(PORTD3);
	while (!digitalRead(Sensor))
	{
	    PORTD |= _BV(PORTD4); // HIGH
	    delayMicroseconds(motor.delay);
	    PORTD &= ~_BV(PORTD4); // LOW
	    delayMicroseconds(2500);
	}
	delay(100);
	slider.position1 = 0;
}

void enableMotors()
{
	PORTD |= _BV(PORTD2);
	PORTD |= _BV(PORTD5);
	motor.enabled = true;
}

void disableMotors()
{
	PORTD &= ~_BV(PORTD2);
	PORTD &= ~_BV(PORTD5);
	motor.enabled = false;
}
// #####################################################################################################################
// ######################################### END OF CODE################################################################
// #####################################################################################################################