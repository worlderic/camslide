// #####################################################################################################################
// ######################################### CONTROLLER ################################################################
// #####################################################################################################################
void getControllerData(boolean mapData)
{
	controller.A = digitalRead(Controller_A);
	controller.B = digitalRead(Controller_B);
	controller.Z = digitalRead(Controller_Z);

	controller.X = analogRead(Controller_X);
	controller.Y = analogRead(Controller_Y);

	/* 	Map the analog data:
		Range: -100 to +100
	*/
	if (mapData)
	{
		controller.X = map(controller.X, controller.XMin, controller.XMax, -100, 100);
		controller.Y = map(controller.Y, controller.YMin, controller.YMax, -100, 100);
	}
}

void calibrateController()
{
	int bufferXMin = 1023;
	int bufferXMax = 0;
	int bufferYMin = 1023;
	int bufferYMax = 0;

	do {
		getControllerData(false);
		if (controller.X < bufferXMin)
			bufferXMin = controller.X;
		if (controller.X > bufferXMax)
			bufferXMax = controller.X;
		if (controller.Y < bufferYMin)
			bufferYMin = controller.Y;
		if (controller.Y > bufferYMax)
			bufferYMax = controller.Y;
	} while (!controller.Z);
	
	controller.XMin = bufferXMin;
	controller.XMax = bufferXMax;
	controller.YMin = bufferYMin;
	controller.YMax = bufferYMax;
}
// #####################################################################################################################  
// ######################################### END OF CODE ###############################################################
// #####################################################################################################################