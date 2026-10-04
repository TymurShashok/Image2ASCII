#include "Pixel.h"
#include "Renderer.h"
#include "ASCIIConverter.h"
#include <Windows.h>
#include "Config.h"

void enableANSI()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	DWORD mode = 0;
	GetConsoleMode(hOut, &mode);

	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	SetConsoleMode(hOut, mode);
}

int main(int argc, char* argv[])
{
	enableANSI();
	
	if (argc < 1) {
		exit(0);
	}

	config conf(argc, argv);
	Renderer render; // for Rendering in console
	ASCIIConverter converter; // Making ASCII Symbols

	cv::Mat image = cv::imread(conf.fileName, cv::IMREAD_COLOR); // Folder with sln
	
	if (image.empty()) { // if file not opening or empty
		std::cout << "Can`t load a image.jpg" << std::endl;
		exit(0);
	}

	render.renderASCIIImage(converter, image, conf); // Making full Image
	
	std::cout << "\nPress Enter to exit...";
	std::cin.get();

	return 0;
}
