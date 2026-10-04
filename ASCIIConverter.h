#pragma once
#include "Pixel.h"
#include "Config.h"

class ASCIIConverter {
private:
	PIXEL pixel;
public:
	double getBrightness() {
		return pixel.getBrightness();
	}
	unsigned char getRed() {
		return pixel.getRed();
	}
	unsigned char getBlue() {
		return pixel.getBlue();
	}
	unsigned char getGreen() {
		return pixel.getGreen();
	}
	void setRed(unsigned char red) {
		pixel.setRed(red);
	}
	void setBlue(unsigned char blue) {
		pixel.setBlue(blue);
	}
	void setGreen(unsigned char green) {
		pixel.setGreen(green);
	}

	char BrightnessToASCIISymbol(config conf);
};
