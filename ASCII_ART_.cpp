#include "Pixel.h"
#include "Renderer.h"
#include "ASCIIConverter.h"

int main() {
	cv::Mat image = cv::imread("image1.jpg", cv::IMREAD_COLOR); // Folder with sln

	if (image.empty()) { // if file not opening or empty
		std::cout << "Can`t load a image.jpg" << std::endl;
		exit(0);
	}

	Renderer render; // for Rendering in console
	ASCIIConverter converter; // Making ASCII Symbols

	render.renderASCIIImage(converter, image); // Making full Image
}
