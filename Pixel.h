#pragma once

class PIXEL {

	unsigned char  B;
	unsigned char  G;
	unsigned char  R;
	double  Brightness;

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