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
	std::string input;
	std::string input2;

	config conf;
	Renderer render; // for Rendering in console
	do {

		if (conf.hasFileName) {
			return 0;
		}
		
		if (argc > 1) { //If using ARG
			conf = config(argc, argv);
			conf.usingARGV = true;

		}

		if (conf.usingARGV == false) {

			do {

				render.PrintTab();

				while (input != "--start") {
					std::cout << ">";
					std::cin >> input;
					if (input == "--help") { render.printHelpMenu(); }
					if (input != "--start" && input != "--help" && input != "--original") {
						std::cin >> input2;
					}
					conf.ConfigInput(input, input2);
				}

			} while (input != "--start");

		}

		ASCIIConverter converter; // Making ASCII Symbols

		// If we use colors, we need to change mode for Windows Terminal;
		if (conf.colorMode == RGB) { render.enableANSIColors(); } // -----Changing-----

		cv::Mat image = cv::imread(conf.fileName, cv::IMREAD_COLOR);
		render.renderASCIIImage(converter, image, conf); // Making full Image

		input = "0";

		system("pause");
		system("cls");

	} while (input != "--exit");

	return 0;
}