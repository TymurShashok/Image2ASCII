#include <src/Renderer.h>
#include <src/ASCIIConverter.h>
#include <src/Pixel.h>
#include <src/Input.h>
#include <src/Config.h>

#include <gtest/gtest.h>

TEST(ConfigTest, ReturnsDefaultValue) {

	Config conf;

	EXPECT_EQ(conf.fileName, "image.jpg");
	EXPECT_EQ(conf.colorMode, RGB);
	EXPECT_EQ(conf.symbols, Medium);

	EXPECT_EQ(conf.width, 100);
	EXPECT_EQ(conf.height, 100);

	EXPECT_EQ(conf.scale, 1.0);

	EXPECT_EQ(conf.usingARGV, false);
	EXPECT_EQ(conf.hasFileName, false);
	EXPECT_EQ(conf.hasCustomScale, false);
	EXPECT_EQ(conf.hasCustomSize, false);
}

TEST(ConfigTest, ReturnsUpdateThoughtCMD) {

	Config conf;

	int argc = 3;
	char* argv[3] = { "Image2ASCII.exe","--filename", "image2.jpg" };

	conf = Config(argc, argv);
	EXPECT_EQ(conf.fileName, "image2.jpg");
	EXPECT_EQ(conf.hasFileName, true);

	argv[1] = { "--width" };
	argv[2] = { "200" };

	conf = Config(argc, argv);

	EXPECT_EQ(conf.width, 200);
	EXPECT_EQ(conf.hasCustomSize, true);

	argv[2] = { "20" };

	conf = Config(argc, argv);

	EXPECT_EQ(conf.width, 100);
	EXPECT_EQ(conf.hasCustomSize, true);


	argv[1] = { "--height" };
	argv[2] = { "200" };

	conf = Config(argc, argv);

	EXPECT_EQ(conf.height, 200);
	EXPECT_EQ(conf.hasCustomSize, true);

	argv[1] = { "--scale" };
	argv[2] = { "0.4" };

	conf = Config(argc, argv);

	EXPECT_EQ(conf.scale, 0.4);
	EXPECT_EQ(conf.hasCustomScale, true);


	argv[1] = { "--color" };
	argv[2] = { "rgb" };

	conf = Config(argc, argv);

	EXPECT_EQ(conf.colorMode, RGB);

	argv[1] = { "--symbols" };
	argv[2] = { "medium" };

	conf = Config(argc, argv);

	EXPECT_EQ(conf.symbols, Medium);

	int argc2 = 9;
	char* argv2[9] = { "Image2ASCII.exe" ,"--filename","image2.jpg","--symbols","small","--color","blackwhite","--scale" ,"0.6" };

	conf = Config(argc2, argv2);

	EXPECT_EQ(conf.fileName, "image2.jpg");
	EXPECT_EQ(conf.symbols, Small);
	EXPECT_EQ(conf.colorMode, BlackWhite);
	EXPECT_EQ(conf.scale, 0.6);
}

TEST(ConfigTest, ReturnsConfigUpdate) {

	Config conf;

	conf.update("--filename", "image2.jpg");
	EXPECT_EQ(conf.fileName, "image2.jpg");

	conf.update("--width", "200");
	EXPECT_EQ(conf.width, 200);
	EXPECT_EQ(conf.hasCustomSize, true);

	conf.update("--height", "150");
	EXPECT_EQ(conf.height, 150);
	EXPECT_EQ(conf.hasCustomSize, true);

	conf.update("--scale", "0.3");
	EXPECT_EQ(conf.scale, 0.3);
	EXPECT_EQ(conf.hasCustomScale, true);

	conf.update("--symbols", "large");
	EXPECT_EQ(conf.symbols, Large);

	conf.update("--color", "rgb");
	EXPECT_EQ(conf.colorMode, RGB);
}
