#pragma once
#include "Pixel.h"

enum howManySymbols { smallSymb, mediumSymb, largeSymb };

class ASCIIConverter {
private:
	PIXEL pixel;
	howManySymbols mode = mediumSymb;
public:
	howManySymbols getSymbolsMode() {
		return mode;
	}
	double getBrightness() {
		return pixel.getBrightness();
	}
	void setSymbolsMode(howManySymbols mode) {
		this->mode = mode;
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

	char BrightnessToASCIISymbol();
};
