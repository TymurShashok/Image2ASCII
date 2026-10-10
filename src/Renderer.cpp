#include "Renderer.h"
#include "Pixel.h"
#include "ASCIIConverter.h"

#include <fstream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>

void Renderer::enableANSIColors(const Config& conf)
{
	if (conf.colorMode == RGB) {
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		DWORD mode = 0;
		GetConsoleMode(hOut, &mode);

		mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

		SetConsoleMode(hOut, mode);
	}
}

void Renderer::printError(const Config& conf)
{
	if (conf.hasFileName == false) {
		std::cout << "* Wrong file name or path" << std::endl;
	}
}

void Renderer::printHelpMenu()
{
	std::cout << "========================HELP========================" << std::endl;;
	std::cout << "--filename <Name.type or Path>" << std::endl;
	std::cout << "--symbols <Small/Medium/Large> - out symbols format" << std::endl;
	std::cout << "--color <rgb/wb> - out color format" << std::endl;
	std::cout << "--width <cols> - out width" << std::endl;
	std::cout << "--height <rows> - out height" << std::endl;
	std::cout << "--start - starting programm" << std::endl;
	std::cout << "--exit - leave" << std::endl;

	system("pause");
	system("cls");
	PrintTab();
}

void Renderer::PrintTab() {

	Config conf;
	ASCIIConverter converter;
	conf.colorMode = BlackWhite;
	conf.fileName = "Image2ASCII_Tab.jpg";
	conf.symbols = Large;
	conf.width = 100;
	conf.height = 100;

	cv::Mat image = cv::imread(conf.fileName, cv::IMREAD_COLOR);

	renderASCIIImage(converter, image, conf);
}

std::string Renderer::printASCIISymbols(ASCIIConverter ASCIIConverter, const Config& conf)
{
	if (conf.colorMode == RGB) {
		return "\33[38;2;" + std::to_string((int)ASCIIConverter.getRed()) + ";" + std::to_string((int)ASCIIConverter.getGreen()) +
			";" + std::to_string((int)ASCIIConverter.getBlue()) + "m" + std::string(1, ASCIIConverter.BrightnessToASCIISymbol(conf)) + "\033[0m";
	}
	else {
		return std::string(1, ASCIIConverter.BrightnessToASCIISymbol(conf));
	}
}

void Renderer::renderASCIIImage(ASCIIConverter ASCIIConverter, cv::Mat image, const Config& conf)
{

	if (image.empty()) { // if file not opening or empty
		std::cout << "Can`t load a " << conf.fileName << std::endl;
		return;
	}

	enableANSIColors(conf);
	std::ofstream file("image.txt");
	cv::Mat resizedImage;

	int width;
	int height;

	if (conf.hasCustomScale) {
		width = conf.scale * image.cols;
		height = (conf.scale * image.rows) / 2;
	}
	else if (conf.hasCustomSize) {
		width = conf.width;
		height = conf.height / 2;
	}
	else {
		width = image.cols;
		height = image.rows / 2;
	}


	cv::resize(image, resizedImage, cv::Size(width, height));

	for (int y = 0; y < resizedImage.rows; y++) {
		for (int x = 0; x < resizedImage.cols; x++) {

			cv::Vec3b bgrPixel = resizedImage.at<cv::Vec3b>(y, x);

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