#include "ASCIIConverter.h"
#include "Config.h"

char ASCIIConverter::BrightnessToASCIISymbol(const config& conf) 
{

	const char* smallSymbols = "@#*+=-:. ";
	const char* mediumSymbols = "@#W$9876543210?!;:=-,._ ";
	const char* largeSymbols = "@$#WmaOzAdzcfvxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

	short activeLength = 0;
	const char* activeASCIISymbols;
	switch (conf.symbols) {
	case Small:
	{
		activeASCIISymbols = smallSymbols;
		activeLength = 9;
		break;
	}
	case Medium:
	{
		activeASCIISymbols = mediumSymbols;
		activeLength = 24;
		break;
	}
	case Large:
	{
		activeASCIISymbols = largeSymbols;
		activeLength = 48;
		break;
	}
	default: {
		activeASCIISymbols = smallSymbols;
		activeLength = 9;
		break;
	}
	}

	int index = (static_cast<int>(pixel.getBrightness()) * (activeLength - 1) / 255); // Choice a symbol

	return activeASCIISymbols[index];
}

