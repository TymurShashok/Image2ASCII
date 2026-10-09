#pragma once

#include <string>
#include <iostream>

enum Color { BlackWhite, RGB };
enum Symbols { Small, Medium, Large };

struct config
{
	std::string fileName = "image.jpg"; // Name of Image for ASCII transformation

	Symbols symbols = Medium; // How Many Symbols in ASCII Image
	Color colorMode = RGB; // Color of ASCII Image

	short width = 100; // Result Width
	short height = 100; // Result Height
	double scale = 1;

	bool usingARGV = false;
	bool hasFileName = false;
	bool hasCustomScale = false;
	bool hasCustomSize = false;

	config() = default;  // Default 

	config(int argc, char* argv[]) { // Working Programm
			
	/*	if (argv[1] != "--exit" && argv[1] != "--filename" && argv[1] != "--symbols" && argv[1] != "--color" && argv[1] != "--original"
			&& argv[1] != "--scale" && argv[1] != "--width" && argv[1] != "--height") {
			std::cout << "Wrong Command: Use --help to information!" << std::endl;
			exit(0);
		}*/

			if (std::string(argv[1]) == "--exit") {
				exit(0);
			}

		if (std::string(argv[1]) == "--filename") {
			fileName = std::string(argv[2]);
			hasFileName = true;
		}

		for (int i = 0; i < argc; i++) {

			if (std::string(argv[i]) == "--symbols") {
				if (std::string(argv[i + 1]) == "Small" || std::string(argv[i + 1]) == "small") {
					symbols = Small;
				}
				else if (std::string(argv[i + 1]) == "Medium" || std::string(argv[i + 1]) == "medium") {
					symbols = Medium;
				}
				else {
					symbols = Large;
				}
			}

			if (std::string(argv[i]) == "--color") {
				if (std::string(argv[i + 1]) == "RGB" || std::string(argv[i + 1]) == "rgb") {
					colorMode = RGB;
				}
				else {
					colorMode = BlackWhite;
				}
			}

			if (std::string(argv[i]) == "--original") { // without Resizing;
				return;
			}
			if (std::string(argv[i]) == "--scale") {
				if (argv[i + 1]) {
					scale = std::stod(argv[i + 1]);
					hasCustomSize = true;
				}
			}
			if (std::string(argv[i]) == "--width") {
				if (argv[i + 1]) {
					width = std::stoi(argv[i + 1]);
					width = checkSize(width);
				}
			}
			if (std::string(argv[i]) == "--height") {
				if (argv[i + 1]) {
					height = std::stoi(argv[i + 1]);
					height = checkSize(height);
				}
			}
		}
	}

	int checkSize(int size)
	{
		if (size < 100) {
			return size = 100;
		}
		return size;
	}

	void ConfigInput(const std::string& text, const std::string& text2) {

		if (text == "--filename") {
			fileName = text2;
			hasFileName = true;
		}
		if (text == "--symbols") {
			if (text2 == "small") { symbols = Small; }
			if (text2 == "medium") { symbols = Medium; }
			else { symbols = Large; }
		}
		if (text == "--color") {
			if (text2 == "rgb") { colorMode = RGB; }
			if (text2 == "blackwhite") { colorMode = BlackWhite; }
		}
		if (text == "--width") {
			width = std::stoi(text2);
			width = checkSize(width);
			hasCustomSize = true;
		}
		if (text == "--height") {
			height = std::stoi(text2);
			height = checkSize(height);
			hasCustomSize = true;
		}
		if (text == "--scale") {
			scale = std::stod(text2);
			hasCustomScale = true;
		}
		if (text == "--original") {
			hasCustomSize = false;
		}
	}

};