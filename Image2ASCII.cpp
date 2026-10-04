#include "Pixel.h"
#include "Renderer.h"
#include "ASCIIConverter.h"
#include "Config.h"

/*@project Image2ASCII
* @version v1.0.3
* @date 04.10.2026
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

	render.renderASCIIImage(converter, image, conf); // Making full Image

	std::cout << "\nPress Enter to exit...";
	std::cin.get();

	return 0;
}