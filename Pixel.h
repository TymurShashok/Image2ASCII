#pragma once

/**
*@class PIXEL
*@formulaLuma Brightness = (0.299 * Red) + (0.587 * Green) + (0.114 * Blue)
*/

class PIXEL
{
	unsigned char  B = 0; // Blue 
	unsigned char  G = 0; // Green
	unsigned char  R = 0; // Red

	double  Brightness = 0.0;
public:

	double getBrightness() {
		return Brightness = (0.299 * R) + (0.587 * G) + (0.114 * B); // Finding brightness level (0 - 255)
	}
	/**
	* ------ getters -----
	*/
	unsigned char getRed() {
		return R;
	}
	unsigned char getBlue() {
		return B;
	}
	unsigned char getGreen() {
		return G;
	}
	/**
	* ------ setters -----
	*/
	void setRed(unsigned char red) {
		R = red;
	}
	void setBlue(unsigned char blue) {
		B = blue;
	}
	void setGreen(unsigned char green) {
		G = green;
	}
};