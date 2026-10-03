#pragma once
#include <string>
#include "ASCIIConverter.h"
#include <opencv2/opencv.hpp>

enum color { BlackWhite, RGB };

class Renderer {
	color colorMode = RGB; // BlackWhite or RGB
public:
	std::string printASCIISymbols(ASCIIConverter ASCIIConverter);
	void renderASCIIImage(ASCIIConverter ASCIIConverter, cv::Mat image);

};