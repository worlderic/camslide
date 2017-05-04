// #####################################################################################################################
// ######################################### WORKING ###################################################################
// #####################################################################################################################
void run()
{
	int length, position, distance, repeats, shutter, d3lay;

	gotoZero();

	lcd.setDisplayOff();

	// Prepare for working routine
	length = arrayToInt(slider.length);
	position = arrayToInt(slider.length);
	repeats = arrayToInt(camera.repeats);
	shutter = arrayToInt(camera.shutter);
	d3lay = arrayToInt(camera.delay);

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
	slider.position2 = 0;
}

float stepsToMillimeter(int steps)
{
	return (steps * slider.transmission);
}

float stepsToDegrees(int steps)
{
	return (steps * turner.transmission);
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