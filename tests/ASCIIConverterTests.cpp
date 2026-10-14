#include <src/Renderer.h>
#include <src/ASCIIConverter.h>
#include <src/Pixel.h>
#include <src/Input.h>
#include <src/Config.h>

#include <gtest/gtest.h>

TEST(ASCIIConverterTest, ReturnsDarkestSymbol) {

	ASCIIConverter converter;
	Config conf;

	converter.setBlue(0);
	converter.setGreen(0);
	converter.setRed(0);

	std::string_view symbols = converter.symbolChoice(conf);

	int index = std::round((converter.getBrightness() * (symbols.size() - 1) / 255));
	
	unsigned char symb = symbols[index];
	ASSERT_EQ(converter.getBrightness(), 0);
	
	EXPECT_EQ(symb, '@');
	
}

TEST(ASCIIConverterTest, ReturnsBrightestSymbol) {

	ASCIIConverter converter;
	Config conf;

	converter.setBlue(255);
	converter.setGreen(255);
	converter.setRed(255);


	std::string_view symbols = converter.symbolChoice(conf);

	int index = std::round((converter.getBrightness() * (symbols.size() - 1) / 255));
	ASSERT_EQ(converter.getBrightness(), 255);
	EXPECT_EQ(symbols[index], ' ');

}

TEST(ASCIIConverterTest, ReturnsAverageBrightnessSymbol) {

	ASCIIConverter converter;
	Config conf;

	converter.setBlue(128);
	converter.setGreen(128);
	converter.setRed(128);


	std::string_view symbols;
	int index;


	conf.symbols = Symbols::SMALL;	
	symbols = converter.symbolChoice(conf);
	index = std::round((converter.getBrightness() * (symbols.size() - 1) / 255));

	EXPECT_NEAR(converter.getBrightness(), 128, 0.1);
	EXPECT_EQ(symbols[index], '=');

	conf.symbols = Symbols::MEDIUM;
	symbols = converter.symbolChoice(conf);
	index = std::round((converter.getBrightness() * (symbols.size() - 1) / 255));
	EXPECT_NEAR(converter.getBrightness(), 128, 0.1);
	EXPECT_EQ(symbols[index], '1');

	conf.symbols = Symbols::LARGE;
	symbols = converter.symbolChoice(conf);
	index = std::round((converter.getBrightness() * (symbols.size() - 1) / 255));
	EXPECT_NEAR(converter.getBrightness(), 128, 0.1);
	EXPECT_EQ(symbols[index], '{');
}
