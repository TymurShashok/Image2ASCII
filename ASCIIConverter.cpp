#include "ASCIIConverter.h"


char ASCIIConverter::BrightnessToASCIISymbol() {

	const char* smallSymbols = "@#*+=-:. ";
	const char* mediumSymbols = "@#W$9876543210?!;:=-,._ ";
	const char* largeSymbols = "@$#WmaOzAdzcfvxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

	int activeLength = 0;
	const char* activeASCIISymbols;
	switch (getSymbolsMode()) {
	case smallSymb:
	{
		activeASCIISymbols = smallSymbols;
		activeLength = 9;
		break;
	}
	case mediumSymb:
	{
		activeASCIISymbols = mediumSymbols;
		activeLength = 24;
		break;
	}
	case largeSymb:
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

