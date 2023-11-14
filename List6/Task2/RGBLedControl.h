#ifndef RGBLEDCONTROL_H
#define RGBLEDCONTROL_H

#include "Arduino.h"
using namespace std;

class RGBLedControl {
public:
	RGBLedControl(int redPin, int greenPin, int bluePin);
	void setColor(int redVolor, int greenColor, int blueColor);
	void setColor(String colorName);

private:
	int redPin;
	int greenPin;
	int bluePin;
};

#endif