#include <iostream>


#include "ASCIIConverter.h"
#include "Config.h"
#include "Input.h"
#include "Renderer.h"

/*@project Image2ASCII
* @version v1.0.8
* @date 07.10.2026
* @author Timur Shashok
* @link https://github.com/TymurShashok/Image2ASCII
* @acknowledgments Thank you for supporting this open-source initiative!
*/

int main(int argc, char* argv[])
{
	/*std::string input;
	std::string input2;*/
	Input input;
	Config conf;
	Renderer render; // for Rendering in console

	if (argc > 1) { //If using ARG
		conf = Config(argc, argv);
		conf.usingARGV = true;
	}

	do {

		if (conf.usingARGV == false) {

			do {

				render.PrintTab();

				while (input.getCommand() != "--start") {
				/*	std::cout << ">";
					std::cin >> input;*/
					std::cout << ">";
					input.inputCommand();

					if (input.getCommand() == "--exit") exit(0);
					if (input.getCommand() == "--help") render.printHelpMenu();
					if (input.getCommand() != "--start" && input.getCommand() != "--help" && input.getCommand() != "--original") {
				/*		std::cin >> input2;*/
					}
					conf.update(input.getCommand(), input.getValue());
				}

			} while (input.getCommand() != "--start");

			input.reset();
		}

		ASCIIConverter converter; // Making ASCII Symbols

		cv::Mat image = cv::imread(conf.fileName, cv::IMREAD_COLOR);
		render.renderASCIIImage(converter, image, conf); // Making full Image

		system("pause");
		system("cls");

		if (conf.usingARGV == true) {
			return 0;
		}

	} while (input.getCommand() != "--exit");

	return 0;
}