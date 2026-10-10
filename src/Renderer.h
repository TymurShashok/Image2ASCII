#pragma once
#include "Config.h"
#include "ASCIIConverter.h"

#include <string>
#include <opencv2/opencv.hpp>
/**
* @class Renderer
* @brief system a responsibile for print ASCII;
*/

class Renderer
{

public:
	void enableANSIColors(const Config& conf); // Enabling a ANSI colors for Terminal
	void printError(const Config& conf);
	void printHelpMenu();
	void PrintTab();
	std::string printASCIISymbols(ASCIIConverter ASCIIConverter, const Config& conf);
	void renderASCIIImage(ASCIIConverter ASCIIConverter, cv::Mat image, const Config& conf);

};