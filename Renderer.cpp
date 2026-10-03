#include "Renderer.h"
#include <fstream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <fstream>
#include "Pixel.h"
#include "ASCIIConverter.h"


std::string Renderer::printASCIISymbols(ASCIIConverter ASCIIConverter)
{
    if (colorMode == 1) {
        return "\33[38;2;" + std::to_string((int)ASCIIConverter.getRed()) + ";" + std::to_string((int)ASCIIConverter.getGreen()) +
            ";" + std::to_string((int)ASCIIConverter.getBlue()) + "m" + std::string(1, ASCIIConverter.BrightnessToASCIISymbol()) + "\033[0m";
    }
    else {
        return std::string(1, ASCIIConverter.BrightnessToASCIISymbol());
    }
}

void Renderer::renderASCIIImage(ASCIIConverter ASCIIConverter, cv::Mat image)
{

    short new_width = 200;
    short new_height = 200;
    cv::Mat resized_image;
    cv::resize(image, resized_image, cv::Size(new_width, new_height));


    std::ofstream file("image.txt");


    for (size_t y = 0; y < resized_image.rows; y++) {
        for (size_t x = 0; x < resized_image.cols; x++) {

            cv::Vec3b bgrPixel = resized_image.at<cv::Vec3b>(y, x);

            ASCIIConverter.setBlue(bgrPixel[0]) ;
            ASCIIConverter.setGreen(bgrPixel[1]);
            ASCIIConverter.setRed(bgrPixel[2]);

            ASCIIConverter.getBrightness();
            file << ASCIIConverter.BrightnessToASCIISymbol();
            std::cout << printASCIISymbols(ASCIIConverter);
        }
        file << std::endl;
        std::cout << std::endl;
    }

}
