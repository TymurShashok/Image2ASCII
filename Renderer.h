#pragma once
#include <string>
#include "ASCIIConverter.h"
#include <opencv2/opencv.hpp>
#include "Config.h"

class Renderer {

public:
	std::string printASCIISymbols(ASCIIConverter ASCIIConverter, config conf);
	void renderASCIIImage(ASCIIConverter ASCIIConverter, cv::Mat image, config conf);

};