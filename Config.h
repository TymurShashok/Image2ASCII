#pragma once
#include <string>

enum color { BlackWhite, RGB };
enum Symbols { Small, Medium, Large };

struct config
{
	std::string fileName = "image.jpg"; // Name of Image for ASCII transformation

	Symbols symbols = Medium; // How Many Symbols in ASCII Image
	color colorMode = RGB; // Color of ASCII Image

	short width = 100; // Result Width
	short height = 100; // Result Height
	config() { fileName = "friren.jpg"; symbols = Medium; colorMode = RGB; width = 200; height = 200; } // Default 

	config(int argc, char* argv[]) { // Working Programm

		if (argv[1]) {
			fileName = argv[1];
		}

		if (std::string(argv[2]) == "Small" || std::string(argv[2]) == "small") { symbols = Small; }
		else if (std::string(argv[2]) == "Medium" || std::string(argv[2]) == "medium") { symbols = Medium; }
		else { symbols = Large; }

		if (std::string(argv[3]) == "Color" || std::string(argv[3]) == "color") {
			colorMode = RGB;
		}
		else {
			colorMode = BlackWhite;
		}
		if (argv[4]) {
			width = std::stoi(argv[4]);
		}
		if (argv[5]) {
			height = std::stoi(argv[5]);
		}
	}
};
