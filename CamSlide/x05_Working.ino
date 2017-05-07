// #####################################################################################################################
// ######################################### WORKING ###################################################################
// #####################################################################################################################
void run()
{
	int amount, distance, repeats, shutter, d3lay, stepsBetweenShots, driveTimeBetweenShots, stabD3lay;

	gotoZero();

	lcd.setDisplayOff();

	// Prepare for working routine
	amount = arrayToInt(camera.amount);
	repeats = arrayToInt(camera.repeats);
	shutter = arrayToInt(camera.shutter);
	d3lay = arrayToInt(camera.delay);
	stepsBetweenShots = camera.totalSteps / amount;
	driveTimeBetweenShots = 2000; // Needs to be calculated!
	stabD3lay = 1500; // Delay for stabilisation

	// And finally start
	slider.zeroIsLeft ? PORTD &= ~_BV(PORTD3) : PORTD |= _BV(PORTD3);
	for (int j = 0; j < amount + 1; j++)
	{
		// Trigger camera
		for (int i = 0; i < repeats; i++)
		{
			PORTB |= _BV(PORTB5);
			shutter == 0 ? delay(100) : delay(shutter);
			PORTB &= ~_BV(PORTB5);
			shutter == 0 ? delay(900) : delay(shutter + 1000);
			delay(d3lay - driveTimeBetweenShots);
		}
		// Drive
		if (j < amount)
		{
			for(int i = 0; i < stepsBetweenShots; i++) 
			{
			    PORTD |= _BV(PORTD4); // Step HIGH
			    delayMicroseconds(motor.delay);
			    PORTD &= ~_BV(PORTD4); // Step LOW
			    delayMicroseconds(1500);
			}
			delay(stabD3lay);
		}

		break;
	}
}

void manualRun()
{
	boolean linearSelected = true;
	enableMotors();
	while (!controller.B)
	{
		getControllerData(true);

		controller.X > 0 ? PORTD |= _BV(PORTD3) : PORTD &= ~_BV(PORTD3);

		if (abs(controller.X) > 5 && digitalRead(Sensor))
		{
			if (linearSelected)
			{
				PORTD |= _BV(PORTD4); // HIGH
			    delayMicroseconds(motor.delay);
			    PORTD &= ~_BV(PORTD4); // LOW
			    delayMicroseconds(map(abs(controller.X), 5, 100, 3000, 200));
			}
			else 
			{
		    	PORTD |= _BV(PORTD7); // HIGH
		        delayMicroseconds(motor.delay);
		        PORTD &= ~_BV(PORTD7); // LOW
		        delayMicroseconds(map(abs(controller.X), 5, 100, 3000, 1500));
			}
		}
		else if (controller.Z)
		{
			linearSelected = !linearSelected;
		}
		else if (controller.A)
		{
			PORTB |= _BV(PORTB5);
			delay(100);
			PORTB &= ~_BV(PORTB5);
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