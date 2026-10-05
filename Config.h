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
	config() { fileName = "image.jpg"; symbols = Medium; colorMode = RGB; width; height; } // Default 

	config(int argc, char* argv[]) { // Working Programm

		if (argv[1]) {
			fileName = std::string(argv[1]);

			for (int i = 0; i < argc; i++) {

				if (std::string(argv[i]) == "--symbols") {
					if (std::string(argv[i + 1]) == "Small" || std::string(argv[i + 1]) == "small") { symbols = Small; }
					else if (std::string(argv[i + 1]) == "Medium" || std::string(argv[i + 1]) == "medium") { symbols = Medium; }
					else if (std::string(argv[i + 1]) == "Large" || std::string(argv[i + 1]) == "large") { symbols = Large; }
				}

				if (std::string(argv[i]) == "--color") {
					if (std::string(argv[i + 1]) == "RGB" || std::string(argv[i + 1]) == "rgb") {
						colorMode = RGB;
					}
					else if (std::string(argv[i + 1]) == "BW" || std::string(argv[i + 1]) == "BW") {
						colorMode = BlackWhite;
					}
				}

				if (std::string(argv[i]) == "--original") { // without Resizing;
					return;
				}
				if (std::string(argv[i]) == "--width") {
					if (argv[i + 1]) {
						width = std::stoi(argv[i + 1]);
					}
				}
				if (std::string(argv[i]) == "--height") {
					if (argv[i + 1]) {
						height = std::stoi(argv[i + 1]);
					}
				}
			}
		}
	}
};