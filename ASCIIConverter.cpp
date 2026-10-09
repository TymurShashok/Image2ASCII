#include "ASCIIConverter.h"
#include "Config.h"

char ASCIIConverter::BrightnessToASCIISymbol(const config& conf)
{
	/**
	* Combinations of ASCII Symbols.
	* ASCII Paletes from Darkest to Brightest.
	*/
	const char* smallSymbols = "@#*+=-:. "; // Small combinations
	const char* mediumSymbols = "@#W$9876543210?!;:=-,._ "; // Medium combinations
	const char* largeSymbols = "@$#WmaOzAdzcfvxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. "; // Large combinations

	uint8_t activeLength = 0;
	const char* activeASCIISymbols;
	switch (conf.symbols) {
	case Small:
	{
		activeASCIISymbols = smallSymbols;
		activeLength = 9; // Small length
		break;
	}
	case Medium:
	{
		activeASCIISymbols = mediumSymbols;
		activeLength = 24; // Medium length
		break;
	}
	case Large:
	{
		activeASCIISymbols = largeSymbols;
		activeLength = 48; // Large Length
		break;
	}
	default: {
		activeASCIISymbols = smallSymbols;
		activeLength = 9; // Default: Small length
		break;
	}
	}

	/**
	* @formula to find a index of Symbol: Brightness * (Length - 1) / MAX_BRIGHTNESS;
	*/
	int index = (static_cast<int>(pixel.getBrightness()) * (activeLength - 1) / 255);

	return activeASCIISymbols[index];
}

