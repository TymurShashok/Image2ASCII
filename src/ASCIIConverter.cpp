#include "ASCIIConverter.h"
#include <opencv2/opencv.hpp>
#include "Config.h"

std::string_view ASCIIConverter::symbolChoice(const Config& conf) {

	std::string_view smallSymbols = "@#*+=-:. "; // Small combinations
	std::string_view mediumSymbols = "@#W$9876543210?!;:=-,_. "; // Symbols::LARGE combinations
	std::string_view largeSymbols = "@$#WmaOzAdzcfvxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. "; // Symbols::LARGE combinations

	switch (conf.symbols) {
	case Symbols::SMALL: return smallSymbols;
	case Symbols::MEDIUM: return mediumSymbols;
	case Symbols::LARGE: return largeSymbols;
	default: return smallSymbols;
	}

}

MediaType ASCIIConverter::detectMediaType(const Config& conf)
{
	cv::VideoCapture video(conf.fileName);

	if (!video.isOpened()) {
		cv::Mat image = cv::imread(conf.fileName);
		if (image.empty()) {
			return UNKNOWN;
		}
		return IMAGE;
	}


	if (video.get(cv::CAP_PROP_FRAME_COUNT) > 1) {
		return VIDEO;
	}
	else {
		return IMAGE;
	}
	return UNKNOWN;
}

