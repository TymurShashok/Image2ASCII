#include "Pixel.h"
#include "Renderer.h"
#include "ASCIIConverter.h"

int main()
{
    cv::Mat image = cv::imread("image1.jpg", cv::IMREAD_COLOR);

    if (image.empty()) {
        std::cout << "Can`t load a image.jpg" << std::endl;
        exit(0);
    }

    Renderer render;
    ASCIIConverter converter;

    render.renderASCIIImage(converter, image);
}
