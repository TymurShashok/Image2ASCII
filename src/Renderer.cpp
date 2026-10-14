#include "Renderer.h"
#include "Pixel.h"
#include "ASCIIConverter.h"

#include <fstream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <string>

void Renderer::enableANSIColors(const Config& conf)
{
	if (conf.colorMode == Color::RGB) {
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
	std::cout << "--symbols <Small/Symbols::LARGE/Symbols::LARGE> - out symbols format" << std::endl;
	std::cout << "--color <Color::RGB/wb> - out color format" << std::endl;
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
	conf.colorMode = Color::BW;
	conf.fileName = "Image2ASCII_Tab.jpg";
	conf.symbols = Symbols::LARGE;
	conf.width = 100;
	conf.height = 100;

	cv::Mat image = cv::imread(conf.fileName, cv::IMREAD_COLOR);
	cv::VideoCapture video(conf.fileName);
	renderASCIIImage(converter, image, conf);
}

void Renderer::renderASCIIImage(ASCIIConverter ASCIIConverter, cv::Mat image, const Config& conf)
{

	if (image.empty()) { // if file not opening or empty
		std::cout << "Can`t load a " << conf.fileName << std::endl;
		return;
	}

	enableANSIColors(conf);

	std::ofstream file("image.txt");

	std::string_view symbols = ASCIIConverter.symbolChoice(conf);
	int index;

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


	int lastR = 1;
	int lastB = 1;
	int lastG = 1;

	std::string numStr[256];

	for (int i = 0; i < 256; i++) {
		numStr[i] = std::to_string(i);
	}

	std::string str;

	cv::resize(image, resizedImage, cv::Size(width, height));

	for (int y = 0; y < resizedImage.rows; y++) {
		for (int x = 0; x < resizedImage.cols; x++) {

			cv::Vec3b bgrPixel = resizedImage.at<cv::Vec3b>(y, x);

			int b = (bgrPixel[0]);
			int g = (bgrPixel[1]);
			int r = (bgrPixel[2]);

			ASCIIConverter.setBlue(bgrPixel[0]);
			ASCIIConverter.setGreen(bgrPixel[1]);
			ASCIIConverter.setRed(bgrPixel[2]);

			if (conf.colorMode == Color::RGB) {
				if (lastB != b || lastG != g || lastR != r) {

					lastB = (bgrPixel[0]);
					lastG = (bgrPixel[1]);
					lastR = (bgrPixel[2]);
					str += "\33[38;2;";
					str += numStr[lastR];
					str += ";";
					str += numStr[lastG];
					str += ";";
					str += numStr[lastB];
					str += "m";
				}
			}

			index = std::round((ASCIIConverter.getBrightness() * (symbols.size() - 1) / 255));
			str += symbols[index];
			file << symbols[index]; // Save a ASCII Symbol in File.TXT

		}
		file << std::endl;
		str += "\n";
	}
	str += "\033[0m";
	std::cout << str;
}

void Renderer::renderASCIIVideo(ASCIIConverter ASCIIConverter, cv::VideoCapture video, const Config& conf)
{

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	DWORD dwMode = 0;
	if (GetConsoleMode(hConsole, &dwMode)) {
		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(hConsole, dwMode);
	}
	COORD coordBufCoord = { 0, 0 };

	if (!video.isOpened()) { // if file not opening or empty
		std::cout << "Can`t load a " << conf.fileName << std::endl;
		return;
	}

	enableANSIColors(conf);

	int index;
	int width = int(video.get(cv::CAP_PROP_FRAME_WIDTH));
	int height = int(video.get(cv::CAP_PROP_FRAME_HEIGHT));
	int delay = 1000 / video.get(cv::CAP_PROP_FPS);

	if (conf.hasCustomScale) {
		width = conf.scale * width;
		height = (conf.scale * height) / 2;
	}
	else if (conf.hasCustomSize) {
		width = conf.width;
		height = conf.height / 2;
	}
	else {
		height = height / 2;
	}

	cv::Mat frame;
	cv::Mat resizedFrame;

	std::string str;
	str.reserve(width * height * 20);

	std::string_view symbols = ASCIIConverter.symbolChoice(conf);

	std::string numStr[256];

	for (int i = 0; i < 256; i++) {
		numStr[i] = std::to_string(i);
	}

	int lastR = 1;
	int lastB = 1;
	int lastG = 1;

	int lastBrightness = 0.0;
	while (true) {

		video >> frame;
		if (frame.empty()) break;
		cv::resize(frame, resizedFrame, cv::Size(width, height));

		str.clear();
		for (int y = 0; y < resizedFrame.rows; y++) {
			for (int x = 0; x < resizedFrame.cols; x++) {

				cv::Vec3b bgrPixel = resizedFrame.at<cv::Vec3b>(y, x);

				int b = bgrPixel[0];
				int g = bgrPixel[1];
				int r = bgrPixel[2];

				ASCIIConverter.setBlue(bgrPixel[0]);
				ASCIIConverter.setGreen(bgrPixel[1]);
				ASCIIConverter.setRed(bgrPixel[2]);

				if (conf.colorMode == Color::RGB) {
					if (lastB != b || lastG != g || lastR != r) {

						lastB = (bgrPixel[0]);
						lastG = (bgrPixel[1]);
						lastR = (bgrPixel[2]);
						str += "\33[38;2;";
						str += numStr[lastR];
						str += ";";
						str += numStr[lastG];
						str += ";";
						str += numStr[lastB];
						str += "m";
					}
				}

				index = std::round((ASCIIConverter.getBrightness() * (symbols.size() - 1) / 255));
				str += symbols[index];
				lastBrightness = ASCIIConverter.getBrightness();
			}
			str += "\n";
		}
		str += "\033[0m";
		SetConsoleCursorPosition(hConsole, coordBufCoord);

		DWORD bytesWritten;
		WriteFile(hConsole, str.data(), static_cast<DWORD>(str.size()), &bytesWritten, NULL);

		if (cv::waitKey(delay) >= 0) break;

	}
}