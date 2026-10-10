#include "ASCIIConverter.h"
#include "Config.h"

char ASCIIConverter::BrightnessToASCIISymbol(const Config& conf)
{
	/**
	* Combinations of ASCII Symbols.
	* ASCII Paletes from Darkest to Brightest.
	*/
	std::string_view smallSymbols = "@#*+=-:. "	; // Small combinations
	std::string_view mediumSymbols = "@#W$9876543210?!;:=-,_. "; // Medium combinations
	std::string_view largeSymbols = "@$#WmaOzAdzcfvxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. "; // Large combinations

	uint8_t activeLength = 0;
	std::string_view activeASCIISymbols;
	switch (conf.symbols) {
	case Small:
	{
		activeASCIISymbols = smallSymbols;
		activeLength = smallSymbols.size(); // Small length
		break;
	}
	case Medium:
	{
		activeASCIISymbols = mediumSymbols;
		activeLength = mediumSymbols.size(); // Medium length
		break;
	}
	case Large:
	{
		activeASCIISymbols = largeSymbols;
		activeLength = largeSymbols.size(); // Large Length
		break;
	}
	default: {
		activeASCIISymbols = smallSymbols;
		activeLength = smallSymbols.size(); // Default: Small length
		break;
	}
	}

	/**
	* @formula to find a index of Symbol: Brightness * (Length - 1) / MAX_BRIGHTNESS;
	*/
	int index = std::round((pixel.getBrightness() * (activeLength - 1) / 255));

	return activeASCIISymbols[index];
}

