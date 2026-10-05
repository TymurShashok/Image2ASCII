#include "Pixel.h"
#include "Renderer.h"
#include "ASCIIConverter.h"
#include "Config.h"

/*@project Image2ASCII
* @version v1.0.5
* @date 05.10.2026
* @author Timur Shashok
* @link https://github.com/TymurShashok/Image2ASCII
* @acknowledgments Thank you for supporting this open-source initiative!
*/

int main(int argc, char* argv[])
{
	config conf;

	if (argc > 1) {
		conf = config(argc, argv);
	}
	Renderer render; // for Rendering in console

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
		cv::Mat resized_image;
		cv::resize(image, resized_image, cv::Size(conf.width, conf.height/2));
		render.renderASCIIImage(converter, resized_image, conf); // Making full Image
	}

	if (argc < 8) {
		render.renderASCIIImage(converter, image, conf); // Making full Image

	}

	std::cout << "\nPress Enter to exit...";
	std::cin.get();

	return 0;

}