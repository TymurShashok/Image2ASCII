#pragma once
#include "Pixel.h"
#include "Config.h"
/**
*@Class ASCIIConverter 
*@Brief For convert Pixel-Data to ASCII Symbols 
*/
class ASCIIConverter 
{
	PIXEL pixel; 
public:

	/**
	* ------ getters ----- 
	*/
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

	/**
	* ------ setters -----
	*/
	void setRed(unsigned char red) {
		pixel.setRed(red);
	}
	void setBlue(unsigned char blue) {
		pixel.setBlue(blue);
	}
	void setGreen(unsigned char green) {
		pixel.setGreen(green);
	}

	/**
	* @brief Function for Converting brightness of Pixel to ASCII Symbol
	* @return symbol ASCII, visual identical to brightness;
	*/
	char BrightnessToASCIISymbol(const config& conf);
};
