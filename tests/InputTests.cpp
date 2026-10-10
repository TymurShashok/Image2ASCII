#include <src/Renderer.h>
#include <src/ASCIIConverter.h>
#include <src/Pixel.h>
#include <src/Input.h>
#include <src/Config.h>

#include <gtest/gtest.h>

TEST(InputTests, ReturnsCommand ) {

	Input input;
	EXPECT_EQ(input.getCommand(), "");

	input.setCommand("--filename");
	EXPECT_EQ(input.getCommand(), "--filename");

}

TEST(InputTests, ReturnsValue) {

	Input input;
	EXPECT_EQ(input.getValue(), "");

	input.setValue("200");
	EXPECT_EQ(input.getValue(), "200");

}

TEST(InputTests, ReturnsReset) {

	Input input;

	input.setCommand("--filename");
	input.setValue("200");

	EXPECT_EQ(input.getCommand(), "--filename");
	EXPECT_EQ(input.getValue(), "200");

	input.reset();

	EXPECT_EQ(input.getCommand(), "");
	EXPECT_EQ(input.getValue(), "");

}