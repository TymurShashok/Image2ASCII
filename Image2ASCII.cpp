#include "Pixel.h"
#include "Renderer.h"
#include "ASCIIConverter.h"
#include "Config.h"
#include <windows.h>
/*@project Image2ASCII
* @version v1.0.7
* @date 07.10.2026
* @author Timur Shashok
* @link https://github.com/TymurShashok/Image2ASCII
* @acknowledgments Thank you for supporting this open-source initiative!
*/
int main(int argc, char* argv[])
{
	std::string input;
	std::string input2;
	std::string cmd;
	config conf;
	Renderer render; // for Rendering in console

	if (argc > 1) { //If using ARG
		conf = config(argc, argv);

		// If we use colors, we need to change mode for Windows Terminal;
		if (conf.colorMode == RGB) {
			render.enableANSIColors(); // -----Changing-----
		}

		ASCIIConverter converter; // Making ASCII Symbols

		cv::Mat image = cv::imread(conf.fileName, cv::IMREAD_COLOR);

		if (image.empty()) { // if file not opening or empty
			std::cout << "Can`t load a " << conf.fileName << std::endl;
			exit(0);
		}


		if (argc >= 8) {
			conf.hasCustomSize = true;
		}
		render.renderASCIIImage(converter, image, conf); // Making full Image
	}

	else { // With exe

		do {

			render.PrintTab();
			do {
				std::cout << ">";
				std::cin >> input;
				if (input != "--start") {
					std::cin >> input2;
					conf.ConfigInput(input, input2);
				}
			} while (input != "--start");
			// If we use colors, we need to change mode for Windows Terminal;
			if (conf.colorMode == RGB) {
				render.enableANSIColors(); // -----Changing-----
			}

			ASCIIConverter converter; // Making ASCII Symbols

			cv::Mat image = cv::imread(conf.fileName, cv::IMREAD_COLOR);

			if (image.empty()) { // if file not opening or empty
				std::cout << "Can`t load a " << conf.fileName << std::endl;
				exit(0);
			}
			render.renderASCIIImage(converter, image, conf); // Making full Image

			system("pause");
			system("cls");

		} while (input != "--exit");


	}
	return 0;

}