#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
struct PIXEL {

    byte B;
    byte G;
    byte R;
    byte Brightness;

    unsigned char getBrightness() {
        return Brightness = (0.299 * R) + (0.587 * G) + (0.114 * B);
    }
};

char BrightnessToASCIISymbol(PIXEL pixel, int mode) {

    const char* smallSymbols = "@#*+=-:. ";
    const char* mediumSymbols = "@#W$9876543210?!;:=-,._ ";
    const char* largeSymbols = "@$#WmaOzAdzcfvxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. ";


    int activeLength = 0;
    const char* activeASCIISymbols;
    switch (mode) {
    case 1: 
    {
        activeASCIISymbols = smallSymbols;
        activeLength = 10;
        break;
    }
    case 2: 
    {
        activeASCIISymbols = mediumSymbols;
        activeLength = 25;
        break;
        break;
    }
    case 3: 
    {
        activeASCIISymbols = largeSymbols;
        activeLength = 49;
        break;
    }
    default: {
        activeASCIISymbols = smallSymbols;
        activeLength = 9;
        break;
    }
}

int index = (pixel.Brightness * (activeLength - 1) / 255);

return activeASCIISymbols[index];
}

int main()
{
    PIXEL pixel;
    cv::Mat image = cv::imread("image.jpg", cv::IMREAD_COLOR);

    if (image.empty()) {
        std::cout << "Can`t load a image.jpg" << std::endl;
        return -1;
    }

    int new_width = 200;
    int new_height = 200;
    int mode = 1;

    cv::Mat resized_image;
    cv::resize(image, resized_image, cv::Size(new_width, new_height));

   for (size_t y = 0; y < resized_image.rows; y++) {
        for (size_t x = 0; x < resized_image.cols; x++) {

            cv::Vec3b bgrPixel = resized_image.at<cv::Vec3b>(y, x);

            pixel.B = bgrPixel[0];
            pixel.G = bgrPixel[1];
            pixel.R = bgrPixel[2];

            pixel.getBrightness();
            std::cout << BrightnessToASCIISymbol(pixel, mode);
        }
        std::cout << std::endl;
    }
    
}
