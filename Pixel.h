#pragma once

class PIXEL {

	unsigned char  B = 0;
	unsigned char  G = 0;
	unsigned char  R = 0;
	double  Brightness = 0.0;

public:

	double getBrightness() {
		return Brightness = (0.299 * R) + (0.587 * G) + (0.114 * B);
	}

	unsigned char getRed() {
		return R;
	}
	unsigned char getBlue() {
		return B;
	}
	unsigned char getGreen() {
		return G;
	}

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