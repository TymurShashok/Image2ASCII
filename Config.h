#pragma once
#include <string>
#include <iomanip>
#include <iostream>

enum color { BlackWhite, RGB };
enum Symbols { Small, Medium, Large }; 

struct config {

	std::string fileName = "image.jpg"; // Name of Image for ASCII transformation

	Symbols symbols = Medium; // How Many Symbols in ASCII Image
	color colorMode = RGB; // Color of ASCII Image

	short width = 40; // Result Width
	short height = 40; // Result Height

	config(int argc, char* argv[]) {
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

	/*void inputConfig() { 
		std::cin >> fileName;
		int symb;
		std::cin >> symb;

		switch (symb) {
		case 0: symbols = smallSymb; break;
		case 1: symbols = mediumSymb; break;
		case 2: symbols = largeSymb; break;
		default: symbols = mediumSymb; break;
		}

		int clrMode;
		std::cin >> clrMode;

		switch (clrMode) {
		case 0: colorMode = BlackWhite; break;
		case 1: colorMode = RGB; break;
		default: colorMode = RGB; break;
		}

		std::cin >> width >> height;
	}*/
