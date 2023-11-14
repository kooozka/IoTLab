#include "RGBLedControl.h"

RGBLedControl::RGBLedControl(int redPin, int greenPin, int bluePin)
{
	this->redPin = redPin;
	this->greenPin = greenPin;
	this->bluePin = bluePin;

	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);
}

void RGBLedControl::setColor(int redColor, int greenColor, int blueColor) {
	if (redColor > 255)
		redColor = 255;
	else if (redColor < 0)
		redColor = 0;
	if (greenColor > 255)
		greenColor = 255;
	else if (greenColor < 0)
		greenColor = 0;
	if (blueColor > 255)
		blueColor = 255;
	else if (blueColor < 0)
		blueColor = 0;

	analogWrite(redPin, redColor);
	analogWrite(greenPin, greenColor);
	analogWrite(bluePin, blueColor);


}

void RGBLedControl::setColor(String colorName) {
	colorName.toUpperCase();
	if (colorName == "RED")
		setColor(255, 0, 0);
	else if (colorName == "GREEN")
		setColor(0, 255, 0);
	else if (colorName == "BLUE")
		setColor(0, 0, 255);
	else if (colorName == "YELLOW")
		setColor(255, 255, 0);
	else if (colorName == "CYAN")
		setColor(0, 255, 255);
	else if (colorName == "MAGENTA")
		setColor(255, 0, 255);
	else if (colorName == "BLACK")
		setColor(0, 0, 0);
	else if (colorName == "WHITE")
		setColor(255, 255, 255);
	else {
		setColor(0, 0, 0);
	}
}
