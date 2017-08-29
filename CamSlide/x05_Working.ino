// #####################################################################################################################
// ######################################### WORKING ###################################################################
// #####################################################################################################################
void run()
{
	lcd.setDisplayOff();

	long amount, distance, repeats, shutter, d3lay, stepsBetweenShots, stepsBetweenShotsLinear, stepsBetweenShotsAngular,
		 driveTimeBetweenShots, turnTimeBetweenShots, timeInMovement;
	motor.delay = 250; // µs
	step.delay = 2000; // µs

	gotoZero(true);
	/*
	// Place turner at starting position
	turner.position1 > 0 ? PORTD |= _BV(PORTD6) : PORTD &= ~_BV(PORTD6);
	for (int i = 0; i < abs(turner.position1); i++)
	{
		PORTD |= _BV(PORTD7); // HIGH
	    delayMicroseconds(motor.delay);
	    PORTD &= ~_BV(PORTD7); // LOW
	    delayMicroseconds(3000);
	}
	*/

	// Prepare for working routine
	amount = arrayToInt(camera.amount); // 1
	repeats = arrayToInt(camera.repeats); // 1
	shutter = arrayToInt(camera.shutter) * 1000; // ms
	d3lay = arrayToInt(camera.delay) * 1000; // ms
	
	// Calc. delay time
	stepsBetweenShotsLinear = slider.totalSteps / amount;
	driveTimeBetweenShots = 1.25 * stepsBetweenShotsLinear; // ms               Step-Constant not correct yet
	turnTimeBetweenShots = 1.25 * stepsBetweenShotsAngular; // ms 				Step-Constant not correct yet
	timeInMovement = driveTimeBetweenShots > turnTimeBetweenShots ? driveTimeBetweenShots : turnTimeBetweenShots; // ms

	// Calc steps on turner
	stepsBetweenShotsAngular = turner.totalSteps / amount;
	stepsBetweenShots = stepsBetweenShotsLinear > stepsBetweenShotsAngular ? stepsBetweenShotsLinear : stepsBetweenShotsAngular;

	// And finally start
	slider.zeroIsLeft ? PORTD &= ~_BV(PORTD3) : PORTD |= _BV(PORTD3);
	turner.position1 > turner.position2 ? PORTD |= _BV(PORTD6) : PORTD &= ~_BV(PORTD6);
	for (int j = 0; j < amount + 1; j++)
	{
		// Trigger camera
		for (int i = 0; i < repeats; i++)
		{
			PORTB |= _BV(PORTB4);
			shutter == 0 ? delay(100) : delay(shutter);
			PORTB &= ~_BV(PORTB4);
			delay(i + 1 == repeats ? 100 : d3lay);
		}
		// Drive & turn
		if (j < amount)
		{
			for (int i = 0; i < stepsBetweenShots; i++) 
			{
			    if (i < stepsBetweenShotsLinear)
				    PORTD |= _BV(PORTD4); // Linear HIGH
				if (i < stepsBetweenShotsAngular)
					PORTD |= _BV(PORTD7); // Angular HIGH
				delayMicroseconds(motor.delay);
			    PORTD &= ~_BV(PORTD4); // Linear LOW
				PORTD &= ~_BV(PORTD7); // Angular LOW
				delayMicroseconds(step.delay);
			}
			if (d3lay - timeInMovement > 500)
				delay(d3lay - timeInMovement);
			else 
				delay(500);
		}
	}
	disableMotors();
	delay(50);
	enableMotors();
}

void manualRun()
{
	boolean selDirR, linearSelected = true;
	enableMotors();
	while (!controller.B)
	{
		getControllerData(true);
		if (controller.X > 0)
		{
			selDirR = true;
			PORTD |= _BV(PORTD3);
			PORTD |= _BV(PORTD6);
		}
		else 
		{
			selDirR = false;
			PORTD &= ~_BV(PORTD3);
			PORTD &= ~_BV(PORTD6);
		}

		if (!digitalRead(Sensor))
		{
			PORTD &= ~_BV(PORTD4); // Linear LOW
			delay(500);
			selDirR ? PORTD &= ~_BV(PORTD3) : PORTD |= _BV(PORTD3);
			while (!digitalRead(Sensor))
			{
				PORTD |= _BV(PORTD4); // HIGH
				delayMicroseconds(motor.delay);
				PORTD &= ~_BV(PORTD4); // LOW
				delayMicroseconds(step.maxDelay);
			}
			delay(1000);
		}
		else if (abs(controller.X) > 5)
		{
			linearSelected ? PORTD |= _BV(PORTD4) : PORTD |= _BV(PORTD7);
			delayMicroseconds(motor.delay);
			PORTD &= ~_BV(PORTD4); // LOW
			PORTD &= ~_BV(PORTD7); // LOW
			delayMicroseconds(map(abs(controller.X), 5, 100, step.maxDelay, step.minDelay));
		}
		else if (controller.Z)
		{
			linearSelected = !linearSelected;
		}
		else if (controller.A) // Take a photo
		{
			PORTB |= _BV(PORTB4);
			delay(100);
			PORTB &= ~_BV(PORTB4);
		}
	}
}

void gotoZero(boolean turnerToStartPos)
{
	int turnerTicks = 0;
	enableMotors();
	slider.zeroIsLeft ? PORTD |= _BV(PORTD3) : PORTD &= ~_BV(PORTD3);
	if (turnerToStartPos)
	{
		turner.absPos > turner.position1 ? PORTD |= _BV(PORTD6) : PORTD &= ~_BV(PORTD6);
		turnerTicks = abs(turner.absPos - turner.position1);
		turner.absPos = turner.position1;
	}
	else 
	{
		turner.absPos < 0 ? PORTD |= _BV(PORTD6) : PORTD &= ~_BV(PORTD6);
		turnerTicks = abs(turner.absPos);
		turner.absPos = 0;
	}
	while (digitalRead(Sensor) || turnerTicks > 0)
	{
		if (digitalRead(Sensor))
			PORTD |= _BV(PORTD4); // HIGH
		if (turnerTicks > 0)
		{
			PORTD |= _BV(PORTD7); // HIGH
		    turnerTicks--;
		}
		delayMicroseconds(motor.delay);
		PORTD &= ~_BV(PORTD4); // LOW
		PORTD &= ~_BV(PORTD7); // LOW
		delayMicroseconds(step.minDelay);
	}
	delay(100);
	slider.zeroIsLeft ? PORTD &= ~_BV(PORTD3) : PORTD |= _BV(PORTD3);
	while (!digitalRead(Sensor))
	{
	    PORTD |= _BV(PORTD4); // HIGH
	    delayMicroseconds(motor.delay);
	    PORTD &= ~_BV(PORTD4); // LOW
	    delayMicroseconds(step.maxDelay);
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
    PORTD &= ~_BV(PORTD4); // Step LOW
	PORTD &= ~_BV(PORTD7); // Step LOW
	motor.enabled = true;
}

void disableMotors()
{
	PORTD &= ~_BV(PORTD2);
	PORTD &= ~_BV(PORTD5);
	motor.enabled = false;
}