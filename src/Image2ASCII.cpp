#include <iostream>

#include <opencv2/core/utils/logger.hpp>
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

	cv::utils::logging::setLogLevel(
		cv::utils::logging::LOG_LEVEL_WARNING
	);

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

					std::cout << ">";
					input.inputCommand();

					if (input.getCommand() == "--exit") exit(0);
					if (input.getCommand() == "--help") render.printHelpMenu();
					if (input.getCommand() != "--start" && input.getCommand() != "--help" && input.getCommand() != "--original") {
					}

					conf.update(input.getCommand(), input.getValue());
				}

			} while (input.getCommand() != "--start");

			input.reset();
		}

		ASCIIConverter converter; // Making ASCII Symbols

		cv::VideoCapture video(conf.fileName);

		cv::Mat image = cv::imread(conf.fileName, cv::IMREAD_COLOR);

		MediaType mediaType;
		mediaType = converter.detectMediaType(conf);

		if (mediaType == IMAGE) {
			render.renderASCIIImage(converter, image, conf); // Making full Image
		}
		else if (mediaType == VIDEO) {
			render.renderASCIIVideo(converter, video, conf); // Making full Image
		}
		else {
			std::cout << "Unknown file format!";
			return -1;
		}

		system("pause");
		system("cls");

		if (conf.usingARGV == true) {
			return 0;
		}

	} while (input.getCommand() != "--exit");

	return 0;
}