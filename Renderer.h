#pragma once
#include <string>
#include "ASCIIConverter.h"
#include <opencv2/opencv.hpp>
#include "Config.h"
/**
* @class Renderer
* @brief system a responsibile for print ASCII;
*/

class Renderer
{

public:
	void enableANSIColors(); // Enabling a ANSI colors for Terminal
	void printError(config& conf);
	void printHelpMenu();
	void PrintTab();
	std::string printASCIISymbols(ASCIIConverter ASCIIConverter, const config& conf);
	void renderASCIIImage(ASCIIConverter ASCIIConverter, cv::Mat image, const config& conf);

};