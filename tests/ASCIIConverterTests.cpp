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

	ASSERT_EQ(converter.getBrightness(), 0);
	EXPECT_EQ(converter.BrightnessToASCIISymbol(conf), '@');
	
}

TEST(ASCIIConverterTest, ReturnsBrightestSymbol) {

	ASCIIConverter converter;
	Config conf;

	converter.setBlue(255);
	converter.setGreen(255);
	converter.setRed(255);

	ASSERT_EQ(converter.getBrightness(), 255);
	EXPECT_EQ(converter.BrightnessToASCIISymbol(conf), ' ');	

}

TEST(ASCIIConverterTest, ReturnsAverageBrightnessSymbol) {

	ASCIIConverter converter;
	Config conf;

	converter.setBlue(128);
	converter.setGreen(128);
	converter.setRed(128);

	conf.symbols = Small;	
	EXPECT_NEAR(converter.getBrightness(), 128, 0.1);
	EXPECT_EQ(converter.BrightnessToASCIISymbol(conf), '=');

	conf.symbols = Medium;
	EXPECT_NEAR(converter.getBrightness(), 128, 0.1);
	EXPECT_EQ(converter.BrightnessToASCIISymbol(conf), '1');

	conf.symbols = Large;
	EXPECT_NEAR(converter.getBrightness(), 128, 0.1);
	EXPECT_EQ(converter.BrightnessToASCIISymbol(conf), '{');
}
