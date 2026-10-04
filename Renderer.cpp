#include "Renderer.h"
#include <fstream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include "Pixel.h"
#include "ASCIIConverter.h"

void Renderer::enableANSIColors()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	DWORD mode = 0;
	GetConsoleMode(hOut, &mode);

	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	SetConsoleMode(hOut, mode);
}

std::string Renderer::printASCIISymbols(ASCIIConverter ASCIIConverter,const config& conf)
{
	if (conf.colorMode == RGB) {
		return "\33[38;2;" + std::to_string((int)ASCIIConverter.getRed()) + ";" + std::to_string((int)ASCIIConverter.getGreen()) +
			";" + std::to_string((int)ASCIIConverter.getBlue()) + "m" + std::string(1, ASCIIConverter.BrightnessToASCIISymbol(conf)) + "\033[0m";
	}
	else {
		return std::string(1, ASCIIConverter.BrightnessToASCIISymbol(conf));
	}
}

void Renderer::renderASCIIImage(ASCIIConverter ASCIIConverter, cv::Mat image,const config& conf)
{

	cv::Mat resized_image;
	cv::resize(image, resized_image, cv::Size(conf.width, conf.height));

	std::ofstream file("image.txt");

	for (int y = 0; y < resized_image.rows; y++) {
		for (int x = 0; x < resized_image.cols; x++) {

			cv::Vec3b bgrPixel = resized_image.at<cv::Vec3b>(y, x);

			ASCIIConverter.setBlue(bgrPixel[0]);
			ASCIIConverter.setGreen(bgrPixel[1]);
			ASCIIConverter.setRed(bgrPixel[2]);


			ASCIIConverter.getBrightness(); 
			file << ASCIIConverter.BrightnessToASCIISymbol(conf); // Save a ASCII Symbol in File.TXT
			std::cout << printASCIISymbols(ASCIIConverter, conf); // Print a Symbol with using of Color-System 
		}
		file << std::endl;
		std::cout << std::endl;
	}

}